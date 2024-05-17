#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "cmark::cmark_exe" for configuration "Release"
set_property(TARGET cmark::cmark_exe APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(cmark::cmark_exe PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/cmark"
  )

list(APPEND _IMPORT_CHECK_TARGETS cmark::cmark_exe )
list(APPEND _IMPORT_CHECK_FILES_FOR_cmark::cmark_exe "${_IMPORT_PREFIX}/bin/cmark" )

# Import target "cmark::cmark" for configuration "Release"
set_property(TARGET cmark::cmark APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(cmark::cmark PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libcmark.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS cmark::cmark )
list(APPEND _IMPORT_CHECK_FILES_FOR_cmark::cmark "${_IMPORT_PREFIX}/lib/libcmark.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
