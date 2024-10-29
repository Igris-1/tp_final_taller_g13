cmake_minimum_required(VERSION 3.16.3)

# Set CMP0135 to NEW to use the preferred behavior for DOWNLOAD_EXTRACT_TIMESTAMP
if (POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

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
option(CLIENT "Enable / disable client program." OFF)
option(SERVER "Enable / disable server program." OFF)
option(EDITOR "Enable / disable editor program." OFF)

# Función para incluir directorios
function(include_directories_for_target target)
    include_directories(${target} PRIVATE
        common_src
        client_src
        server_src
        server_src/game_model
        server_src/game_model/weapon
    )
endfunction()

# Incluir el archivo de advertencias de compilación
include(cmake/CompilerWarnings.cmake)

# ---------------- SDL2 SECTION ------------------
# HEY!! TODO XXX: you need to install some runtime and dev libraries *before*
# compiling the client/editor code.
#
# In xubuntu 24.04 these are:
#
# sudo apt-get install libopus-dev libopusfile-dev libxmp-dev libfluidsynth-dev fluidsynth libwavpack1 libwavpack-dev libfreetype-dev wavpack
#
# Install libSDL2 and libSDL2pp (for client or editor)
# HEY!! TODO XXX: add more dependendies (either for client, server or editor)
if(CLIENT OR EDITOR)
    include(FetchContent)
    FetchContent_Declare(
        SDL2
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-2.30.8
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
        OVERRIDE_FIND_PACKAGE
    )

    FetchContent_Declare(
        SDL2_image
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
        GIT_TAG release-2.8.2
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
        OVERRIDE_FIND_PACKAGE
    )

    FetchContent_Declare(
        SDL2_mixer
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer.git
        GIT_TAG release-2.8.0
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
        OVERRIDE_FIND_PACKAGE
    )

    FetchContent_Declare(
        SDL2_ttf
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
        GIT_TAG release-2.22.0
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
        OVERRIDE_FIND_PACKAGE
    )

    FetchContent_Declare(
        libSDL2pp
        OVERRIDE_FIND_PACKAGE
        URL https://github.com/libSDL2pp/libSDL2pp/archive/cc198c9a5657048bee67ece82de620b2d5661084.zip
    )

    FetchContent_MakeAvailable(SDL2 SDL2_image SDL2_mixer SDL2_ttf libSDL2pp)
endif()


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

    # Encontrar la biblioteca SDL2
    find_package(SDL2 REQUIRED)

    # add libSDL2pp's headers
    target_include_directories(${CLIENT_EXECUTABLE} PRIVATE ${libSDL2pp_SOURCE_DIR})

    # Link the taller_common lib target
    target_link_libraries(${CLIENT_EXECUTABLE} SDL2pp::SDL2pp)

    # add subdirecotire gui
    add_subdirectory(gui)
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