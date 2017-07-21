#pragma once
#include <shared/Export.h>
#include "SingleHistorizableData.hpp"

namespace shared
{
   namespace plugin
   {
      namespace yPluginApi
      {
         namespace historization
         {
            //-----------------------------------------------------
            ///\brief A color (RGB) historizable object
            //-----------------------------------------------------
            class YADOMS_SHARED_EXPORT CColorRGB : public CSingleHistorizableData<unsigned int>
            {
            public:
               //-----------------------------------------------------
               ///\brief                     Constructor
               ///\param[in] keywordName     Yadoms keyword name
               ///\param[in] accessMode      Access mode
               //-----------------------------------------------------
               CColorRGB(const std::string& keywordName,
                        const EKeywordAccessMode& accessMode);

               //-----------------------------------------------------
               ///\brief                     Destructor
               //-----------------------------------------------------
               virtual ~CColorRGB();
            };
         }
      }
   }
} // namespace shared::plugin::yPluginApi::historization

