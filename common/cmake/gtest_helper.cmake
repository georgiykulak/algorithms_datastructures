function( add_gtest
    linkLib testName pathToTest
)
    add_executable( ${testName} ${pathToTest} )
    target_link_libraries( ${testName} ${linkLib} )
    target_link_libraries( ${testName} gtest gtest_main )
    add_test( NAME ${testName}_unittest COMMAND ${testName} )
endfunction()