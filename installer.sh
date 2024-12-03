#!/bin/bash

set -e

GREEN='\033[0;32m'
GRAY='\033[1;30m'
RED='\033[0;31m'
NC='\033[0m'

show_ascii_art() {
cat << "EOF"
    ██████╗ ██╗   ██╗ ██████╗██╗  ██╗
    ██╔══██╗██║   ██║██╔════╝██║ ██╔╝
    ██║  ██║██║   ██║██║     █████╔╝   
    ██║  ██║██║   ██║██║     ██╔═██╗   
    ██████╔╝╚██████╔╝╚██████╗██║  ██╗
    ╚═════╝  ╚═════╝  ╚═════╝╚═╝  ╚═╝
  
   ██████╗  █████╗ ███╗   ███╗███████╗
   ██╔════╝ ██╔══██╗████╗ ████║██╔════╝
   ██║  ███╗███████║██╔████╔██║█████╗  
   ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝  
   ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗
    ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝                                                                       
EOF
echo ""
}


main() {
    show_ascii_art
    help
    while true; do
        echo "Enter a character (or 'q' to quit):"
        read input

        if [ "$input" == "q" ]; then
            echo "See you!"
            break
        fi
        process_input "$input"
    done
}

process_input() {
    case "$1" in
        "d")
            install_dependencies
            ;;
        "i")
            install_game
            ;;
        "a")
            install_dependencies
            install_game
            ;;
        "u")
            uninstall_game
            ;;
        "j")
            uninstall_dependencies
            ;;
        "p")
            uninstall_game
            uninstall_dependencies
            ;;
        "h")
            help
            ;;
        *)
            echo "Character not recognized. Try again.\n"
            ;;
    esac
}

help() {
    echo "Install options:"
    echo "  'd': To install dependencies"
    echo "  'i': To install the game"
    echo "  'a': To install the dependencies and the game"
    echo "  'h': To get the available options"
  
    echo ""
    
    echo "Uninstall options:"
    echo "  'u': To uninstall the game"
    echo "  'j': To uninstall the dependencies"
    echo "  'p': To uninstall the game and the dependencies"

    echo ""
}

install_dependencies() {
  echo -e "${GREEN}Installing dependencies...${NC}"
  
  if [ -f /etc/os-release ]; then
    source /etc/os-release
    
    if [[ "$ID_LIKE" == *"debian"* || "$ID" == "ubuntu" ]]; then
      echo -e "${BLUE}Detected Ubuntu/Debian-based system...${NC}"
      sudo sh -c '
        apt-get install -y cmake
        sudo apt-get install -y libyaml-cpp-dev
        apt-get install -y libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev
        apt-get install -y qt6-base-dev qt6-multimedia
      ' | while IFS= read -r line; do
        echo -e "${GRAY}${line}${NC}"
      done
    elif [[ "$ID_LIKE" == *"arch"* || "$ID" == "arch" || "$ID" == "manjaro" ]]; then
      echo -e "${BLUE}Detected Arch-based system...${NC}"
      sudo sh -c '
        pacman -Syu --noconfirm
        pacman -S --noconfirm cmake
        sudo pacman -S yaml-cpp
        pacman -S --noconfirm sdl2 sdl2_image sdl2_mixer sdl2_ttf
        pacman -S --noconfirm qt6-base qt6-multimedia
      ' | while IFS= read -r line; do
        echo -e "${GRAY}${line}${NC}"
      done
    else
      echo -e "${RED}Unsupported Linux distribution: $ID${NC}"
      return 1
    fi
  else
    echo -e "${RED}Could not detect the operating system.${NC}"
    return 1
  fi

  echo -e "${GREEN}Installation complete!${NC}"
}



install_game() {
  echo -e "${GREEN}Installing game...${NC}"
  if [ -d "build" ]; then
    sudo rm -rf build
  fi
  mkdir build
  cd build
  cmake -DCMAKE_BUILD_TYPE=Release ..
  if sudo make install -j$(nproc); then
    echo -e "${GREEN}Build complete! Ready for use!${NC}"
  else
    echo -e "${RED}Error: Failed to install. Check the error message above for details.${NC}"
  fi
}


uninstall_game() {
  echo -e "${GREEN}Uninstalling game...${NC}"
  sudo rm /usr/bin/duckGameClient || true
  sudo rm /usr/bin/duckGameServer || true
  sudo rm /usr/bin/duckGameEditor || true
  sudo rm -rf /etc/TPDuckGame || true
  sudo rm -rf /usr/lib/TPDuckGame || true
  sudo rm -rf /usr/share/TPDuckGame || true
  if sudo rm -rf build || true; then
      echo -e "${GREEN}Uninstall complete!${NC}"
  else    
      echo -e "${RED}Error: Failed to uninstall. Check the error message above for details.${NC}"
  fi
}


uninstall_dependencies() {
  echo -e "${RED}Removing dependencies...${NC}"

  if [ -f /etc/os-release ]; then
    source /etc/os-release

    if [[ "$ID_LIKE" == *"debian"* || "$ID" == "ubuntu" ]]; then
      echo -e "${BLUE}Detected Ubuntu/Debian-based system...${NC}"
      sudo sh -c '
        apt-get remove --purge -y cmake 2>/dev/null
        apt-get remove --purge -y libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev 2>/dev/null
        apt-get remove --purge -y qt6-base-dev qt6-multimedia 2>/dev/null
        apt-get autoremove -y 2>/dev/null
      ' | while IFS= read -r line; do
        echo -e "${GRAY}${line}${NC}"
      done
    elif [[ "$ID_LIKE" == *"arch"* || "$ID" == "arch" || "$ID" == "manjaro" ]]; then
      echo -e "${BLUE}Detected Arch-based system...${NC}"
      sudo sh -c '
        pacman -Rns --noconfirm cmake 2>/dev/null
        pacman -Rns --noconfirm sdl2 sdl2_image sdl2_mixer sdl2_ttf 2>/dev/null
        pacman -Rns --noconfirm qt6-base qt6-multimedia 2>/dev/null
      ' | while IFS= read -r line; do
        echo -e "${GRAY}${line}${NC}"
      done
    else
      echo -e "${RED}Unsupported Linux distribution: $ID${NC}"
      return 1
    fi
  else
    echo -e "${RED}Could not detect the operating system.${NC}"
    return 1
  fi

  echo -e "${GREEN}Dependencies removed successfully!${NC}"
}



main