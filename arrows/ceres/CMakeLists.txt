# Build / Install plugin containing Ceres algorithm implementations + support
# structures

set( ceres_headers_public
  bundle_adjust.h
  lens_distortion.h
  register_algorithms.h
  reprojection_error.h
  )
set( ceres_headers_private
  types.h
  )

kwiver_install_headers(
  SUBDIR     arrows/ceres
  ${ceres_headers_public}
  )

kwiver_install_headers(
  ${CMAKE_CURRENT_BINARY_DIR}/kwiver_algo_ceres_export.h
  NOPATH   SUBDIR     arrows/ceres
  )

set( ceres_sources
  bundle_adjust.cxx
  register_algorithms.cxx
  types.cxx
  )

kwiver_add_library( kwiver_algo_ceres
  ${ceres_headers_public}
  ${ceres_headers_private}
  ${ceres_sources}
  )
target_link_libraries( kwiver_algo_ceres
  PUBLIC               kwiver_algo
  PRIVATE              ceres
  )

algorithms_create_plugin( kwiver_algo_ceres
  algorithm_plugin_interface.cxx
  )

if (KWIVER_ENABLE_TESTS)
  add_subdirectory(tests)
endif()
