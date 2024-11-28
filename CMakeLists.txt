cmake_minimum_required(VERSION 3.16.3)

# Set CMake policy for CMP0138 if needed
if (POLICY CMP0138)
    cmake_policy(SET CMP0138 NEW)
endif()

# Set C++ Standard
if (NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 20)
endif()

set(CMAKE_CXX_EXTENSIONS ON)

# Project definition
project(DuckGame
    VERSION 0.0.0 # now only god knows what version we are on.
    HOMEPAGE_URL "https://github.com/Igris-1/tp_final_taller_g13"
    LANGUAGES CXX
)

# Options to enable/disable components
option(CLIENT "Enable / disable client GUI program." ON)
option(SERVER "Enable / disable server program." ON)
option(EDITOR "Enable / disable editor program." ON)
option(TESTS "Enable / disable tests." OFF)

# Include compiler warnings configuration
include(cmake/CompilerWarnings.cmake)

# Find required packages
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(Qt6 COMPONENTS Core REQUIRED)
find_package(Qt6 COMPONENTS Widgets REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Multimedia)

# Include directories for SDL2
include_directories(${SDL2_INCLUDE_DIRS} 
    ${SDL2_IMAGE_INCLUDE_DIRS} 
    ${SDL2_MIXER_INCLUDE_DIRS} 
    ${SDL2_TTF_INCLUDE_DIRS}
)


# ---------------- COMMON SECTION ----------------
file(GLOB COMMON_SOURCES "common_src/*.cpp")
add_library(common_lib STATIC ${COMMON_SOURCES})
target_include_directories(common_lib PUBLIC common_src)


# ---------------- CLIENT SECTION -------------
if (CLIENT)
    set(SDL2PP_WITH_IMAGE ON)
    set(SDL2PP_WITH_MIXER ON)
    set(SDL2PP_WITH_TTF ON)
    add_subdirectory(third_party/libSDL2pp)

    set(CLI_GUI_EXECUTABLE duckGameClient)
    
    file(GLOB CLIENT_SOURCES "client_src/*.cpp")
    file(GLOB_RECURSE RESOURCE_FILES "client_gui/*.qrc")
    file(GLOB_RECURSE SRC_FILES "client_gui/*.cpp")
    file(GLOB_RECURSE HEADER_FILES "client_gui/*.h")
    file(GLOB_RECURSE UI_FILES "client_gui/*.ui")
    
    Qt6_wrap_ui(UI_HEADERS ${UI_FILES})
    Qt6_wrap_cpp(MOC_FILES ${HEADER_FILES})
    Qt6_add_resources(RESOURCES_RCC ${RESOURCE_FILES})

    add_executable(${CLI_GUI_EXECUTABLE} 
        ${SRC_FILES} 
        ${UI_HEADERS} 
        ${MOC_FILES} 
        ${RESOURCES_RCC} 
        ${CLIENT_SOURCES}
    )

    target_link_libraries(${CLI_GUI_EXECUTABLE} PRIVATE 
        common_lib 
        Qt6::Widgets 
        Qt6::Multimedia 
        SDL2pp::SDL2pp
    )

    target_include_directories(${CLI_GUI_EXECUTABLE} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
endif()


# ---------------- SERVER SECTION ----------------
if (SERVER)
    set(SRV_EXECUTABLE duckGameServer)

    file(GLOB SERVER_SOURCES
        "configuration_yamls/*.cpp"
        "server_src/*.cpp"
        "server_src/game_model/*.cpp"
        "server_src/actions/*.cpp"
        "server_src/game_model/weapon/*.cpp"
        "server_src/game_model/weapon/bullets_strategy/*.cpp"
        "server_src/game_model/weapon/weapons_strategy/*.cpp"
    )

    add_executable(${SRV_EXECUTABLE} ${SERVER_SOURCES})
    target_link_libraries(${SRV_EXECUTABLE} PRIVATE common_lib yaml-cpp)
    target_include_directories(${SRV_EXECUTABLE} PRIVATE server_src)
endif()


# ---------------- EDITOR SECTION ----------------
if (EDITOR)
    set(EDITOR_EXECUTABLE duckGameEditor)

    file(GLOB EDITOR_RESOURCES "editor_src/*.qrc")
    file(GLOB EDITOR_SOURCES "editor_src/*.cpp")
    file(GLOB EDITOR_HEADERS "editor_src/*.h")
    file(GLOB EDITOR_UI "editor_src/*.ui")

    qt6_wrap_ui(EDITOR_UI_HEADERS ${EDITOR_UI}) 
    qt6_wrap_cpp(MOC_EDITOR_FILES ${EDITOR_HEADERS})  
    qt6_add_resources(EDITOR_RESOURCES_RCC ${EDITOR_RESOURCES})  

    add_executable(${EDITOR_EXECUTABLE}
        ${EDITOR_SOURCES}
        ${MOC_EDITOR_FILES}
        ${EDITOR_UI_HEADERS}
        ${EDITOR_RESOURCES_RCC}
    )

    target_include_directories(${EDITOR_EXECUTABLE} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
    target_link_libraries(${EDITOR_EXECUTABLE} PRIVATE common_lib yaml-cpp Qt6::Widgets Qt6::Multimedia)
endif()


#  ---------------- TEST SECTION ----------------
if (TESTS)
    add_subdirectory(tests_src)
endif()


# ---------------- INSTALL SECTION ----------------
# set(BIN_INSTALL_DIR "/usr/bin") # ejecutables
# set(SHARED_DIR "/usr/lib/TPDuckGame") # librerías compartidas
# set(CONF_INSTALL_DIR "/etc/TPDuckGame") # archivos de configuración
# set(ASSETS_INSTALL_DIR "/usr/share/TPDuckGame") # assets

# # Install executables
# install(TARGETS duckGameServer duckGameClient duckGameEditor 
#     DESTINATION ${BIN_INSTALL_DIR} 
#     PERMISSIONS WORLD_READ WORLD_WRITE WORLD_EXECUTE)

# # Install common library
# install(TARGETS common_lib 
#     DESTINATION ${SHARED_DIR} 
#     PERMISSIONS WORLD_READ WORLD_WRITE WORLD_EXECUTE)

# # Install configuration files
# install(DIRECTORY "configuration_yamls" DESTINATION ${CONF_INSTALL_DIR})

# # Install assets
# install(DIRECTORY "assets" DESTINATION ${ASSETS_INSTALL_DIR})