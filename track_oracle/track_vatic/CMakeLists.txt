#
# vatic tracks
#

set( track_vatic_public_headers
  track_vatic.h
  file_format_vatic.h
)

set( track_vatic_sources
  file_format_vatic.cxx
)

kwiver_install_headers(
  ${track_vatic_public_headers}
  SUBDIR        track_oracle/track_vatic
)

kwiver_install_headers(
  ${CMAKE_CURRENT_BINARY_DIR}/track_vatic_export.h
  SUBDIR        track_oracle/track_vatic
  NOPATH
)

kwiver_add_library( track_vatic
  ${track_vatic_public_headers}
  ${track_vatic_sources}
  ${CMAKE_CURRENT_BINARY_DIR}/track_vatic_export.h
)

target_link_libraries( track_vatic
PUBLIC                 track_oracle
                       track_oracle_format_base
                       vgl
                       vital_logger
)
