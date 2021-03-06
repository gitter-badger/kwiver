# C interface library

set(vital_c_public_headers
  algorithm.h
  algorithm_plugin_manager.h

  common.h
  config_block.h
  error_handle.h

  algo_def/convert_image.h
  algo_def/image_io.h
  algo_def/track_features.h

  types/camera.h
  types/camera_intrinsics.h
  types/camera_map.h
  types/color.h
  types/covariance.h
  types/descriptor.h
  types/eigen.h
  types/feature.h
  types/image.h
  types/image_container.h
  types/image_container.hxx
  types/rotation.h
  types/track.h
  types/track_set.h
  )

set(vital_c_private_headers
  # Created by CMake during configuration
  ${CMAKE_CURRENT_BINARY_DIR}/vital_c_export.h
  helpers/algorithm.h
  helpers/c_utils.h
  helpers/camera.h
  helpers/camera_intrinsics.h
  helpers/camera_map.h
  helpers/config_block.h
  helpers/descriptor.h
  helpers/image_container.h
  helpers/track.h
  helpers/track_set.h
  )

set(vital_c_sources
  algorithm.cxx
  algorithm_plugin_manager.cxx
  common.cxx
  config_block.cxx
  error_handle.cxx

  algo_def/convert_image.cxx
  algo_def/image_io.cxx
  algo_def/track_features.cxx

  helpers/c_utils.cxx

  types/camera.cxx
  types/camera_intrinsics.cxx
  types/camera_map.cxx
  types/color.cxx
  types/covariance.cxx
  types/descriptor.cxx
  types/eigen.cxx
  types/feature.cxx
  types/image.cxx
  types/image_container.cxx
  types/rotation.cxx
  types/track.cxx
  types/track_set.cxx
  )

kwiver_install_headers(
  ${vital_c_public_headers}
  SUBDIR     vital/bindings/c
  )

kwiver_install_headers(
  ${CMAKE_CURRENT_BINARY_DIR}/vital_c_export.h
  SUBDIR     vital/bindings/c
  NOPATH
  )

kwiver_add_library( vital_c
  ${vital_c_public_headers}
  ${vital_c_private_headers}
  ${vital_c_sources}
  )

target_link_libraries( vital_c
  PRIVATE     vital
              vital_apm
  )
