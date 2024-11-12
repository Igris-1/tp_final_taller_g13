cmake_minimum_required(VERSION 3.16.3)

if (POLICY CMP0138)
    cmake_policy(SET CMP0138 NEW)
endif()

if (NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 20)
endif()

# strongly encouraged to enable this globally to avoid conflicts between
# -Wpedantic being enabled and -std=c++20 and -std=gnu++20 for example
# when compiling with PCH enabled
set(CMAKE_CXX_EXTENSIONS ON)

# Nombre del proyecto
project(DuckGame
    VERSION 0.0.0
    HOMEPAGE_URL "https://github.com/Igris-1/tp_final_taller_g13"
    LANGUAGES CXX
    )


# ENABLE / DISABLE client, server, testings, algun uso le vamos a dar
option(CLIENT "Enable / disable client program." ON)
option(CLIENT_GUI "Enable / disable client GUI program." OFF)
option(SERVER "Enable / disable server program." ON)
option(EDITOR "Enable / disable editor program." OFF)
option(TESTS "Enable / disable tests." OFF)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})

# Función para incluir directorios
function(include_directories_for_target target)
    include_directories(${target} PRIVATE
        common_src
        client_src
        server_src
        server_src/game_model
        server_src/game_model/weapon
        server_src/game_model/weapon/bullets_strategy
        server_src/game_model/weapon/weapons_strategy
    )
endfunction()

# Incluir el archivo de advertencias de compilación
include(cmake/CompilerWarnings.cmake)


# ---------------- CLIENT SECTION ----------------
if (CLIENT)
    set(SDL2PP_WITH_IMAGE ON)
    set(SDL2PP_WITH_MIXER ON)
    set(SDL2PP_WITH_TTF ON)
    
    # incluir static sdl2pp /third_party/libSDL2pp
    add_subdirectory(third_party/libSDL2pp)

    # Nombre del ejecutable del cliente
    set(CLIENT_EXECUTABLE client)
    
    # Agregar archivos fuente para el cliente
    file(GLOB CLIENT_SOURCES
    "client_src/*.cpp"
    "common_src/*.cpp"
    )

    # Crear el ejecutable del cliente
    add_executable(${CLIENT_EXECUTABLE} ${CLIENT_SOURCES})
    include_directories_for_target(${CLIENT_EXECUTABLE})

    # Encontrar la biblioteca SDL2
    find_package(SDL2 REQUIRED)

    # add libSDL2pp's headers
    target_include_directories(${CLIENT_EXECUTABLE} PRIVATE ${libSDL2pp_SOURCE_DIR})

    # Link the taller_common lib target
    target_link_libraries(${CLIENT_EXECUTABLE} SDL2pp::SDL2pp)
endif()

# ---------------- CLIENT_GUI SECTION ----------------
if (CLIENT_GUI)
    # Encontrar el paquete de Qt necesario
    find_package(Qt6 COMPONENTS Widgets REQUIRED)
    find_package(Qt6 REQUIRED COMPONENTS Multimedia)

    # Nombre del ejecutable del cliente
    set(CLIENT_GUI_EXECUTABLE client_gui_exec)

    # Ruta del directorio de fuentes
    set(GUI_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/client_gui)

    # Buscar todos los archivos .cpp, .h, .ui y .qrc en la carpeta gui
    file(GLOB_RECURSE RESOURCE_FILES "${GUI_SRC_DIR}/*.qrc")
    file(GLOB_RECURSE SRC_FILES "${GUI_SRC_DIR}/*.cpp")
    file(GLOB_RECURSE HEADER_FILES "${GUI_SRC_DIR}/*.h")
    file(GLOB_RECURSE UI_FILES "${GUI_SRC_DIR}/*.ui")

    # Procesar los archivos .ui para generar encabezados automáticamente
    Qt6_wrap_ui(UI_HEADERS ${UI_FILES})

    # Procesar los archivos de cabecera para generar el código de meta-objetos
    Qt6_wrap_cpp(MOC_FILES ${HEADER_FILES})

    # Agregar los archivos de recursos
    Qt6_add_resources(RESOURCES_RCC ${RESOURCE_FILES})

    list(REMOVE_ITEM CLIENT_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/client_src/client_main.cpp")

    # Crear el ejecutable
    add_executable(${CLIENT_GUI_EXECUTABLE} ${SRC_FILES} ${UI_HEADERS} ${MOC_FILES} ${RESOURCES_RCC} ${CLIENT_SOURCES})

    # Configurar la inclusión de directorios de archivos generados automáticamente
    target_include_directories(${CLIENT_GUI_EXECUTABLE} PRIVATE ${CMAKE_CURRENT_BINARY_DIR} ${GUI_SRC_DIR} ${libSDL2pp_SOURCE_DIR})

    # Enlazar el ejecutable con las bibliotecas de Qt necesarias
    target_link_libraries(${CLIENT_GUI_EXECUTABLE} Qt6::Widgets Qt6::Multimedia SDL2pp::SDL2pp)
endif()



# ---------------- SERVER SECTION ----------------
if (SERVER)
    # Nombre del ejecutable del servidor
    set(SERVER_EXECUTABLE server)

    # Agregar archivos fuente para el servidor
    file(GLOB SERVER_SOURCES
    "server_src/*.cpp"
    "server_src/game_model/*.cpp"
    "server_src/actions/*.cpp"
    "server_src/game_model/weapon/*.cpp"
    "common_src/*.cpp"
    "server_src/game_model/weapon/bullets_strategy/*.cpp"
    "server_src/game_model/weapon/weapons_strategy/*.cpp"
    )

    # Crear el ejecutable del servidor
    add_executable(${SERVER_EXECUTABLE} ${SERVER_SOURCES})
    include_directories_for_target(${SERVER_EXECUTABLE})
endif()


# ---------------- EDITOR SECTION ----------------
if (EDITOR)
    # Nombre del ejecutable del editor
    set(EDITOR_EXECUTABLE editor_exec)

    # Agregar archivos fuente para el editor
    file(GLOB EDITOR_SOURCES
    "editor_src/*.cpp"
    "common_src/*.cpp"
    )

    # Crear el ejecutable del editor
    add_executable(editor_exec ${EDITOR_SOURCES})
    include_directories_for_target(editor_exec)
endif()


#  ------ TEST SECTION -----------
if (TESTS)
    # El CMakeLists.txt de tests_src compila los tests, 
    # crea un exec en tests_src y lo ejecuta autimaticamente
    add_subdirectory(tests_src)
    
endif()