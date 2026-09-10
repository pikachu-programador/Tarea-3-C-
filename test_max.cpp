#include <iostream>
#include <vector>
#include "core_numeric.h"
#include "vector3d.h"

int main() {
    std::cout << "=== TEST: max ===" << std::endl;

    // ---- CASOS QUE SI COMPILAN ----

    // double cumple Comparable (operator> nativo del lenguaje).
    std::vector<double> datos = {1, 2.7, 0.3};
    std::cout << "Maximo double: " << core_numeric::max(datos) << std::endl; // 2.7

    // Vector3D define operator> comparando por magnitud (norma al cuadrado),
    // asi que max() tambien funciona con objetos, no solo con numeros.
    std::vector<Vector3D> vectores = {Vector3D(1,0,0), Vector3D(0,5,0), Vector3D(1,1,1)};
    std::cout << "Vector maxima magnitud: " << core_numeric::max(vectores) << std::endl; // (0,5,0)

    // ---- CASOS QUE NO COMPILAN ----

    // struct SinComparar { int v; };
    // core_numeric::max(std::vector<SinComparar>{{1},{2}});
    // Falla el concept Comparable<SinComparar>: la clase no define operator>,
    // entonces { a > b } -> std::same_as<bool> no es una expresion valida y
    // el compilador no encuentra una version de max() que acepte este tipo.
    // Nota: a diferencia de sum/mean/variance, max NO requiere Addable, asi
    // que un tipo podria fallar aqui aunque sepa sumarse, si no sabe compararse.

    // int numero = 5;
    // core_numeric::max(numero);
    // Falla Iterable<int>: max necesita recorrer un contenedor con begin/end,
    // y un numero suelto no es iterable.

    return 0;
}
