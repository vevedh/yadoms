#pragma once
#include "IUpdateChecker.h"
#include "shared/event/EventHandler.hpp"
#include "pluginSystem/IFactory.h"
#include "pluginSystem/Manager.h"

namespace update
{
   namespace worker
   {
      class CUpdateChecker : public IUpdateChecker
      {
      public:
         CUpdateChecker(const boost::posix_time::time_duration firstScanDelay,
                        const boost::posix_time::time_duration nextScanDelays,
                        boost::shared_ptr<pluginSystem::CManager> pluginManager,
                        boost::shared_ptr<dataAccessLayer::IEventLogger> eventLogger,
            bool developerMode);
         virtual ~CUpdateChecker();

         // IUpdateChecker Implementation
         void forceRebuildUpdates() override;
         shared::CDataContainer getUpdates(bool includePreleases) const override;
         // [END] IUpdateChecker Implementation

      protected:
         void doWork(const boost::posix_time::time_duration firstScanDelay,
                     const boost::posix_time::time_duration nextScanDelays);
         void scan();
         shared::CDataContainer buildUpdates(bool includePreleases,
                                             const pluginSystem::IFactory::AvailablePluginMap& pluginsLocalVersions,
                                             const shared::CDataContainer& pluginsAvailableVersions);
         shared::CDataContainer buildPluginList(const pluginSystem::IFactory::AvailablePluginMap& localVersions,
                                                const shared::CDataContainer& availableVersions,
                                                bool includePreleases);

      private:
         boost::shared_ptr<pluginSystem::CManager> m_pluginManager;
         boost::shared_ptr<dataAccessLayer::IEventLogger> m_eventLogger;
         bool m_developerMode;

         boost::thread m_thread;
         shared::event::CEventHandler m_evtHandler;

         mutable boost::recursive_mutex m_updateMutex;
         shared::CDataContainer m_allUpdates;
         shared::CDataContainer m_releasesOnlyUpdates;
         bool m_updatesAvailable;
      };
   } // namespace worker
} // namespace update
