#include "stdafx.h"
#include "HttpMethods.h"
#include "HttpException.hpp"
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/SSLException.h>
#include <shared/exception/Exception.hpp>
#include <shared/Log.h>
#include "SecureSession.h"
#include "StandardSession.h"
#include <Poco/URI.h>

namespace shared
{
   CDataContainer CHttpMethods::sendGetRequest(const std::string& url)
   {
      return sendGetRequest(url, CDataContainer());
   }

   bool CHttpMethods::sendGetRequest(const boost::shared_ptr<IHTTPSession> session,
                                     const CDataContainer& headerParameters,
                                     const CDataContainer& parameters,
                                     boost::function1<void, CDataContainer&> onReceive,
                                     const boost::posix_time::time_duration& timeout)
   {
      try
      {
         auto mapParameters = parameters.getAsMap();
         auto mapheaderParameters = headerParameters.getAsMap();
         Poco::URI uri(session->getUrl());

         if (!parameters.empty())
         {
            for (const auto& parametersIterator : mapParameters)
               uri.addQueryParameter(parametersIterator.first, parametersIterator.second);
         }

         Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_GET,
                                        uri.getPathAndQuery(),
                                        Poco::Net::HTTPMessage::HTTP_1_1);

         if (!headerParameters.empty())
         {
            for (const auto& headerparametersIterator : mapheaderParameters)
               request.add(headerparametersIterator.first, headerparametersIterator.second);
         }

         session->setTimeout(timeout);
         session->sendRequest(request);

         Poco::Net::HTTPResponse response;

         if (response.getStatus() == Poco::Net::HTTPResponse::HTTP_OK)
         {
            CDataContainer data;

            if (jsonResponseReader(session, response, data))
            {
               onReceive(data);
               return true;
            }

            const auto message = (boost::format("content not yet managed : %1%") % response.getContentType()).str();
            YADOMS_LOG(error) << message;
            throw exception::CException(message);
         }

         const auto message = (boost::format("Invalid HTTP result : %1%") % response.getReason()).str();
         YADOMS_LOG(error) << message;
         throw exception::CException(message);
      }
      catch (const Poco::Net::SSLException& e)
      {
         std::cerr << e.what() << ": " << e.message() << std::endl;
         throw CHttpException(e.message());
      }
      catch (Poco::Exception& e)
      {
         const auto message = (boost::format("Fail to send get http request \"%1%\" : %2%") % session->getUrl() % e.message()).str();
         YADOMS_LOG(error) << message;
         throw CHttpException(message);
      }
   }

   CDataContainer CHttpMethods::sendGetRequest(const std::string& url,
                                               const CDataContainer& parameters,
                                               const boost::posix_time::time_duration& timeout)
   {
      CDataContainer responseData;
      const auto session = boost::make_shared<CStandardSession>(url);

      sendGetRequest(session,
                     CDataContainer(), // no header parameters
                     parameters,
                     [&](CDataContainer& data)
                     {
                        responseData = data;
                     },
                     timeout);

      return responseData;
   }

   bool CHttpMethods::jsonResponseReader(const boost::shared_ptr<IHTTPSession> session,
                                         Poco::Net::HTTPResponse& httpresponse,
                                         CDataContainer& response)
   {
      auto& rs = session->receiveResponse(httpresponse);
      if (boost::icontains(httpresponse.getContentType(), "application/json"))
      {
         // Content-Length is not always fullfilled so we don't use hasContentLength and getContentLength
         const std::istreambuf_iterator<char> eos;
         const std::string content(std::istreambuf_iterator<char>(rs), eos);
         response.deserialize(content);
         return true;
      }
      return false;
   }
} // namespace shared
