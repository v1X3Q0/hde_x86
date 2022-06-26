project(hde_x86)

set(LOCAL_SOURCE_DIR minfuncfind)

add_library(${PROJECT_NAME} STATIC
    ${LOCAL_SOURCE_DIR}/hde32.c
    ${LOCAL_SOURCE_DIR}/hde64.c
    hde64_post.c)

add_executable(minfuncfind
    ${LOCAL_SOURCE_DIR}/hde32.c
    ${LOCAL_SOURCE_DIR}/hde64.c
    ${LOCAL_SOURCE_DIR}/main.cpp)
