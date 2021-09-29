cmake_minimum_required (VERSION 3.20.0) # use the latest major version available

if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(FATAL_ERROR "FATAL: In-source builds are not allowed. You should create a separate directory for build files.")
endif()

if (NOT CMAKE_BUILD_TYPE)
  set (CMAKE_BUILD_TYPE "Release")
  message (STATUS "Build type not specified: using 'Release' by default")
endif()

project (surv-royale)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)

file (MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/SurvRoyale-client")
file (MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/SurvRoyale-server")

include_directories (SYSTEM "${CMAKE_SOURCE_DIR}/SFML/include")
include_directories (SYSTEM "${CMAKE_SOURCE_DIR}/zipper")

link_directories ("${CMAKE_SOURCE_DIR}/SFML/build/lib")
link_directories ("${CMAKE_SOURCE_DIR}/zipper/build")

file (GLOB CLIENT_SRC_FILES "${CMAKE_SOURCE_DIR}/src/client/*.cpp")
file (GLOB SERVER_SRC_FILES "${CMAKE_SOURCE_DIR}/src/server/*.cpp")

add_executable (surv-royale-client WIN32 ${CLIENT_SRC_FILES}) # remove WIN32 if you want to keep console logs on Windows
add_executable (surv-royale-server ${SERVER_SRC_FILES})

add_custom_command (TARGET surv-royale-client POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:surv-royale-client> "${CMAKE_BINARY_DIR}/SurvRoyale-client")
add_custom_command (TARGET surv-royale-server POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:surv-royale-server> "${CMAKE_BINARY_DIR}/SurvRoyale-server")

target_link_libraries (surv-royale-client sfml-graphics sfml-window sfml-audio sfml-network sfml-system Zipper-static z)
target_link_libraries (surv-royale-server sfml-network sfml-system)

file (COPY "LICENSE.txt" DESTINATION "${CMAKE_BINARY_DIR}/SurvRoyale-client")
file (COPY "CHANGELOG.txt" DESTINATION "${CMAKE_BINARY_DIR}/SurvRoyale-client")
file (COPY "GameData.zip" DESTINATION "${CMAKE_BINARY_DIR}/SurvRoyale-client")

file (COPY "LICENSE.txt" DESTINATION "${CMAKE_BINARY_DIR}/SurvRoyale-server")
file (COPY "CHANGELOG.txt" DESTINATION "${CMAKE_BINARY_DIR}/SurvRoyale-server")
file (COPY "server.conf" DESTINATION "${CMAKE_BINARY_DIR}/SurvRoyale-server")
