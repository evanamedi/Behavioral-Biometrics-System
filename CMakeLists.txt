cmake_minimum_required(VERSION 3.30)
project(BBS C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(BBS
    capture_keystroke.c
    capture_keystroke.h
    display_text.c
    display_text.h
    main.c
    store_data.c
    store_data.h
    timing.c
    timing.h
        commands.c)
