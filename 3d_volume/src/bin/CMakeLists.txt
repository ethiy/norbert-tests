include_directories(BEFORE "${PROJECT_SOURCE_DIR}/src/lib")

set(manual_test_SRC
    "${PROJECT_SOURCE_DIR}/src/bin/manual_test.cpp"
)

add_executable(manual_test ${manual_test_SRC})
target_link_libraries(manual_test norbert.volume)
