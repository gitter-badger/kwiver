project(kwiver_util_tests)

include(kwiver-test-setup)

set( test_libraries vital vital_apm kwiversys )

##############################
# Util tests
##############################

kwiver_discover_tests(util_timer             test_libraries test_timer.cxx)
kwiver_discover_tests(util_any_converter     test_libraries test_any_convert.cxx)
