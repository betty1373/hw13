cmake_minimum_required(VERSION 3.2)

if (NOT DEFINED ENV{GITHUB_RUN_NUMBER})
    set(ENV{GITHUB_RUN_NUMBER} 1)
endif()
project(fashio_mnist VERSION 0.0.$ENV{GITHUB_RUN_NUMBER})

find_package(Threads REQUIRED)

configure_file(version.h.in ${PROJECT_SOURCE_DIR}/version.h)

file(GLOB TARGET_SRC
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/inc/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/inc/*.h")
add_executable(fashio_mnist ${TARGET_SRC})

set_target_properties(fashio_mnist PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wall;-Wextra;-pedantic;-Werror"
)
target_link_libraries(fashio_mnist PRIVATE 
    ${CMAKE_THREAD_LIBS_INIT}
)

install(TARGETS fashio_mnist RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)
