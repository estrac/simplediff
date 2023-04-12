# Non-digit tests ===============================================================
file (COPY . DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_test(NAME test1
         COMMAND ${CMAKE_BINARY_DIR}/bin/simplediff test_base.txt test1.txt -v
         )

add_test(NAME test2
         COMMAND ${CMAKE_BINARY_DIR}/bin/simplediff test_base.txt test2.txt -v
         )
set_property(TEST test2 PROPERTY WILL_FAIL TRUE)

add_test(NAME test3
         COMMAND ${CMAKE_BINARY_DIR}/bin/simplediff test_base.txt test3.txt -v
         )
set_property(TEST test3 PROPERTY WILL_FAIL TRUE)

# Digit tests ===================================================================
add_test(NAME test4
         COMMAND ${CMAKE_BINARY_DIR}/bin/simplediff digits_base.txt digits1.txt -v
         )

add_test(NAME test5
         COMMAND ${CMAKE_BINARY_DIR}/bin/simplediff digits_base.txt digits2.txt -v
         )
set_property(TEST test5 PROPERTY WILL_FAIL TRUE)

add_test(NAME test6
         COMMAND ${CMAKE_BINARY_DIR}/bin/simplediff digits_base.txt digits3.txt -v
         )
set_property(TEST test6 PROPERTY WILL_FAIL TRUE)

if (MSVC)
    # Create target to run tests from Visual Studio
    add_custom_target(Tests
                      COMMAND ${CMAKE_CTEST_COMMAND}
                      -C $<CONFIGURATION> --force-new-ctest-process
                      WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
                      )
endif ()
