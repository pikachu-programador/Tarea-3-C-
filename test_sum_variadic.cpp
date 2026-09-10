#include <iostream>
#include "core_numeric.h"

int main() {
    std::cout << "=== TEST: sum_variadic ===" << std::endl;

    // ---- CASOS QUE SI COMPILAN ----

    // Todos int: cada Ts (int) cumple Addable, se expande el fold (args + ...).
    auto s1 = core_numeric::sum_variadic(1, 2, 33, 4);
    std::cout << "Suma int: " << s1 << std::endl; // 40

    // Todos double: mismo caso pero con otro tipo, tambien cumple Addable.
    auto s2 = core_numeric::sum_variadic(1.5, 2.5, 3.0);
    std::cout << "Suma double: " << s2 << std::endl; // 7.0

    // Tipos mezclados (int y double): se usa std::common_type_t para llevarlos
    // todos al mismo tipo (double) antes de sumar con el fold expression.
    auto s3 = core_numeric::sum_variadic(1, 2.5, 3);
    std::cout << "Suma mixta: " << s3 << std::endl; // 6.5

    // ---- CASOS QUE NO COMPILAN ----

    // core_numeric::sum_variadic("Hola", "Mundo");
    // Aqui cada argumento es const char* (puntero). El operador + entre dos
    // punteros no esta definido en C++ (no se pueden "sumar" dos direcciones
    // de memoria), asi que { a + b } -> std::same_as<T> nunca se cumple y
    // Addable<const char*> falla para cada uno de los Ts del paquete variadic.

    // struct SinSuma { int v; };
    // core_numeric::sum_variadic(SinSuma{1}, SinSuma{2});
    // Falla Addable<SinSuma> por la misma razon que en sum(): la clase no
    // define operator+.

    return 0;
}
