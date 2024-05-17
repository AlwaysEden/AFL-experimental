# CMake generated Testfile for 
# Source directory: /home/s22100141/AFLplusplus-experimental/cJSON
# Build directory: /home/s22100141/AFLplusplus-experimental/cJSON/fuzzing/afl-build-suppress1
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(cJSON_test "/home/s22100141/AFLplusplus-experimental/cJSON/fuzzing/afl-build-suppress1/cJSON_test")
set_tests_properties(cJSON_test PROPERTIES  _BACKTRACE_TRIPLES "/home/s22100141/AFLplusplus-experimental/cJSON/CMakeLists.txt;248;add_test;/home/s22100141/AFLplusplus-experimental/cJSON/CMakeLists.txt;0;")
subdirs("tests")
subdirs("fuzzing")
