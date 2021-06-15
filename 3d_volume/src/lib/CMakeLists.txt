include_directories(BEFORE "${PROJECT_SOURCE_DIR}/src/lib")

set(norbert_SRC
    "${PROJECT_SOURCE_DIR}/src/lib/norbert/algorithms.cpp"
)

add_library(norbert ${norbert_SRC})
