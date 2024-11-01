# Versión mínima de CMake
cmake_minimum_required(VERSION 3.15)

# Encontrar el paquete de Qt necesario
find_package(Qt5 COMPONENTS Widgets REQUIRED)

# Ruta del directorio de fuentes
set(GUI_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Buscar todos los archivos .cpp, .h y .ui en la carpeta gui
file(GLOB_RECURSE SRC_FILES "${GUI_SRC_DIR}/*.cpp" "${GUI_SRC_DIR}/*.h" "${GUI_SRC_DIR}/*.ui")

# Procesar los archivos .ui para generar encabezados automáticamente
qt5_wrap_ui(UI_HEADERS ${UI_FILES})

# Agregar el ejecutable utilizando los archivos fuente y los encabezados generados
add_executable(gui_executable ${SRC_FILES} ${UI_HEADERS})

# Enlazar el ejecutable con las bibliotecas de Qt necesarias
target_link_libraries(gui_executable Qt5::Widgets)

# Configurar la inclusión de directorios de archivos generados automáticamente
target_include_directories(gui_executable PRIVATE ${CMAKE_CURRENT_BINARY_DIR})