#include "stdafx.h"
#include "Uv.h"
#include "../StandardCapacities.h"

namespace shared { namespace plugin { namespace yadomsApi { namespace historization
{

CUv::CUv(const std::string& keywordName, const EMeasureType& measureType)
   :CSingleHistorizableData<double>(keywordName, CStandardCapacities::Uv, "uv", 0.0, measureType)
{
}

CUv::~CUv()
{
}

} } } } // namespace shared::plugin::yadomsApi::historization

