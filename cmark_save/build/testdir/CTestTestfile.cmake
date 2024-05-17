# CMake generated Testfile for 
# Source directory: /home/s22100141/cmark/test
# Build directory: /home/s22100141/cmark/build/testdir
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(html_normalization "/usr/bin/python3.6" "-m" "doctest" "/home/s22100141/cmark/test/normalize.py")
set_tests_properties(html_normalization PROPERTIES  _BACKTRACE_TRIPLES "/home/s22100141/cmark/test/CMakeLists.txt;24;add_test;/home/s22100141/cmark/test/CMakeLists.txt;0;")
add_test(spectest_executable "/usr/bin/python3.6" "/home/s22100141/cmark/test/spec_tests.py" "--no-normalize" "--spec" "/home/s22100141/cmark/test/spec.txt" "--program" "/home/s22100141/cmark/build/src/cmark")
set_tests_properties(spectest_executable PROPERTIES  _BACKTRACE_TRIPLES "/home/s22100141/cmark/test/CMakeLists.txt;48;add_test;/home/s22100141/cmark/test/CMakeLists.txt;0;")
add_test(smartpuncttest_executable "/usr/bin/python3.6" "/home/s22100141/cmark/test/spec_tests.py" "--no-normalize" "--spec" "/home/s22100141/cmark/test/smart_punct.txt" "--program" "/home/s22100141/cmark/build/src/cmark --smart")
set_tests_properties(smartpuncttest_executable PROPERTIES  _BACKTRACE_TRIPLES "/home/s22100141/cmark/test/CMakeLists.txt;54;add_test;/home/s22100141/cmark/test/CMakeLists.txt;0;")
add_test(regressiontest_executable "/usr/bin/python3.6" "/home/s22100141/cmark/test/spec_tests.py" "--no-normalize" "--spec" "/home/s22100141/cmark/test/regression.txt" "--program" "/home/s22100141/cmark/build/src/cmark")
set_tests_properties(regressiontest_executable PROPERTIES  _BACKTRACE_TRIPLES "/home/s22100141/cmark/test/CMakeLists.txt;60;add_test;/home/s22100141/cmark/test/CMakeLists.txt;0;")
