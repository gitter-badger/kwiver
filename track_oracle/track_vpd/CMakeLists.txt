#
# VIRAT Public Data track / events
#

set( track_vpd_public_headers
  track_vpd_track.h
  track_vpd_event.h
  file_format_vpd_track.h
  file_format_vpd_event.h
)

set( track_vpd_sources
  track_vpd_track.cxx
  track_vpd_event.cxx
  file_format_vpd_track.cxx
  file_format_vpd_event.cxx
)

kwiver_install_headers(
  ${track_vpd_public_headers}
  SUBDIR        track_oracle/track_vpd
)

kwiver_install_headers(
  ${CMAKE_CURRENT_BINARY_DIR}/track_vpd_export.h
  SUBDIR        track_oracle/track_vpd
  NOPATH
)

kwiver_add_library( track_vpd
  ${track_vpd_public_headers}
  ${track_vpd_sources}
  ${CMAKE_CURRENT_BINARY_DIR}/track_vpd_export.h
)

target_link_libraries( track_vpd
  PUBLIC               track_oracle
                       track_oracle_format_base
                       vgl
  PRIVATE              vital_logger
                       vul
)

