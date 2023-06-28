cmake_minimum_required(VERSION 3.25)
project(MyFirstGUI)

# 静态库编译
# wget https://download.qt.io/official_releases/qt/5.15/5.15.10/submodules/qtbase-everywhere-opensource-src-5.15.10.tar.xz
# configure.bat -confirm-license -debug-and-release -static -mp -accessibility -platform win32-msvc2022-x64 -qt-zlib -qt-libjpeg -qt-libpng -qt-freetype -opengl dynamic  -nomake examples -nomake tests -no-compile-examples -prefix ./BUILD -opensource -feature-relocatable
# nmake
# nmake install

# 设置 C++ 标准和自动 MOC/RCC/UIC
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# 设置SDK路径
set(Qt_SDK_MSVC "D:/Developer/Qt/5.15.2/msvc2019_64")
set(Qt_SDK_MSVC_STATIC "D:/Developer/Qt/5.15.2/msvc2019_64.static")
set(Qt_SDK_MINGW "D:/Developer/Qt/5.15.2/mingw81_64")
set(Qt_SDK_LINUX "/usr/local/Qt/5.15.2/gcc_64")

# 链接模式
set(PROJECT_WIN_RELEASE_MODE dynamic)
#set(PROJECT_WIN_RELEASE_MODE static)
#set(PROJECT_WIN_RELEASE_MODE mingw)

# 动态链接时 windeployqt 部署参数
set(windeployqt_params
        --no-compiler-runtime
        --no-translations
        --no-angle
        --no-opengl-sw
        --no-system-d3d-compiler
        $<$<CONFIG:Debug>:--debug>
        $<$<CONFIG:Debug>:--pdb>
        $<TARGET_FILE:MyFirstGUI>
        )

# 设置 Qt 的安装路径
if (WIN32)
    if (PROJECT_WIN_RELEASE_MODE STREQUAL dynamic)
        set(CMAKE_PREFIX_PATH ${Qt_SDK_MSVC})
    elseif (PROJECT_WIN_RELEASE_MODE STREQUAL static)
        set(CMAKE_PREFIX_PATH ${Qt_SDK_MSVC_STATIC})
    elseif (PROJECT_WIN_RELEASE_MODE STREQUAL mingw)
        set(CMAKE_PREFIX_PATH ${Qt_SDK_MINGW})
    endif ()
else ()
    set(CMAKE_PREFIX_PATH ${Qt_SDK_LINUX})
endif (WIN32)


find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED
        )

# 编译目标
add_executable(MyFirstGUI WIN32 main.cpp mainwindow.cpp mainwindow.ui)
target_link_libraries(MyFirstGUI
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        )



# 动态链接库部署
if (WIN32 AND PROJECT_WIN_RELEASE_MODE STREQUAL dynamic)
    add_custom_command(TARGET MyFirstGUI POST_BUILD
            COMMAND ${CMAKE_PREFIX_PATH}/bin/windeployqt.exe ${windeployqt_params} $<TARGET_FILE:MyFirstGUI>
            )
endif ()