cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
project(start-stdexec VERSION 0.1.0 LANGUAGES C CXX)

set(MY_NAME ${PROJECT_NAME})
set(MY_ROOT ${PROJECT_SOURCE_DIR})

include(${MY_ROOT}/cmake/global.cmake)

# CPM avoid re-downloading dependencies
#  export CPM_SOURCE_CACHE=$HOME/.cache/CPM
set(CPM_DOWNLOAD_VERSION 0.38.7)
set(CPM_DOWNLOAD_LOCATION "${CMAKE_BINARY_DIR}/cmake/CPM_${CPM_DOWNLOAD_VERSION}.cmake")

if(NOT (EXISTS ${CPM_DOWNLOAD_LOCATION}))
  message(STATUS "Downloading CPM.cmake")
  file(DOWNLOAD https://github.com/TheLartians/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake ${CPM_DOWNLOAD_LOCATION})
endif()

include(${CPM_DOWNLOAD_LOCATION})

# options

# configs

# packages

CPMAddPackage("gh:fmtlib/fmt#10.2.1")

CPMAddPackage(
  GITHUB_REPOSITORY gabime/spdlog
  VERSION 1.13.0
  OPTIONS "SPDLOG_FMT_EXTERNAL 1"
)

CPMAddPackage(
  NAME stdexec
  GITHUB_REPOSITORY NVIDIA/stdexec
  GIT_TAG nvhpc-23.09.rc4
  OPTIONS "STDEXEC_BUILD_EXAMPLES OFF" "STDEXEC_BUILD_TESTS OFF"
)

CPMAddPackage(
  NAME taskflow
  GITHUB_REPOSITORY taskflow/taskflow
  VERSION 3.6.0
  OPTIONS "TF_BUILD_TESTS OFF" "TF_BUILD_EXAMPLES OFF"
  DOWNLOAD_ONLY YES
)

# targets

include_directories(
  ${taskflow_SOURCE_DIR}
)

set(MY_TARGETS )
set(MY_SAMPLES ${MY_ROOT}/samples)

## samples

### stdexec_start

add_executable(stdexec_start samples/stdexec_start.cc)
target_link_libraries(stdexec_start fmt spdlog STDEXEC::stdexec)
target_compile_options(stdexec_start PRIVATE -Wno-unused-parameter -Wno-missing-field-initializers -Wno-non-template-friend)
list(APPEND MY_TARGETS stdexec_start)

### taskflow_start

add_executable(taskflow_start samples/taskflow_start.cc)
target_link_libraries(taskflow_start fmt spdlog)
list(APPEND MY_TARGETS taskflow_start)

# install

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)
set(CMAKE_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/${MY_NAME}")

set(CMAKE_MACOSX_RPATH 1)
#set(CMAKE_INSTALL_RPATH "${MY_CMAKE_RPATH}")

install(TARGETS ${MY_TARGETS}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
