# Nombre del directorio de construcción
BUILD_DIR = build

# Detectar el número de núcleos disponibles
CORES = $(shell nproc)

# Objetivos del Makefile
.PHONY: all clean

# El objetivo por defecto es 'all'
all: $(BUILD_DIR)/Makefile
	$(MAKE) -C $(BUILD_DIR) -j$(CORES)

# Crear el directorio de construcción y ejecutar CMake
$(BUILD_DIR)/Makefile: $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake ..

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Limpiar la compilación
clean:
	rm -rf $(BUILD_DIR)

test:
	./$(BUILD_DIR)/tests_src/runTests

super:
	make clean
	make -j$(CORES)
	make test
