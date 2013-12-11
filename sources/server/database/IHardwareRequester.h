#pragma once

#include "entities/Hardware.h"

class IHardwareRequester
{
public:
   //--------------------------------------------------------------
   /// \brief           Add new hardware plugin instance
   /// \param [in] newHardware   New hardware informations
   //--------------------------------------------------------------
   virtual bool addHardware(boost::shared_ptr<CHardware> newHardware) = 0;

   //--------------------------------------------------------------
   /// \brief           Get hardware informations
   /// \param [in] hardwareId   Hardware plugin instance Id
   /// \throw           std::invalid_argument if hardwareId is unknown
   //--------------------------------------------------------------
   virtual boost::shared_ptr<CHardware> getHardware(int hardwareId) = 0;

   //--------------------------------------------------------------
   /// \brief           List all hardware plugin instances
   /// \return          List of registered plugin instances
   //--------------------------------------------------------------
   virtual std::vector<boost::shared_ptr<CHardware> > getHardwares() = 0;

   //--------------------------------------------------------------
   /// \brief           Update hardware informations
   /// \param [in] hardware   Hardware to update
   //--------------------------------------------------------------
   virtual bool updateHardware(boost::shared_ptr<CHardware> hardware) = 0;

   //--------------------------------------------------------------
   /// \brief           Remove hardware plugin instance
   /// \param [in] hardwareId   Hardware plugin instance Id
   //--------------------------------------------------------------
   virtual bool removeHardware(int hardwareId) = 0;

public:
   virtual ~IHardwareRequester()
   {
   }
};
