#include <iostream>
#include "core_numeric.h"

int main() {
    std::cout << "=== TEST: mean_variadic ===" << std::endl;

    // ---- CASOS QUE SI COMPILAN ----

    // Todos int: el tipo comun (Common) es int, is_integral_v<int> es true,
    // asi que if constexpr entra por la rama que convierte a double antes de
    // dividir (para no perder la parte decimal del promedio).
    auto m1 = core_numeric::mean_variadic(1, 2, 3, 4);
    std::cout << "Promedio enteros: " << m1 << std::endl; // 2.5

    // Mezcla int/double: std::common_type_t da double, is_integral_v<double>
    // es false, entra por la otra rama y divide directo (Common ya es Divisible).
    auto m2 = core_numeric::mean_variadic(0.1, 2, 3, 4);
    std::cout << "Promedio mixto: " << m2 << std::endl; // 2.275

    // ---- CASOS QUE NO COMPILAN ----

    // core_numeric::mean_variadic("a", "b");
    // mean_variadic reutiliza sum_variadic internamente, que ya exige
    // Addable<Ts> para cada tipo. Como const char* no cumple Addable (no se
    // pueden sumar dos punteros), el error aparece antes de llegar siquiera
    // a la logica de promedio.

    return 0;
}
