#include <iostream>
#include <vector>
#include "core_numeric.h"
#include "vector3d.h"

int main() {
    std::cout << "=== TEST: variance ===" << std::endl;

    // ---- CASOS QUE SI COMPILAN ----

    // double cumple Addable, Divisible, Subtractable y Multiplicable: necesita
    // los cuatro porque variance resta cada valor de la media y eleva al cuadrado.
    std::vector<double> datos = {1.0, 2.0, 3.0};
    std::cout << "Varianza double: " << core_numeric::variance(datos) << std::endl; // 0.6666

    // Vector3D define +, -, *, / component a componente: cumple los 4 concepts.
    std::vector<Vector3D> vectores = {Vector3D(1,0,0), Vector3D(3,0,0), Vector3D(5,0,0)};
    std::cout << "Varianza Vector3D: " << core_numeric::variance(vectores) << std::endl;

    // ---- CASOS QUE NO COMPILAN ----

    // std::vector<std::string> palabras = {"a","b"};
    // core_numeric::variance(palabras);
    // Falla Subtractable<std::string> (no existe operator-) y ademas Divisible
    // (no existe operator/ con size_t). variance necesita restar (valor - media)
    // y luego dividir el acumulado, asi que basta con que falle cualquiera de los
    // dos para que la llamada no compile.

    // struct SoloSuma { int v; SoloSuma operator+(const SoloSuma& o) const { return {v+o.v}; } };
    // core_numeric::variance(std::vector<SoloSuma>{{1},{2}});
    // Este caso es mas sutil: SoloSuma SI cumple Addable (tiene operator+), pero
    // variance tambien exige Subtractable y Multiplicable, y esta clase no define
    // ni operator- ni operator*. Muestra que cumplir un concept no basta si la
    // funcion necesita varios a la vez.

    return 0;
}
