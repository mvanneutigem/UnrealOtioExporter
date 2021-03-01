# Install script for directory: C:/code/OpenTimelineIO/src/opentimelineio

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Users/Marieke/CMakeBuilds/214f8a8b-7066-c33b-bb58-4d17ce832417/install/x64-Release")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "RelWithDebInfo")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/opentimelineio/cxx-sdk/include/opentimelineio/any.h;/opentimelineio/cxx-sdk/include/opentimelineio/anyDictionary.h;/opentimelineio/cxx-sdk/include/opentimelineio/anyVector.h;/opentimelineio/cxx-sdk/include/opentimelineio/clip.h;/opentimelineio/cxx-sdk/include/opentimelineio/composable.h;/opentimelineio/cxx-sdk/include/opentimelineio/composition.h;/opentimelineio/cxx-sdk/include/opentimelineio/deserialization.h;/opentimelineio/cxx-sdk/include/opentimelineio/effect.h;/opentimelineio/cxx-sdk/include/opentimelineio/errorStatus.h;/opentimelineio/cxx-sdk/include/opentimelineio/externalReference.h;/opentimelineio/cxx-sdk/include/opentimelineio/freezeFrame.h;/opentimelineio/cxx-sdk/include/opentimelineio/gap.h;/opentimelineio/cxx-sdk/include/opentimelineio/generatorReference.h;/opentimelineio/cxx-sdk/include/opentimelineio/imageSequenceReference.h;/opentimelineio/cxx-sdk/include/opentimelineio/item.h;/opentimelineio/cxx-sdk/include/opentimelineio/linearTimeWarp.h;/opentimelineio/cxx-sdk/include/opentimelineio/marker.h;/opentimelineio/cxx-sdk/include/opentimelineio/mediaReference.h;/opentimelineio/cxx-sdk/include/opentimelineio/missingReference.h;/opentimelineio/cxx-sdk/include/opentimelineio/optional.h;/opentimelineio/cxx-sdk/include/opentimelineio/safely_typed_any.h;/opentimelineio/cxx-sdk/include/opentimelineio/serializableCollection.h;/opentimelineio/cxx-sdk/include/opentimelineio/serializableObject.h;/opentimelineio/cxx-sdk/include/opentimelineio/serializableObjectWithMetadata.h;/opentimelineio/cxx-sdk/include/opentimelineio/serialization.h;/opentimelineio/cxx-sdk/include/opentimelineio/stack.h;/opentimelineio/cxx-sdk/include/opentimelineio/stackAlgorithm.h;/opentimelineio/cxx-sdk/include/opentimelineio/stringUtils.h;/opentimelineio/cxx-sdk/include/opentimelineio/timeEffect.h;/opentimelineio/cxx-sdk/include/opentimelineio/timeline.h;/opentimelineio/cxx-sdk/include/opentimelineio/track.h;/opentimelineio/cxx-sdk/include/opentimelineio/trackAlgorithm.h;/opentimelineio/cxx-sdk/include/opentimelineio/transition.h;/opentimelineio/cxx-sdk/include/opentimelineio/typeRegistry.h;/opentimelineio/cxx-sdk/include/opentimelineio/unknownSchema.h;/opentimelineio/cxx-sdk/include/opentimelineio/vectorIndexing.h;/opentimelineio/cxx-sdk/include/opentimelineio/version.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/opentimelineio/cxx-sdk/include/opentimelineio" TYPE FILE FILES
    "C:/code/OpenTimelineIO/src/opentimelineio/any.h"
    "C:/code/OpenTimelineIO/src/opentimelineio/anyDictionary.h"
    "C:/code/OpenTimelineIO/src/opentimelineio/anyVector.h"
    "C:/code/OpenTimelineIO/src/opentimelineio/clip.h"
    "C:/code/OpenTimelineIO/src/opentimelineio/composable.h"
    "C:/code/OpenTimelineIO/src/opentimelineio/composition.h"
    "C:/code/OpenTimelineIO/src/opentimelineio/deserialization.h"
    "C:/code/OpenTimelineIO/src/opentimelineio/effect.h"
    "C:/code/OpenTimelineIO/src/opentimelineio/errorStatus.h"
    "C:/code/OpenTimelineIO/src/opentimelineio/externalReference.h"
    "C:/code/OpenTimelineIO/src/opentimelineio/freezeFrame.h"
    "C:/code/OpenTimelineIO/src/opentimelineio/gap.h"
    "C:/code/OpenTimelineIO/src/opentimelineio/generatorReference.h"
    "C:/code/OpenTimelineIO/src/opentimelineio/imageSequenceReference.h"
    "C:/code/OpenTimelineIO/src/opentimelineio/item.h"
    "C:/code/OpenTimelineIO/src/opentimelineio/linearTimeWarp.h"
    "C:/code/OpenTimelineIO/src/opentimelineio/marker.h"
    "C:/code/OpenTimelineIO/src/opentimelineio/mediaReference.h"
    "C:/code/OpenTimelineIO/src/opentimelineio/missingReference.h"
    "C:/code/OpenTimelineIO/src/opentimelineio/optional.h"
    "C:/code/OpenTimelineIO/src/opentimelineio/safely_typed_any.h"
    "C:/code/OpenTimelineIO/src/opentimelineio/serializableCollection.h"
    "C:/code/OpenTimelineIO/src/opentimelineio/serializableObject.h"
    "C:/code/OpenTimelineIO/src/opentimelineio/serializableObjectWithMetadata.h"
    "C:/code/OpenTimelineIO/src/opentimelineio/serialization.h"
    "C:/code/OpenTimelineIO/src/opentimelineio/stack.h"
    "C:/code/OpenTimelineIO/src/opentimelineio/stackAlgorithm.h"
    "C:/code/OpenTimelineIO/src/opentimelineio/stringUtils.h"
    "C:/code/OpenTimelineIO/src/opentimelineio/timeEffect.h"
    "C:/code/OpenTimelineIO/src/opentimelineio/timeline.h"
    "C:/code/OpenTimelineIO/src/opentimelineio/track.h"
    "C:/code/OpenTimelineIO/src/opentimelineio/trackAlgorithm.h"
    "C:/code/OpenTimelineIO/src/opentimelineio/transition.h"
    "C:/code/OpenTimelineIO/src/opentimelineio/typeRegistry.h"
    "C:/code/OpenTimelineIO/src/opentimelineio/unknownSchema.h"
    "C:/code/OpenTimelineIO/src/opentimelineio/vectorIndexing.h"
    "C:/code/OpenTimelineIO/src/opentimelineio/version.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/opentimelineio/opentimelineio.lib")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/opentimelineio" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/Marieke/CMakeBuilds/214f8a8b-7066-c33b-bb58-4d17ce832417/build/x64-Release/src/opentimelineio/opentimelineio.lib")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/opentimelineio/opentimelineio.dll")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/opentimelineio" TYPE SHARED_LIBRARY FILES "C:/Users/Marieke/CMakeBuilds/214f8a8b-7066-c33b-bb58-4d17ce832417/build/x64-Release/src/opentimelineio/opentimelineio.dll")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/opentimelineio/cxx-sdk/OpenTimelineIOConfig.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}/opentimelineio/cxx-sdk/OpenTimelineIOConfig.cmake"
         "C:/Users/Marieke/CMakeBuilds/214f8a8b-7066-c33b-bb58-4d17ce832417/build/x64-Release/src/opentimelineio/CMakeFiles/Export/_opentimelineio/cxx-sdk/OpenTimelineIOConfig.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}/opentimelineio/cxx-sdk/OpenTimelineIOConfig-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}/opentimelineio/cxx-sdk/OpenTimelineIOConfig.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/opentimelineio/cxx-sdk/OpenTimelineIOConfig.cmake")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/opentimelineio/cxx-sdk" TYPE FILE FILES "C:/Users/Marieke/CMakeBuilds/214f8a8b-7066-c33b-bb58-4d17ce832417/build/x64-Release/src/opentimelineio/CMakeFiles/Export/_opentimelineio/cxx-sdk/OpenTimelineIOConfig.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "/opentimelineio/cxx-sdk/OpenTimelineIOConfig-relwithdebinfo.cmake")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
file(INSTALL DESTINATION "/opentimelineio/cxx-sdk" TYPE FILE FILES "C:/Users/Marieke/CMakeBuilds/214f8a8b-7066-c33b-bb58-4d17ce832417/build/x64-Release/src/opentimelineio/CMakeFiles/Export/_opentimelineio/cxx-sdk/OpenTimelineIOConfig-relwithdebinfo.cmake")
  endif()
endif()

