cmake_minimum_required(VERSION 3.16.3)

if (POLICY CMP0135)
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

# Variables para los ejecutables
set(CLIENT_EXECUTABLE client_exec)
set(SERVER_EXECUTABLE server_exec)

# Agregar archivos fuente para el cliente
file(GLOB CLIENT_SOURCES
    "client_src/*.cpp"
    "common_src/*.cpp"
)

# Agregar archivos fuente para el servidor
file(GLOB SERVER_SOURCES
    "server_src/*.cpp"
    "server_src/game_model/*.cpp"
    "common_src/*.cpp"
)

# Crear el ejecutable del cliente
add_executable(${CLIENT_EXECUTABLE} ${CLIENT_SOURCES})
include_directories_for_target(${CLIENT_EXECUTABLE})

# Crear el ejecutable del servidor
add_executable(${SERVER_EXECUTABLE} ${SERVER_SOURCES})
include_directories_for_target(${SERVER_EXECUTABLE})
