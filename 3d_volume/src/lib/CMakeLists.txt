include_directories(BEFORE "${PROJECT_SOURCE_DIR}/src/lib")

set(maths_SRC
    "${PROJECT_SOURCE_DIR}/src/lib/norbert/volume.cpp"
)

add_library(norbert.volume ${maths_SRC})
target_link_libraries(norbert.volume)
