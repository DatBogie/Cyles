cmake_minimum_required(VERSION 3.19)
project(Cyles LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

set(CMAKE_AUTORCC ON)

qt_standard_project_setup()

qt_add_executable(Cyles
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    filetreeview.h filetreeview.cpp
    cylesutils.h cylesutils.cpp
    Resources.qrc
    prefwindow.h prefwindow.cpp
    themebuilder.h themebuilder.cpp
    theme.h theme.cpp
    cylessignals.h cylessignals.cpp


)

target_link_libraries(Cyles
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS Cyles
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Cyles
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
