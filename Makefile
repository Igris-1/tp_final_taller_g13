# Nombre del directorio de construcción
BUILD_DIR = build

# Detectar el número de núcleos disponibles
CORES = $(shell nproc)


# Tipo de compilación: Debug o Release (por defecto Debug)
BUILD_TYPE ?= Debug

# Objetivos del Makefile
.PHONY: all clean test super debug release

# El objetivo por defecto es 'all'
all: $(BUILD_DIR)/Makefile
	$(MAKE) -C $(BUILD_DIR) -j$(CORES)

# Crear el directorio de construcción y ejecutar CMake
$(BUILD_DIR)/Makefile: $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) ..

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Limpiar la compilación
clean:
	rm -rf $(BUILD_DIR)

# Ejecutar las pruebas
test:
	./$(BUILD_DIR)/tests_src/runTests

# Compilar en modo Debug
debug: clean
	$(MAKE) BUILD_TYPE=Debug all

# Compilar en modo Release
release: clean
	$(MAKE) BUILD_TYPE=Release all

# Limpiar, compilar y ejecutar pruebas
super: clean all

superTest:
	make 
	make test
