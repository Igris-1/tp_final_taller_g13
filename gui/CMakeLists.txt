cmake_minimum_required(VERSION 3.16)

project(StartWindowApp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# Agregar los archivos fuentes y encabezados
set(SOURCES
    main.cpp
    startWindow.cpp
)

set(HEADERS
    startWindow.h
)

# Asegúrate de que la ruta a startWindow.ui sea correcta
set(UIS
    gui/startWindow.ui  # Asegúrate de que la ruta sea correcta
)

# Agregar el archivo de recursos
set(RESOURCES
    resources.qrc  # Asegúrate de que tu archivo qrc tenga las rutas a assets
)

# Incluir recursos si estás utilizando Qt5 o Qt6
if(${QT_VERSION_MAJOR} EQUAL 5)
    qt5_wrap_ui(UI_HEADERS ${UIS})
    qt5_add_resources(RESOURCE_FILES ${RESOURCES})
else()
    qt6_wrap_ui(UI_HEADERS ${UIS})
    qt6_add_resources(RESOURCE_FILES ${RESOURCES})
endif()

# Variables para los ejecutables
set(START_WINDOW_EXECUTABLE startWindow)

# Agregar el ejecutable y compilar todos los archivos necesarios
add_executable(StartWindowApp ${SOURCES} ${HEADERS} ${UI_HEADERS} ${RESOURCE_FILES})

# Enlazar las bibliotecas necesarias de Qt
target_link_libraries(StartWindowApp Qt${QT_VERSION_MAJOR}::Widgets)
