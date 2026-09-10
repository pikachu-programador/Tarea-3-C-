#include <iostream>
#include <vector>
#include "core_numeric.h"
#include "vector3d.h"

int main() {
    std::cout << "=== TEST: sum ===" << std::endl;

    // ---- CASOS QUE SI COMPILAN ----

    // int cumple Addable (int + int -> int) y Iterable lo da el vector.
    std::vector<int> enteros = {1, 2, 3, 4, 5};
    std::cout << "Suma enteros: " << core_numeric::sum(enteros) << std::endl; // 15

    // double tambien cumple Addable.
    std::vector<double> flotantes = {1.5, 2.5, 3.0};
    std::cout << "Suma flotantes: " << core_numeric::sum(flotantes) << std::endl; // 7.0

    // Vector3D define operator+ que retorna Vector3D, asi que tambien cumple Addable:
    // sum() funciona igual con objetos propios que con tipos primitivos.
    std::vector<Vector3D> vectores = {Vector3D(1,0,0), Vector3D(0,1,0), Vector3D(0,0,1)};
    std::cout << "Suma vectores: " << core_numeric::sum(vectores) << std::endl; // (1,1,1)

    // ---- CASOS QUE NO COMPILAN ----

    // int numero = 10;
    // core_numeric::sum(numero);
    // Falla el concept Iterable<int>: sum() necesita un contenedor recorrible con
    // std::begin/std::end, y un int suelto no tiene eso. El error aparece antes
    // de siquiera evaluar si el tipo es sumable.

    // struct SinSuma { int v; };
    // core_numeric::sum(std::vector<SinSuma>{{1},{2}});
    // Aqui si es Iterable (es un vector), pero falla Addable<SinSuma>: la clase
    // SinSuma no define operator+, entonces la expresion { a + b } dentro del
    // concept no es valida y el compilador rechaza la llamada.

    return 0;
}
