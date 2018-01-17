cmake_minimum_required (VERSION 3.2)
project (FT)

set(FT_VERSION_MAJOR 1 CACHE STRING "major version" FORCE)
set(FT_VERSION_MINOR 0 CACHE STRING "minor version" FORCE)
set(FT_VERSION "${ACRLFT_VERSION_MAJOR}.${ACRLFT_VERSION_MINOR}" CACHE STRING "version" FORCE)

option(FT_DEBUG_MODE "whether or not debug mode is activated" OFF)

if (APPLE)
  option(USE_CLANG "build application with clang" ON)
  set(compiler_flags "-std=c++11 -stdlib=libc++ -O3 -Wall -Weverything -Wno-shorten-64-to-32 -Wno-padded -Wno-missing-prototypes -Wno-format-nonliteral -Wno-disabled-macro-expansion -Wno-missing-noreturn")
  set(CMAKE_C_COMPILER "clang")
  set(CMAKE_CXX_COMPILER "clang++")

  set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} /usr/local/lib)
  find_package(Armadillo REQUIRED)
  include_directories(${ARMADILLO_INCLUDE_DIRS})

  set(lapackblas_libraries "")
else ()
  set(compiler_flags "-g -Wall -Wextra -O3 -std=c++11")

  set(CMAKE_C_COMPILER "cc")
  set(CMAKE_CXX_COMPILER "c++")
  find_package(Armadillo REQUIRED)
  include_directories(${ARMADILLO_INCLUDE_DIRS})
  
  find_package(BLAS REQUIRED)
  find_package(LAPACK REQUIRED)
  set(lapackblas_libraries ${BLAS_LIBRARIES} ${LAPACK_LIBRARIES})

endif()

# set(static_libs 1)
set(static_libs 0)

SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

include_directories(include)
add_subdirectory(src)

add_subdirectory(test)