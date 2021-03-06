
MACRO(ADD_VS_NATVIS _targetName)

   if (MSVC)
      target_sources(${_targetName} INTERFACE ${PROJECT_SOURCE_DIR}/../ideTools/debugTools/boost.natvis)
      target_sources(${_targetName} INTERFACE ${PROJECT_SOURCE_DIR}/../ideTools/debugTools/boost_Containers.natvis)
      target_sources(${_targetName} INTERFACE ${PROJECT_SOURCE_DIR}/../ideTools/debugTools/boost_DateTime.natvis)
      target_sources(${_targetName} INTERFACE ${PROJECT_SOURCE_DIR}/../ideTools/debugTools/boost_Geometry.natvis)
      target_sources(${_targetName} INTERFACE ${PROJECT_SOURCE_DIR}/../ideTools/debugTools/boost_Gil.natvis)
      target_sources(${_targetName} INTERFACE ${PROJECT_SOURCE_DIR}/../ideTools/debugTools/boost_IntrusiveContainers.natvis)
      target_sources(${_targetName} INTERFACE ${PROJECT_SOURCE_DIR}/../ideTools/debugTools/boost_MultiArray.natvis)
      target_sources(${_targetName} INTERFACE ${PROJECT_SOURCE_DIR}/../ideTools/debugTools/boost_MultiIndex.natvis)
      target_sources(${_targetName} INTERFACE ${PROJECT_SOURCE_DIR}/../ideTools/debugTools/boost_Multiprecision.natvis)
      target_sources(${_targetName} INTERFACE ${PROJECT_SOURCE_DIR}/../ideTools/debugTools/boost_PointerContainerLibrary.natvis)
      target_sources(${_targetName} INTERFACE ${PROJECT_SOURCE_DIR}/../ideTools/debugTools/boost_PropertyTree.natvis)
      target_sources(${_targetName} INTERFACE ${PROJECT_SOURCE_DIR}/../ideTools/debugTools/boost_Rational.natvis)
      target_sources(${_targetName} INTERFACE ${PROJECT_SOURCE_DIR}/../ideTools/debugTools/boost_Regex.natvis)
      target_sources(${_targetName} INTERFACE ${PROJECT_SOURCE_DIR}/../ideTools/debugTools/boost_SmartPointers.natvis)
      target_sources(${_targetName} INTERFACE ${PROJECT_SOURCE_DIR}/../ideTools/debugTools/boost_uBLAS.natvis)
      target_sources(${_targetName} INTERFACE ${PROJECT_SOURCE_DIR}/../ideTools/debugTools/boost_Unordered.natvis)
      target_sources(${_targetName} INTERFACE ${PROJECT_SOURCE_DIR}/../ideTools/debugTools/boost_Variant.natvis)
      
      source_group(vsHelpers  ${PROJECT_SOURCE_DIR}/../ideTools/debugTools/*.*)
   endif()

ENDMACRO()

