#pragma once

#include "entities/Device.h"


namespace database { 


   class IDeviceRequester
   {
   public:
      //--------------------------------------------------------------
      /// \brief           Add new device 
      /// \param [in]      newDevice   New device informations
      /// \return          deviceId generated by the database
      /// \throw           shared::exception::CEmptyResult if fails
      //--------------------------------------------------------------
      virtual int addDevice(boost::shared_ptr<entities::CDevice> newDevice) = 0;

      //--------------------------------------------------------------
      /// \brief                 Get device informations
      /// \param [in] deviceId   Device Id
      /// \throw                 CInvalidParameterException if deviceId is unknown
      //--------------------------------------------------------------
      virtual boost::shared_ptr<entities::CDevice> getDevice(int deviceId) = 0;

      //--------------------------------------------------------------
      /// \brief           List all devices
      /// \return          List of registered devices
      //--------------------------------------------------------------
      virtual std::vector<boost::shared_ptr<entities::CDevice> > getDevices() = 0;

      //--------------------------------------------------------------
      /// \brief           Update device informations
      /// \param [in]      deviceId   Device  Id
      /// \param [in]      newConfiguration   New configuration
      /// \throw           shared::exception::CEmptyResult if fails
      //--------------------------------------------------------------
      virtual void updateDeviceConfiguration(int deviceId, const std::string& newConfiguration) = 0;

      //--------------------------------------------------------------
      /// \brief           Remove device 
      /// \param [in] deviceId   Device  Id
      /// \throw           shared::exception::CEmptyResult if fails
      //--------------------------------------------------------------
      virtual void removeDevice(int deviceId) = 0;

      //--------------------------------------------------------------
      /// \brief       Destructor
      //--------------------------------------------------------------
      virtual ~IDeviceRequester()
      {
      }
   };

 
} //namespace database 
   