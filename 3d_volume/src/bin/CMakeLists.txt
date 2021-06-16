include_directories(BEFORE "${PROJECT_SOURCE_DIR}/src/lib")

set(manual_image_test_SRC
    "${PROJECT_SOURCE_DIR}/src/bin/manual_image_test.cpp"
)

add_executable(manual_image_test ${manual_image_test_SRC})
target_link_libraries(manual_image_test norbert CONAN_PKG::boost)
