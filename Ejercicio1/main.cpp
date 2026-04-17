#include <iostream>
#include "arbin.h"
using namespace std;


template <typename T>
int cuentaHojas(const Arbin<T> &arbol, typename Arbin<T>::Iterador it){

    // caso base
    if(it.arbolVacio())
        return 0;

    // ver si es hoja
    if(arbol.subIzq(it).arbolVacio() && arbol.subDer(it).arbolVacio())
        return 1;


    return cuentaHojas(arbol, arbol.subIzq(it)) + cuentaHojas(arbol, arbol.subDer(it));

}

template <typename T>
int numeroHojas(const Arbin<T> &arbol){

    return cuentaHojas(arbol, arbol.getRaiz());
}

int main()
{
    // Construimos algunos arboles vacios y hojas
    Arbin<int> vacio;
    Arbin<int> hoja1(1, vacio, vacio);
    Arbin<int> hoja2(3, vacio, vacio);
    Arbin<int> hoja3(6, vacio, vacio);
    
    // Construimos nodos intermedios
    Arbin<int> subArbol1(2, hoja1, hoja2); // Tiene 2 hojas (1 y 3)
    Arbin<int> subArbol2(5, vacio, hoja3); // Tiene 1 hoja (6)
    
    // Construimos la raiz del arbol uniendo los subarboles
    Arbin<int> miArbol(4, subArbol1, subArbol2);

    cout << "Arbol vacio tiene: " << numeroHojas(vacio) << " hojas. (Esperado: 0)" << endl;
    cout << "Arbol hoja (solo raiz) tiene: " << numeroHojas(hoja1) << " hojas. (Esperado: 1)" << endl;
    cout << "Arbol complejo tiene: " << numeroHojas(miArbol) << " hojas. (Esperado: 3)" << endl;

    return 0;
}
