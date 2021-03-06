# Build / Install Plugin containing core algorithm implementations

set( plugin_core_headers
  close_loops_bad_frames_only.h
  close_loops_exhaustive.h
  close_loops_keyframe.h
  close_loops_multi_method.h
  compute_ref_homography_core.h
  convert_image_bypass.h
  estimate_canonical_transform.h
  filter_features_magnitude.h
  hierarchical_bundle_adjust.h
  initialize_cameras_landmarks.h
  match_features_fundamental_matrix.h
  match_features_homography.h
  register_algorithms.h
  track_features_core.h
  transform.h
  triangulate_landmarks.h

  epipolar_geometry.h
  interpolate_camera.h
  match_matrix.h
  metrics.h
  projected_track_set.h
  triangulate.h
  )
kwiver_install_headers(
  SUBDIR     arrows/core
  ${plugin_core_headers}
  )
kwiver_install_headers(
  ${CMAKE_CURRENT_BINARY_DIR}/kwiver_algo_export.h
  NOPATH   SUBDIR     arrows/core
  )

set( plugin_core_sources
  close_loops_bad_frames_only.cxx
  close_loops_exhaustive.cxx
  close_loops_keyframe.cxx
  close_loops_multi_method.cxx
  compute_ref_homography_core.cxx
  convert_image_bypass.cxx
  estimate_canonical_transform.cxx
  filter_features_magnitude.cxx
  hierarchical_bundle_adjust.cxx
  initialize_cameras_landmarks.cxx
  match_features_fundamental_matrix.cxx
  match_features_homography.cxx
  register_algorithms.cxx
  track_features_core.cxx
  transform.cxx
  triangulate_landmarks.cxx

  epipolar_geometry.cxx
  interpolate_camera.cxx
  match_matrix.cxx
  metrics.cxx
  projected_track_set.cxx
  triangulate.cxx
  )

# Address MSVC fatal error C1128:
# number of sections exceeded object file format limit
if(${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
  set_source_files_properties(
    triangulate.cxx
    PROPERTIES COMPILE_FLAGS "/bigobj"
    )
endif()

kwiver_add_library( kwiver_algo
  ${plugin_core_headers}
  ${plugin_core_sources}
  )

target_link_libraries( kwiver_algo
  PUBLIC               vital
  )

algorithms_create_plugin( kwiver_algo
  algorithm_plugin_interface.cxx
  )

if (KWIVER_ENABLE_TESTS)
  add_subdirectory(tests)
endif()
