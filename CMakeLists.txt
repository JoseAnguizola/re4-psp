cmake_minimum_required(VERSION 3.13)

project(re4-psp C CXX)

if(NOT PLATFORM_PSP)
  message(FATAL_ERROR "Configure with the PSP toolchain: psp-cmake -B build")
endif()

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_executable(re4 src/main.c)

target_compile_options(re4 PRIVATE -Wall -Wextra)

target_link_libraries(re4 PRIVATE
  pspdebug
  pspdisplay
  pspge
  pspctrl
)

create_pbp_file(
  TARGET re4
  TITLE "Resident Evil 4 PSP"
  VERSION 00.01
)
