# CMake generated Testfile for 
# Source directory: /mnt/windows/media/programs/CppBitonic_sort/tests
# Build directory: /mnt/windows/media/programs/CppBitonic_sort/build/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(/mnt/windows/media/programs/CppBitonic_sort/tests/e2e/io/001.dat "bash" "-c" "/mnt/windows/media/programs/CppBitonic_sort/tests/e2e/run.sh /mnt/windows/media/programs/CppBitonic_sort/tests/e2e/io/001.dat ./main")
set_tests_properties(/mnt/windows/media/programs/CppBitonic_sort/tests/e2e/io/001.dat PROPERTIES  DEPENDS "main" WORKING_DIRECTORY "/mnt/windows/media/programs/CppBitonic_sort/build" _BACKTRACE_TRIPLES "/mnt/windows/media/programs/CppBitonic_sort/tests/CMakeLists.txt;8;add_test;/mnt/windows/media/programs/CppBitonic_sort/tests/CMakeLists.txt;0;")
add_test(/mnt/windows/media/programs/CppBitonic_sort/tests/e2e/io/002.dat "bash" "-c" "/mnt/windows/media/programs/CppBitonic_sort/tests/e2e/run.sh /mnt/windows/media/programs/CppBitonic_sort/tests/e2e/io/002.dat ./main")
set_tests_properties(/mnt/windows/media/programs/CppBitonic_sort/tests/e2e/io/002.dat PROPERTIES  DEPENDS "main" WORKING_DIRECTORY "/mnt/windows/media/programs/CppBitonic_sort/build" _BACKTRACE_TRIPLES "/mnt/windows/media/programs/CppBitonic_sort/tests/CMakeLists.txt;8;add_test;/mnt/windows/media/programs/CppBitonic_sort/tests/CMakeLists.txt;0;")
