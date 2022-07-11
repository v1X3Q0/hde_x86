project(hde_x86)

set(LOCAL_SOURCE_DIR minfuncfind)

add_library(${PROJECT_NAME} STATIC
    ${LOCAL_SOURCE_DIR}/hde32.c
    ${LOCAL_SOURCE_DIR}/hde64.c
    hde64_post.c)

if(ARCH MATCHES "AMD64" OR ARCH MATCHES "i386" OR ARCH MATCHES "x86_64")
    add_executable(minfuncfind
        ${LOCAL_SOURCE_DIR}/hde32.c
        ${LOCAL_SOURCE_DIR}/hde64.c
        ${LOCAL_SOURCE_DIR}/main.cpp)
endif()