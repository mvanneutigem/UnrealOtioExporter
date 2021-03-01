#----------------------------------------------------------------
# Generated CMake target import file for configuration "RelWithDebInfo".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "OTIO::opentimelineio" for configuration "RelWithDebInfo"
set_property(TARGET OTIO::opentimelineio APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(OTIO::opentimelineio PROPERTIES
  IMPORTED_IMPLIB_RELWITHDEBINFO "/opentimelineio/opentimelineio.lib"
  IMPORTED_LOCATION_RELWITHDEBINFO "/opentimelineio/opentimelineio.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS OTIO::opentimelineio )
list(APPEND _IMPORT_CHECK_FILES_FOR_OTIO::opentimelineio "/opentimelineio/opentimelineio.lib" "/opentimelineio/opentimelineio.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
