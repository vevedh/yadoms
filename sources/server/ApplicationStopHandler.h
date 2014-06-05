//
// System signals handler
//
#pragma once

#include <csignal>
#include <shared/event/EventHandler.hpp>

//-----------------------------------------------------------------------------
/// \class              Application stop handler
//-----------------------------------------------------------------------------
class CApplicationStopHandler
{
public:
   //-----------------------------------------------------------------------------
   /// \brief		                     Constructor
   /// \param[in] targetEventHandler   Event handler to notify
   /// \param[in] eventId              Event ID to send when stop occurs
   //-----------------------------------------------------------------------------
   CApplicationStopHandler(shared::event::CEventHandler& targetEventHandler, int eventId);

   //-----------------------------------------------------------------------------
   /// \brief		                     Destructor
   //-----------------------------------------------------------------------------
   ~CApplicationStopHandler();

private:
   //-----------------------------------------------------------------------------
   /// \brief		                     Internal interruption handler
   /// \param[in] signal               Signal source of interruption
   //-----------------------------------------------------------------------------
   static void handleInternal(int signal);

   //-----------------------------------------------------------------------------
   /// \brief		                     The main m_thread method
   //-----------------------------------------------------------------------------
   void doWork();

private:
   //-----------------------------------------------------------------------------
   /// \brief		                     Event handler to notify
   //-----------------------------------------------------------------------------
   shared::event::CEventHandler& m_targetEventHandler;

   //-----------------------------------------------------------------------------
   /// \brief		                     Event ID to send when stop occurs
   //-----------------------------------------------------------------------------
   int m_eventId;

   //-----------------------------------------------------------------------------
   /// \brief		                     The thread waiting for system signals
   //-----------------------------------------------------------------------------
   boost::shared_ptr<boost::thread> m_thread;


   //-----------------------------------------------------------------------------
   /// \brief		                     The flag used between interruption and thread
   //-----------------------------------------------------------------------------
   static volatile sig_atomic_t StopRequested;
};
