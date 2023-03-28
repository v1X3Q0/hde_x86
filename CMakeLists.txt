project(hde_x86)

set(LOCAL_SOURCE_DIR minfuncfind)

add_library(${PROJECT_NAME} SHARED
    ${LOCAL_SOURCE_DIR}/hde32.c
    ${LOCAL_SOURCE_DIR}/hde64.c
    hde64_post.c)

if(ARCH MATCHES "AMD64" OR ARCH MATCHES "i386" OR ARCH MATCHES "x86_64")
    add_executable(minfuncfind
        ${LOCAL_SOURCE_DIR}/hde32.c
        ${LOCAL_SOURCE_DIR}/hde64.c
        ${LOCAL_SOURCE_DIR}/main.cpp)
    
    add_executable(${PROJECT_NAME}.x hde_exe.c)
endif()


set(INCLUDE_LIST ${ANDROID_TOOL_BASE}/common/local_util)

set(LINK_LIST ${PROJECT_NAME} localUtil)

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    find_package(getopt_for_windows)
    list(APPEND INCLUDE_LIST ${getopt_for_windows_INCLUDE_DIR})
    target_link_directories(${PROJECT_NAME}.x PRIVATE ${getopt_for_windows_LIB_DIR})
    list(APPEND LINK_LIST getopt_for_windows_static)
endif()

if(ARCH MATCHES "AMD64" OR ARCH MATCHES "i386" OR ARCH MATCHES "x86_64")
    target_include_directories(${PROJECT_NAME}.x PRIVATE ${INCLUDE_LIST})
    target_link_libraries(${PROJECT_NAME}.x PRIVATE ${LINK_LIST})
endif()

