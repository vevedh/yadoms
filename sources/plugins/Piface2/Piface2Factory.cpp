#include "stdafx.h"
#include "Piface2Factory.h"
#include "wiringPi.h"
#include <mcp23s17.h>
#include "InitializationException.hpp"
#include <errno.h>
#include <unistd.h>

#define BASE_ADDRESS 16
#define NB_INPUTS  8
#define NB_OUTPUTS 8

static const std::string Model("Piface2");

CPiface2Factory::CPiface2Factory(boost::shared_ptr<yApi::IYPluginApi> api,
                                 const std::string& device,
                                 const IPf2Configuration& configuration,
                                 shared::CDataContainer details)
{
   std::cout << "user euid:" << geteuid() << std::endl;

   // Initializing wiringPi in Gpio mode
   // need root privilege, but needed of pullup or pulldown
   if (wiringPiSetupGpio() ==-1 )
      throw CInitializationException( strerror (errno) );

   //Initializing the component
   mcp23s17Setup( BASE_ADDRESS, 0, 0 );

   // IO Configuration
   for (int counter=0; counter<NB_OUTPUTS; ++counter)
   {
      std::string name = "DO" + boost::lexical_cast<std::string>(counter);
      m_DigitalOutput[counter] = boost::make_shared<CIO>( name, BASE_ADDRESS, counter, EPullResistance::kDisable, yApi::EKeywordAccessMode::kGetSet);
      m_mapKeywordsName[ name ] = m_DigitalOutput[counter];
      m_keywordsToDeclare.push_back(m_DigitalOutput[counter]->historizable());
   }

   for (int counter=0; counter<NB_INPUTS; ++counter)
   {
      std::string name = "DI" + boost::lexical_cast<std::string>(counter);
      m_DigitalInput[counter]  = boost::make_shared<CIO>( name , BASE_ADDRESS+8, counter, configuration.PullResistanceState(counter), yApi::EKeywordAccessMode::kGet);
      m_mapKeywordsName[ name ] = m_DigitalOutput[counter];
      m_keywordsToDeclare.push_back(m_DigitalInput[counter]->historizable());
   }

   //Déclaration of all IOs
   api->declareDevice(device, Model, m_keywordsToDeclare, details);
}

void CPiface2Factory::OnConfigurationUpdate(boost::shared_ptr<yApi::IYPluginApi> api,
                                            const IPf2Configuration& configuration,
                                            shared::CDataContainer details)
{
   for (int counter=0; counter<NB_INPUTS; ++counter)
   {
      std::string name = "DI" + boost::lexical_cast<std::string>(counter);
      m_DigitalInput[counter]->ConfigurePullResistance( configuration.PullResistanceState(counter) );
   }
}

std::map<std::string, boost::shared_ptr<CIO> > CPiface2Factory::getAllDigitalIO(void)
{
   return m_mapKeywordsName;
}

CPiface2Factory::~CPiface2Factory()
{}