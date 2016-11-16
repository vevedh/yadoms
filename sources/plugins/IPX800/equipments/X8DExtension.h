#pragma once

#include <shared/plugin/yPluginApi/IYPluginApi.h>
#include "IEquipment.h"
#include "../specificHistorizers/inputOutput.h"

// Shortcut to yPluginApi namespace
namespace yApi = shared::plugin::yPluginApi;

#define X8D_DI_QTY 8

namespace equipments
{
   //-----------------------------------------------------
   ///\brief X8-D Extension
   //-----------------------------------------------------
   class CX8DExtension : public IEquipment
   {
   public:
      //-----------------------------------------------------
      ///\brief                     Constructor
      ///\param[in] keywordName     Yadoms keyword name
      //-----------------------------------------------------
      CX8DExtension(boost::shared_ptr<yApi::IYPluginApi> api,
                    const std::string& device,
                    const int position);

      // IExtension implementation
      std::string getDeviceName() const override;
      std::string getDeviceType() const override;
      int getSlot() const override;
      void historizePendingCommand(boost::shared_ptr<yApi::IYPluginApi> api, boost::shared_ptr<const yApi::IDeviceCommand> command) override;
      void updateFromDevice(const std::string& type, boost::shared_ptr<yApi::IYPluginApi> api, shared::CDataContainer& values, bool forceHistorization = false) override;
      shared::CDataContainer buildMessageToDevice(boost::shared_ptr<yApi::IYPluginApi> api, shared::CDataContainer& parameters, boost::shared_ptr<const yApi::IDeviceCommand> command) override;
      // [END] IExtension implementation

      //-----------------------------------------------------
      ///\brief                     Destructor
      //-----------------------------------------------------
      virtual ~CX8DExtension();

   private:

      //-----------------------------------------------------
      ///\brief                     The device name
      //-----------------------------------------------------
      std::string m_deviceName;

      //-----------------------------------------------------
      ///\brief                     The device type
      //-----------------------------------------------------
      std::string m_deviceType;

      //-----------------------------------------------------
      ///\brief                     The slot position
      //-----------------------------------------------------
      int m_position;

      //-----------------------------------------------------
      ///\brief                     The list of keyword
      //-----------------------------------------------------
      std::vector<boost::shared_ptr<specificHistorizers::CInputOuput> > m_keywordList;
   };
} // namespace equipments