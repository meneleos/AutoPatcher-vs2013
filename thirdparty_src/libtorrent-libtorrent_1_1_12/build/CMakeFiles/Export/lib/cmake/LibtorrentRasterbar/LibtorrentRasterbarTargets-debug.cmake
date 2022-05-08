#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "LibtorrentRasterbar::torrent-rasterbar" for configuration "Debug"
set_property(TARGET LibtorrentRasterbar::torrent-rasterbar APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(LibtorrentRasterbar::torrent-rasterbar PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/torrent-rasterbar.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/torrent-rasterbar.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS LibtorrentRasterbar::torrent-rasterbar )
list(APPEND _IMPORT_CHECK_FILES_FOR_LibtorrentRasterbar::torrent-rasterbar "${_IMPORT_PREFIX}/lib/torrent-rasterbar.lib" "${_IMPORT_PREFIX}/bin/torrent-rasterbar.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
