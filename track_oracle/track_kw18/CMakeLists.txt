#
# kw18 tracks
#

set( track_kw18_public_headers
  track_kw18.h
  file_format_kw18.h
)

set( track_kw18_sources
  file_format_kw18.cxx
)

kwiver_install_headers(
  ${track_kw18_public_headers}
  SUBDIR     track_oracle/track_kw18
)

kwiver_install_headers(
  ${CMAKE_CURRENT_BINARY_DIR}/track_kw18_export.h
  SUBDIR     track_oracle/track_kw18
  NOPATH
)

kwiver_add_library( track_kw18
  ${track_kw18_public_headers}
  ${track_kw18_sources}
  ${CMAKE_CURRENT_BINARY_DIR}/track_kw18_export.h
)

target_link_libraries( track_kw18
  PUBLIC               track_oracle
                       data_terms
  PRIVATE              vital_logger
                       vul
                       vgl
                       track_oracle_format_base
)
