function( init_gtest )
    execute_process( COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download
    )
    if ( result )
        message( FATAL_ERROR "CMake step for googletest failed: ${result}" )
    endif()

    execute_process( COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download
    )
    if ( result )
        message( FATAL_ERROR "Build step for googletest failed: ${result}" )
    endif()

    # Prevent overriding the parent project's compiler/linker
    # settings on Windows
    set( gtest_force_shared_crt ON CACHE BOOL "" FORCE )

    # Add googletest directly to our build. This defines
    # the gtest and gtest_main targets.
    add_subdirectory(
        ${CMAKE_CURRENT_BINARY_DIR}/googletest-src
        ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL
    )
endfunction()

function( add_gtest
    linkLib testName pathToTest
)
    add_executable( ${testName} ${pathToTest} )
    target_link_libraries( ${testName} ${linkLib} )
    target_link_libraries( ${testName} gtest gtest_main )
    add_test( NAME ${testName}_unittest COMMAND ${testName} )
endfunction()