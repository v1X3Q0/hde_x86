project(hde_x86)

if(NOT DEFINED ANDROID_TOOL_BASE)
    message("no ANDROID_TOOL_BASE, setting to working directory")
    set(ANDROID_TOOL_BASE ${CMAKE_CURRENT_SOURCE_DIR})
endif()

set(LOCAL_SOURCE_DIR minfuncfind)

set(INCLUDE_LIST ${ANDROID_TOOL_BASE}/common/local_util)

set(LIBDIR_LIST )

set(LINK_LIST ${PROJECT_NAME} localUtil)

add_library(${PROJECT_NAME} SHARED
    ${LOCAL_SOURCE_DIR}/hde32.c
    ${LOCAL_SOURCE_DIR}/hde64.c
    hde64_post.c)

add_executable(minfuncfind
    ${LOCAL_SOURCE_DIR}/hde32.c
    ${LOCAL_SOURCE_DIR}/hde64.c
    ${LOCAL_SOURCE_DIR}/main.cpp)

add_executable(${PROJECT_NAME}.x hde_exe.c)

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    find_package(getopt_for_windows)
    list(APPEND INCLUDE_LIST ${getopt_for_windows_INCLUDE_DIR})
    list(APPEND LIBDIR_LIST ${getopt_for_windows_LIB_DIR})
    list(APPEND LINK_LIST getopt_for_windows_static)
endif()

target_include_directories(${PROJECT_NAME}.x PRIVATE ${INCLUDE_LIST})

target_link_directories(${PROJECT_NAME}.x PRIVATE ${LIBDIR_LIST})

target_link_libraries(${PROJECT_NAME}.x PRIVATE ${LINK_LIST})

