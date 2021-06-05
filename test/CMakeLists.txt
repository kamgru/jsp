enable_testing()

add_executable(all_tests
        TestMain.cpp
        ScannerTests.cpp
        ParserTests.cpp)

target_link_libraries(all_tests jsp)

add_test("All" all_tests -V)