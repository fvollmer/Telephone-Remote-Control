cmake_minimum_required(VERSION 2.8)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_C_COMPILER sdcc)


project(phone_remote_control LANGUAGES C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DFOSC=30000000 --iram-size 256")


set(CMAKE_C_STANDARD 11)
add_executable(${PROJECT_NAME} "main.c" "util.c" "iap.c" "phone.c" "isr.c" "time.c" "storage.c")


add_custom_target(flash
  DEPENDS ${PROJECT_NAME}
  COMMAND stcgal -t 30000 ${PROJECT_NAME}.ihx
)

