#include <iostream>
#include "core_numeric.h"

int main() {
    std::cout << "=== TEST: variance_variadic ===" << std::endl;

    // ---- CASOS QUE SI COMPILAN ----

    // Todos int: reutiliza mean_variadic (que ya vimos que funciona con enteros)
    // y luego calcula (valor - media)^2 para cada uno, sumando con fold expression.
    auto v1 = core_numeric::variance_variadic(1, 2, 3, 4);
    std::cout << "Varianza enteros: " << v1 << std::endl; // 1.25

    // Todos double: mismo algoritmo, sin necesidad de conversion a double.
    auto v2 = core_numeric::variance_variadic(1.0, 2.0, 3.0, 4.0);
    std::cout << "Varianza double: " << v2 << std::endl; // 1.25

    // ---- CASOS QUE NO COMPILAN ----

    // core_numeric::variance_variadic("a", "b", "c");
    // variance_variadic exige Addable, Subtractable y Multiplicable para cada
    // tipo del paquete (los necesita para restar la media y elevar al cuadrado).
    // const char* no cumple ninguno de los tres: no se pueden sumar, restar ni
    // multiplicar dos punteros entre si, asi que el compilador rechaza la
    // llamada por incumplir varios concepts a la vez.

    return 0;
}
