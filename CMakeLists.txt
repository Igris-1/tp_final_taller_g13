cmake_minimum_required(VERSION 3.16.3)

if (POLICY CMP0138)
    cmake_policy(SET CMP0138 NEW)
endif()

if (NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 20)
endif()

set(CMAKE_CXX_EXTENSIONS ON)

project(DuckGame
    VERSION 0.0.0
    HOMEPAGE_URL "https://github.com/Igris-1/tp_final_taller_g13"
    LANGUAGES CXX
)

option(CLIENT "Enable / disable client program." ON)
option(CLIENT_GUI "Enable / disable client GUI program." ON)
option(SERVER "Enable / disable server program." ON)
option(EDITOR "Enable / disable editor program." OFF)
option(TESTS "Enable / disable tests." OFF)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})

include(cmake/CompilerWarnings.cmake)

# Biblioteca común
file(GLOB COMMON_SOURCES "common_src/*.cpp" "configuration_yaml/*.cpp")

add_library(common_lib STATIC ${COMMON_SOURCES})
target_include_directories(common_lib PUBLIC common_src)

# ---------------- CLIENT SECTION ----------------
if (CLIENT)
    set(SDL2PP_WITH_IMAGE ON)
    set(SDL2PP_WITH_MIXER ON)
    set(SDL2PP_WITH_TTF ON)

    add_subdirectory(third_party/libSDL2pp)

    set(CLIENT_EXECUTABLE client)
    file(GLOB CLIENT_SOURCES "client_src/*.cpp")
    add_executable(${CLIENT_EXECUTABLE} ${CLIENT_SOURCES})
    target_link_libraries(${CLIENT_EXECUTABLE} PRIVATE common_lib SDL2pp::SDL2pp)
    target_include_directories(${CLIENT_EXECUTABLE} PRIVATE client_src ${libSDL2pp_SOURCE_DIR})
endif()

# ---------------- CLIENT_GUI SECTION ----------------
if (CLIENT_GUI)
    find_package(Qt6 COMPONENTS Core REQUIRED)
    find_package(Qt6 COMPONENTS Widgets REQUIRED)
    find_package(Qt6 REQUIRED COMPONENTS Multimedia)

    set(CLIENT_GUI_EXECUTABLE client_gui)
    set(GUI_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/client_gui)

    file(GLOB_RECURSE RESOURCE_FILES "${GUI_SRC_DIR}/*.qrc")
    file(GLOB_RECURSE SRC_FILES "${GUI_SRC_DIR}/*.cpp")
    file(GLOB_RECURSE HEADER_FILES "${GUI_SRC_DIR}/*.h")
    file(GLOB_RECURSE UI_FILES "${GUI_SRC_DIR}/*.ui")

    Qt6_wrap_ui(UI_HEADERS ${UI_FILES})
    Qt6_wrap_cpp(MOC_FILES ${HEADER_FILES})
    Qt6_add_resources(RESOURCES_RCC ${RESOURCE_FILES})

    list(REMOVE_ITEM CLIENT_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/client_src/client_main.cpp")

    add_executable(${CLIENT_GUI_EXECUTABLE} ${SRC_FILES} ${UI_HEADERS} ${MOC_FILES} ${RESOURCES_RCC} ${CLIENT_SOURCES})
    target_link_libraries(${CLIENT_GUI_EXECUTABLE} PRIVATE common_lib Qt6::Widgets Qt6::Multimedia SDL2pp::SDL2pp)
    target_include_directories(${CLIENT_GUI_EXECUTABLE} PRIVATE ${CMAKE_CURRENT_BINARY_DIR} ${GUI_SRC_DIR} ${libSDL2pp_SOURCE_DIR})
endif()

# ---------------- SERVER SECTION ----------------
if (SERVER)
    set(SERVER_EXECUTABLE server)
    file(GLOB SERVER_SOURCES
        "server_src/*.cpp"
        "server_src/game_model/*.cpp"
        "server_src/actions/*.cpp"
        "server_src/game_model/weapon/*.cpp"
        "server_src/game_model/weapon/bullets_strategy/*.cpp"
        "server_src/game_model/weapon/weapons_strategy/*.cpp"
    )

    add_executable(${SERVER_EXECUTABLE} ${SERVER_SOURCES})
    target_link_libraries(${SERVER_EXECUTABLE} PRIVATE common_lib)
    target_include_directories(${SERVER_EXECUTABLE} PRIVATE server_src)
endif()

# ---------------- EDITOR SECTION ----------------
if (EDITOR)
    set(EDITOR_EXECUTABLE editor_exec)
    file(GLOB EDITOR_SOURCES "editor_src/*.cpp")
    add_executable(editor_exec ${EDITOR_SOURCES})
    target_link_libraries(editor_exec PRIVATE common_lib)
    target_include_directories(editor_exec PRIVATE editor_src)
endif()

#  ------ TEST SECTION -----------
if (TESTS)
    add_subdirectory(tests_src)
endif()


# ---------------- INSTALL SECTION ----------------
# set(BIN_INSTALL_DIR "/usr/bin")
# set(SHARED_DIR "/usr/lib/TPDuckGame")

# set(CONF_INSTALL_DIR "/etc/TPDuckGame")
# set(VAR_INSTALL_DIR "/var/TPDuckGame")

# install(TARGETS client server DESTINATION ${BIN_INSTALL_DIR}  PERMISSIONS WORLD_READ WORLD_WRITE WORLD_EXECUTE)
# install(TARGETS common_lib client_gui DESTINATION ${SHARED_DIR} PERMISSIONS WORLD_READ WORLD_WRITE WORLD_EXECUTE)

# install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/maps" "${CMAKE_CURRENT_SOURCE_DIR}/resources" DESTINATION ${VAR_INSTALL_DIR} FILE_PERMISSIONS WORLD_READ WORLD_WRITE)
# install(FILES "configuration.yaml" DESTINATION ${CONF_INSTALL_DIR} PERMISSIONS WORLD_READ WORLD_WRITE)