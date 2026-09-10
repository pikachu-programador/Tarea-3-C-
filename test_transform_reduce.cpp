#include <iostream>
#include <vector>
#include "core_numeric.h"
#include "vector3d.h"

int main() {
    std::cout << "=== TEST: transform_reduce ===" << std::endl;

    // ---- CASOS QUE SI COMPILAN ----

    // La lambda recibe double y retorna double (x*x): double es Addable, asi
    // que se puede sumar el resultado de aplicarla a cada elemento.
    std::vector<double> datos = {1.0, 2.0, 3.0};
    auto r1 = core_numeric::transform_reduce(datos, [](double x){ return x*x; });
    std::cout << "Suma cuadrados: " << r1 << std::endl; // 1+4+9 = 14

    // Funciona igual con int: la funcion template F puede ser cualquier lambda.
    std::vector<int> enteros = {1, 2, 3, 4};
    auto r2 = core_numeric::transform_reduce(enteros, [](int x){ return x*2; });
    std::cout << "Suma doble: " << r2 << std::endl; // 20

    // El contenedor es de Vector3D pero la lambda transforma cada elemento a un
    // double (v.x+v.y+v.z), asi que lo que importa para Addable es el tipo de
    // RETORNO de la funcion, no el tipo del contenedor original.
    std::vector<Vector3D> vectores = {Vector3D(1,0,0), Vector3D(0,2,0)};
    auto r3 = core_numeric::transform_reduce(vectores, [](const Vector3D& v){ return v.x+v.y+v.z; });
    std::cout << "Suma componentes: " << r3 << std::endl; // 3.0

    // ---- CASOS QUE NO COMPILAN ----

    // struct SinSuma { int v; };
    // core_numeric::transform_reduce(std::vector<std::string>{"a"},
    //     [](const std::string& s){ return SinSuma{(int)s.length()}; });
    // Aqui el contenedor (vector<string>) si es Iterable, y la lambda si se puede
    // llamar sobre cada string. El problema es el TIPO DE RETORNO de la lambda:
    // SinSuma no define operator+, entonces falla Addable<SinSuma> y
    // transform_reduce no puede acumular los resultados con result + func(item).

    return 0;
}
