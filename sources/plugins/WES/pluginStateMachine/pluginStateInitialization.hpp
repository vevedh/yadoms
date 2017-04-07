#pragma once
#include <boost/msm/front/euml/euml.hpp>
#include <boost/msm/front/euml/state_grammar.hpp>
#include <boost/msm/back/state_machine.hpp>

#include <shared/plugin/yPluginApi/IYPluginApi.h>
#include <shared/Log.h>
#include "pluginStateCommonDeclaration.hpp"


// Shortcut to yPluginApi namespace
namespace yApi = shared::plugin::yPluginApi;

namespace msm = boost::msm;
using namespace boost::msm::front::euml;

//--------------------------------------------------------------
/// \brief	D�claration de l'�tat initialization
/// \note   
//--------------------------------------------------------------

BOOST_MSM_EUML_ACTION(pluginInitializationEntryState)
{
   template <class Evt, class Fsm, class State>
   void operator()(Evt const& evt, Fsm& stateMachine, State&)
   {
      auto api = evt.get_attribute(m_pluginApi);
      auto configuration = pluginInitialization.get_attribute(m_configuration);
      auto factory = evt.get_attribute(m_factory);
      auto refreshTimer = pluginFaulty.get_attribute(m_refreshTimer);

      api->setPluginState(yApi::historization::EPluginState::kCustom, "initialization");
      factory->loadConfiguration(api, configuration);

      // Create the timer for refresh IOs
      refreshTimer = api->getEventHandler().createTimer(kRefreshStatesReceived, shared::event::CEventTimer::kPeriodic, boost::posix_time::seconds(10));

      if (factory->getMasterEquipment() == 0)
         stateMachine.enqueue_event(EvtInitializedNoEquipment(api));
      else
         stateMachine.enqueue_event(EvtInitialized(api, factory));
   }

   template <class Evt, class Fsm, class State>
   void exception_caught(Evt const& evt, Fsm&, std::exception&)
   {
      auto api = evt.get_attribute(m_pluginApi);

      api->setPluginState(yApi::historization::EPluginState::kCustom, "initializationError");
      YADOMS_LOG(error) << "WES plugin initialization error...";
   }
};

BOOST_MSM_EUML_STATE((pluginInitializationEntryState,
                      no_action,
                      attributes_ << m_configuration << m_refreshTimer,
                      configure_ << no_configure_),
                     pluginInitialization);