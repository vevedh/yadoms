#include "stdafx.h"
#include "DiskUsage.h"
#include <shared/Log.h>
#include <shared/exception/Exception.hpp>

CDiskUsage::CDiskUsage(const std::string & device, const std::string & keywordName, const std::string & driveName)
   :m_device(device), 
    m_keyword( new yApi::historization::CLoad(keywordName) ), 
    m_driveName(driveName)
{}

CDiskUsage::~CDiskUsage()
{}

void CDiskUsage::declareKeywords(boost::shared_ptr<yApi::IYPluginApi> context, shared::CDataContainer details)
{
	if (!context->keywordExists( m_device, m_keyword->getKeyword()))
       context->declareKeyword(m_device, *m_keyword, details);
}

void CDiskUsage::historizeData(boost::shared_ptr<yApi::IYPluginApi> context) const
{
   if (!context)
      throw shared::exception::CException("context must be defined");

   context->historizeData(m_device, *m_keyword);
}

void CDiskUsage::read()
{
   ULARGE_INTEGER FreeSpaceAvailable, TotalSpace, TotalFreeSpaceAvailable;

   if (!GetDiskFreeSpaceEx(m_driveName.c_str(), &FreeSpaceAvailable, &TotalSpace, &TotalFreeSpaceAvailable))
   {
      std::stringstream Message;
      Message << "GetDiskFreeSpaceEx return an error : ";
      Message << GetLastError();
      throw shared::exception::CException ( Message.str() );
   }

   float DiskUsage = (float) floor((1 - (float) FreeSpaceAvailable.QuadPart / TotalSpace.QuadPart) * 1000) /10;

   m_keyword->set( DiskUsage );

   YADOMS_LOG(debug) << m_driveName << " Disk Usage : " << m_keyword->formatValue();
}

boost::shared_ptr<yApi::historization::IHistorizable> CDiskUsage::GetHistorizable() const
{
	return m_keyword;
}
