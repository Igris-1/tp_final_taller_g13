# Proyecto Final de Taller

## Requisitos de Instalación

Para correr este programa, es necesario instalar las siguientes dependencias que se instalan automaticamente con el instalador, los detalles del instalador en la web.
- Qt6
- QtMediaDev
- SDL2
- SDL2pp
- CMake

## Instrucciones para Ejecutar

1. Clona el repositorio y navega a la carpeta del proyecto.
2. Ejecuta `make` para compilar el proyecto en modo debug.
3. Navega a la carpeta `build` y ejecuta los siguientes comandos en terminales separadas:
   
   - Para iniciar el servidor:
     ```sh
     ./duckGameServer 8080
     ```

   - Para iniciar un cliente:
     ```sh
     ./duckGameClient
     ```
   - Para iniciar el editor:
     ```sh
     ./duckGameEditor
     ```
> El server se puede levantar en cualquier puerto y el cliente por default se autocompleta con puerto 8080 e ip localhost, ambos modificables

## Estructura del Proyecto

El proyecto se organiza en las siguientes carpetas:

- `client/`: Contiene el código fuente del cliente.
- `server/`: Contiene el código fuente del servidor.
- `editor/`: Contiene el código fuente del editor.
- `common/`: Contiene el código fuente compartido entre cliente y servidor.

## Notas Adicionales
- [Pagina web del tp](https://igris-1.github.io/duckGametp/)
