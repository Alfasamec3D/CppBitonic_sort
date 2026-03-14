enable_testing()

find_program(BASH_EXECUTABLE bash REQUIRED)
file (GLOB testfiles "e2e/io/*.dat")
foreach (file ${testfiles})
    add_test(NAME ${file} 
        #COMMAND ${BASH_EXECUTABLE} 
        #       e2e/run.sh 
        #      "${file}" "$<TARGET_FILE:main>" 
        COMMAND bash -c "${CMAKE_SOURCE_DIR}/tests/e2e/run.sh ${file} ./main"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        
)
set_tests_properties(${file} PROPERTIES DEPENDS main)
endforeach()