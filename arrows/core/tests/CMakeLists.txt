project(arrows_test_core)

include(kwiver-test-setup)

set( test_libraries    kwiver_algo vital vital_apm )

##############################
# Algorithms core plugin tests
##############################
kwiver_discover_tests(core_triangulate_landmarks        test_libraries test_triangulate_landmarks.cxx)
kwiver_discover_tests(core_epipolar_geometry            test_libraries test_epipolar_geometry.cxx)
kwiver_discover_tests(core_interpolate_camera           test_libraries test_interpolate_camera.cxx)
