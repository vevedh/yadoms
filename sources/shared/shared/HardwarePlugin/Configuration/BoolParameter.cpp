#include "stdafx.h"

#include "BoolParameter.h"

CHardwarePluginConfigurationBoolParameter::CHardwarePluginConfigurationBoolParameter(const std::string& name, const std::string& description, bool defaultValue)
   :CHardwarePluginConfigurationSimpleParameter<bool>("bool", name, description, defaultValue)
{
}

boost::shared_ptr<CHardwarePluginConfigurationParameter> CHardwarePluginConfigurationBoolParameter::clone() const
{
   boost::shared_ptr<CHardwarePluginConfigurationParameter> p(new CHardwarePluginConfigurationBoolParameter(getName(), getDescription(), m_value));
   return p;
}

const std::string CHardwarePluginConfigurationBoolParameter::valueToString(bool current) const
{
   return (current ? m_value : m_defaultValue) ? "true" : "false";
}

void CHardwarePluginConfigurationBoolParameter::valueFromString(const std::string& valueAsString)
{
   m_value = valueAsString == "true";
}
