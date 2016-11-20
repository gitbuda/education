find_package(Threads REQUIRED)

file(GLOB_RECURSE ALL_UNIT_CPP *.cpp)

foreach(ONE_UNIT_CPP ${ALL_UNIT_CPP})

    get_filename_component(ONE_UNIT_EXEC ${ONE_UNIT_CPP} NAME_WE)

    # Avoid name collision 
    set(TARGET_NAME unit_test_${ONE_UNIT_EXEC})

    add_executable(${TARGET_NAME} ${ONE_UNIT_CPP})
    set_target_properties(${TARGET_NAME} PROPERTIES OUTPUT_NAME ${ONE_UNIT_EXEC}) 
    target_link_libraries(${TARGET_NAME} gtest gtest_main gmock ${CMAKE_THREAD_LIBS_INIT})
    add_test(${TARGET_NAME} ${ONE_UNIT_EXEC})

endforeach()
