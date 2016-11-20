find_package(Threads REQUIRED)

file(GLOB_RECURSE ALL_LONG_RUN_CPP *.cpp)

foreach(ONE_LONG_RUN_CPP ${ALL_LONG_RUN_CPP})

    get_filename_component(ONE_LONG_RUN_EXEC ${ONE_LONG_RUN_CPP} NAME_WE)

    # Avoid name collision 
    set(TARGET_NAME long_run_test_${ONE_LONG_RUN_EXEC})

    add_executable(${TARGET_NAME} ${ONE_LONG_RUN_CPP})
    set_target_properties(${TARGET_NAME} PROPERTIES OUTPUT_NAME ${ONE_LONG_RUN_EXEC}) 
    add_test(${TARGET_NAME} ${ONE_LONG_RUN_EXEC})

endforeach()
