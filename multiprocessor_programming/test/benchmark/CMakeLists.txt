find_package(Threads REQUIRED)

file(GLOB_RECURSE ALL_LONG_CPP *.cpp)

foreach(ONE_LONG_CPP ${ALL_LONG_CPP})

    get_filename_component(ONE_LONG_EXEC ${ONE_LONG_CPP} NAME_WE)

    # Avoid name collision 
    set(TARGET_NAME benchmark_test_${ONE_LONG_EXEC})

    add_executable(${TARGET_NAME} ${ONE_LONG_CPP})
    set_target_properties(${TARGET_NAME} PROPERTIES OUTPUT_NAME ${ONE_LONG_EXEC}) 
#    target_link_libraries(${TARGET_NAME} benchmark ${CMAKE_THREAD_LIBS_INIT})
    add_test(${TARGET_NAME} ${ONE_LONG_EXEC})

endforeach()

