#include <gtest/gtest.h>

// Función que vamos a probar
int Add(int a, int b) { return a + b; }

// Caso de prueba para la función Add
TEST(AddTest, HandlesPositiveNumbers) {
    EXPECT_EQ(Add(1, 2), 3);  // Prueba con números positivos
    EXPECT_EQ(Add(2, 2), 4);  // Otro caso con números positivos
}

TEST(AddTest, HandlesNegativeNumbers) {
    EXPECT_EQ(Add(-1, -1), -2);  // Prueba con números negativos
    EXPECT_EQ(Add(-1, 1), 0);    // Prueba con un número positivo y uno negativo
}

TEST(AddTest, HandlesZero) {
    EXPECT_EQ(Add(0, 0), 0);  // Prueba con ceros
    EXPECT_EQ(Add(0, 5), 5);  // Prueba con cero y un número positivo
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);  // Inicializa Google Test
    return RUN_ALL_TESTS();                  // Ejecuta todas las pruebas
}
