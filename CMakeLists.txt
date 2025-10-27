cmake_minimum_required(VERSION 3.29.3)
project(wwin LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(wwin
    wwin/main.cpp
    wwin/wwin/icons.cpp
    wwin/wwin/screen.cpp
    wwin/wwin/sounds.cpp
    wwin/wwin/utilits.cpp
)

target_include_directories(wwin PRIVATE
    wwin/
    wwin/wwin/
)

if(MSVC)
    target_compile_options(wwin PRIVATE 
        /W4 
        /permissive-
        $<$<CONFIG:Debug>:/MDd /Od /RTC1 /sdl->
        $<$<CONFIG:Release>:/MD /O2 /sdl->
    )
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
else()
    target_compile_options(wwin PRIVATE 
        -Wall 
        -Wextra 
        -Wpedantic
    )
endif()

if(MINGW)
    target_link_options(wwin PRIVATE -mwindows)
    target_link_libraries(wwin PRIVATE 
        winmm
        user32
        gdi32  
        ole32
        shell32
        advapi32
        kernel32
        ntdll
    )
elseif(MSVC)
    target_link_options(wwin PRIVATE /SUBSYSTEM:WINDOWS)
    target_link_libraries(wwin PRIVATE 
        winmm.lib
        user32.lib
        gdi32.lib
        ole32.lib
        shell32.lib
        advapi32.lib
        kernel32.lib
        ntdll.lib
    )
endif()

target_compile_definitions(wwin PRIVATE
    $<$<CONFIG:Debug>:_DEBUG>
    $<$<CONFIG:Release>:NDEBUG>
    _CONSOLE
    UNICODE
    _UNICODE
)

set_target_properties(wwin PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)
