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



# Enable / Disable client, server, testings, algun uso le vamos a dar
option(TESTS "Enable / disable tests." ON)
option(CLIENT "Enable / disable client program." ON)
option(SERVER "Enable / disable server program." ON)
option(EDITOR "Enable / disable editor program." OFF)


# Función para incluir directorios
function(include_directories_for_target target)
    include_directories(${target} PRIVATE
        common_src
        client_src
        server_src
        server_src/game_model
    )
endfunction()

# Incluir el archivo de advertencias de compilación
include(cmake/CompilerWarnings.cmake)


# ---------------- CLIENT SECTION ----------------
if (CLIENT)
    # Nombre del ejecutable del cliente
    set(CLIENT_EXECUTABLE client_exec)
    
    # Agregar archivos fuente para el cliente
    file(GLOB CLIENT_SOURCES
    "client_src/*.cpp"
    "common_src/*.cpp"
    )

    # Crear el ejecutable del cliente
    add_executable(${CLIENT_EXECUTABLE} ${CLIENT_SOURCES})
    include_directories_for_target(${CLIENT_EXECUTABLE})
endif()

# ---------------- SERVER SECTION ----------------
if (SERVER)
    # Nombre del ejecutable del servidor
    set(SERVER_EXECUTABLE server_exec)

    # Agregar archivos fuente para el servidor
    file(GLOB SERVER_SOURCES
    "server_src/*.cpp"
    "server_src/game_model/*.cpp"
    "common_src/*.cpp"
    )

    # Crear el ejecutable del servidor
    add_executable(${SERVER_EXECUTABLE} ${SERVER_SOURCES})
    include_directories_for_target(${SERVER_EXECUTABLE})
endif()

# ---------------- GUI SECTION----------------
add_subdirectory(gui)

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