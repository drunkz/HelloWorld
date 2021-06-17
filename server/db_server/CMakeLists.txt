project(db_server VERSION 0.0.1)

set(VERSION_MAJOR "${db_server_VERSION_MAJOR}")
set(VERSION_MINOR "${db_server_VERSION_MINOR}")
set(VERSION_PATCH "${db_server_VERSION_PATCH}")

configure_file(${CMAKE_SOURCE_DIR}/cmake/version.h.in
                ${CMAKE_CURRENT_SOURCE_DIR}/include/version.h)

set(source_files
    db_server.cpp
    ../engine/server_base.cpp
    )

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
	message("current platform: Linux")
elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
    message("current platform: Windows")
else()
    message("other platform: ${CMAKE_SYSTEM_NAME}")
endif()

include_directories("/home/dkz/src/breakpad/src")
link_directories("/home/dkz/src/breakpad/src/client/linux")
add_compile_definitions(BOOST_LOG_DYN_LINK BOOST_STACKTRACE_USE_BACKTRACE)

add_executable(db_server ${source_files})
target_link_libraries(db_server lua boost_log boost_log_setup pthread boost_thread dl backtrace breakpad_client)

add_custom_command(
    TARGET db_server POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/config.ini ${CMAKE_CURRENT_BINARY_DIR}/config.ini
    )
