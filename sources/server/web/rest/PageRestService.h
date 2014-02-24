﻿#pragma once

#include "IRestService.h"
#include "database/IDataProvider.h"

class CPageRestService : public IRestService
{
public:
   CPageRestService(boost::shared_ptr<database::IDataProvider> dataProvider);
   virtual ~CPageRestService();

public:
    // IRestService implementation
   virtual void configureDispatcher(CRestDispatcher & dispatcher);
   // [END] IRestService implementation

   static const std::string & getRestKeyword();
   CJson getOnePage(const std::vector<std::string> & parameters, const CJson & requestContent);   
   CJson getAllPages(const std::vector<std::string> & parameters, const CJson & requestContent);  
   CJson getPageWidget(const std::vector<std::string> & parameters, const CJson & requestContent);   

   CJson addPage(const std::vector<std::string> & parameters, const CJson & requestContent);   
   CJson updatePage(const std::vector<std::string> & parameters, const CJson & requestContent);   
   CJson updateAllPages(const std::vector<std::string> & parameters, const CJson & requestContent);   
   CJson deletePage(const std::vector<std::string> & parameters, const CJson & requestContent);   
   CJson deleteAllPages(const std::vector<std::string> & parameters, const CJson & requestContent);   


   CJson addWidgetForPage(const std::vector<std::string> & parameters, const CJson & requestContent);   
   CJson replaceAllWidgetsForPage(const std::vector<std::string> & parameters, const CJson & requestContent);   
   CJson deleteAllWidgetsForPage(const std::vector<std::string> & parameters, const CJson & requestContent);   

   CJson transactionalMethod(CRestDispatcher::CRestMethodHandler realMethod, const std::vector<std::string> & parameters, const CJson & requestContent);

private:
   boost::shared_ptr<database::IDataProvider> m_dataProvider;
   static std::string m_restKeyword;
};