#include <iostream>
#include <string>
#include "core_numeric.h"

int main() {
    std::cout << "=== TEST: max_variadic ===" << std::endl;

    // ---- CASOS QUE SI COMPILAN ----

    // Tipos mezclados (int y double): se usa std::common_type_t<T, Ts...> para
    // que todos los argumentos se comparen y se guarden en el mismo tipo comun.
    auto m1 = core_numeric::max_variadic(1, 2.7, 3, 4);
    std::cout << "Maximo mixto: " << m1 << std::endl; // 4

    // Todos int: el fold expression compara cada argumento contra el resultado
    // acumulado hasta el momento, quedandose siempre con el mayor.
    auto m2 = core_numeric::max_variadic(10, 5, 33, 2);
    std::cout << "Maximo enteros: " << m2 << std::endl; // 33

    // ---- CASOS QUE NO COMPILAN ----

    // Nota: probé pasarle std::string y en realidad SI compila, porque
    // std::string ya tiene operator> definido (compara alfabeticamente), asi
    // que cumple Comparable. No sirve como ejemplo de fallo. El caso que si
    // falla de verdad es una clase sin operator>:

    // struct SinComparar { int v; };
    // core_numeric::max_variadic(SinComparar{1}, SinComparar{2});
    // Falla el concept Comparable<SinComparar>: la clase no define operator>,
    // y max_variadic necesita comparar (rest > result) en cada paso del fold
    // expression para saber cual argumento es mayor. Sin ese operador, la
    // expresion { a > b } -> std::same_as<bool> no es valida y no compila.

    return 0;
}
