#include <iostream>
#include <vector>
#include "core_numeric.h"
#include "vector3d.h"

int main() {
    std::cout << "=== TEST: mean ===" << std::endl;

    // ---- CASOS QUE SI COMPILAN ----

    // double cumple Addable y Divisible: double/size_t sigue siendo double.
    std::vector<double> datos = {1.0, 2.0, 3.0};
    std::cout << "Promedio double: " << core_numeric::mean(datos) << std::endl; // 2.0

    // Vector3D define operator/ (por escalar), asi que cumple Divisible tambien.
    std::vector<Vector3D> vectores = {Vector3D(2,0,0), Vector3D(0,4,0)};
    std::cout << "Promedio Vector3D: " << core_numeric::mean(vectores) << std::endl; // (1,2,0)

    // ---- CASOS QUE NO COMPILAN ----

    // std::vector<int> enteros = {1,2,3};
    // core_numeric::mean(enteros);
    // Falla el concept Divisible<int>. Aunque parezca raro, al dividir un int entre
    // un std::size_t (que es unsigned), las reglas de conversion de C++ hacen que
    // el resultado se convierta a size_t, no a int. Como el concept exige que
    // { a / n } sea exactamente std::same_as<int>, la condicion no se cumple y
    // mean() rechaza vectores de enteros (solo acepta tipos flotantes).

    // std::vector<std::string> palabras = {"a","b"};
    // core_numeric::mean(palabras);
    // Falla Divisible<std::string>: std::string no tiene operator/ definido con
    // std::size_t, entonces la expresion ni siquiera es valida sintacticamente.

    return 0;
}
