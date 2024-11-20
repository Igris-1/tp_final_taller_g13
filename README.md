# Proyecto Final de Taller

## Requisitos de Instalación

Para correr este programa, es necesario instalar las siguientes dependencias:
- Qt6
- QtMediaDev
- SDL2
- SDL2pp
- CMake

## Instrucciones para Ejecutar

1. Clona el repositorio y navega a la carpeta del proyecto.
2. Ejecuta `cmake .` para generar los archivos de construcción.
3. Ejecuta `make` para compilar el proyecto.
4. Navega a la carpeta `build` y ejecuta los siguientes comandos en terminales separadas:

   - Para iniciar el servidor:
     ```sh
     ./server 8080
     ```

   - Para iniciar un cliente:
     ```sh
     ./client_qt
     ```

## Estructura del Proyecto

El proyecto se organiza en las siguientes carpetas:

- `client/`: Contiene el código fuente del cliente.
- `server/`: Contiene el código fuente del servidor.
- `editor/`: Contiene el código fuente del editor.
- `common/`: Contiene el código fuente compartido entre cliente y servidor.

## Notas Adicionales

- Las partidas actualmente deben ser obligatoriamente de 4 jugadores y las partidas inician automáticamente al ser 4 jugadores.
- En la ventana de "New Game" de Qt, solo funciona el primer mapa para jugar, el resto son placeholders. El selector de cantidad de jugadores para la partida de la izquierda no hace nada y el checkbox de "LocalPlayer 2" de la derecha hace que haya un segundo jugador localmente.
- En la ventana de "Join Game", no está implementado poder elegir a qué partida unirse, solo se toca "Start" y el servidor te une a la primera partida que encuentre donde haya espacio para agregar al cliente, sean 1 o 2 jugadores. En la ventana de "Join Game" también hay un checkbox para poner 2 jugadores localmente.




