#include <iostream>
#include <cstdlib>
#include <queue>
#include <stack>
#include "arbin.h"
#include "abb.h"
#include "Excep_Ej6.h"

// Recorridos

template <typename T>
void inorden(const Arbin<T>& a, const typename Arbin<T>::Iterador& r) {
    if (!r.arbolVacio()) {
        inorden(a, a.subIzq(r));
        cout << r.observar() << " ";
        inorden(a, a.subDer(r));
    }
}

template <typename T>
void preorden(const Arbin<T>& a, const typename Arbin<T>::Iterador& r) {
    if (!r.arbolVacio()) {
        cout << r.observar() << " ";
        preorden(a, a.subIzq(r));
        preorden(a, a.subDer(r));
    }
}

template <typename T>
void postorden(const Arbin<T>& a, const typename Arbin<T>::Iterador& r) {
    if (!r.arbolVacio()) {
        postorden(a, a.subIzq(r));
        postorden(a, a.subDer(r));
        cout << r.observar() << " ";
    }
}

template <typename T>
void anchura(const Arbin<T>& a) {
    if (!a.esVacio()) {
        queue<typename Arbin<T>::Iterador> c;
        typename Arbin<T>::Iterador ic = a.getRaiz();
        c.push(ic);
        while (!c.empty()) {
             ic = c.front();
             c.pop();
             cout << ic.observar() << " ";
             if (!a.subIzq(ic).arbolVacio())
                c.push(a.subIzq(ic));
             if (!a.subDer(ic).arbolVacio())
                c.push(a.subDer(ic));
        }
    }
}

template <typename T>
void pintarRama(const Arbin<T>& arbol, typename Arbin<T>::Iterador it, int nivel) {
    if (!it.arbolVacio()) {
        pintarRama(arbol, arbol.subDer(it), nivel + 1);
        for (int i = 0; i < nivel; i++) {
            cout << "    ";
        }
        cout << it.observar() << endl;
        pintarRama(arbol, arbol.subIzq(it), nivel + 1);
    }
}

template <typename T>
void pintarArbol(const Arbin<T>& arbol) {
    if (arbol.esVacio()) {
        cout << "[Arbol Vacio]" << endl;
    } else {
        pintarRama(arbol, arbol.getRaiz(), 0);
        cout << "--------------------" << endl;
    }
}


/***************************************************************************/
/****************************** EJERCICIOS *********************************/
/***************************************************************************/
//Ejercicio 1
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
int numHojas(const Arbin<T> &arbol){

    return cuentaHojas(arbol, arbol.getRaiz());
}

/****************************************************************************/
//Ejercicio 2

template <typename T>
Arbin<T> creaSimetrico(const Arbin<T> &arbol, typename Arbin<T>::Iterador it){
    if(it.arbolVacio())
        return Arbin<T>();

    return Arbin<T>(it.observar(), creaSimetrico(arbol, arbol.subDer(it)), creaSimetrico(arbol, arbol.subIzq(it)));
}


template <typename T>
Arbin<T> simetrico(const Arbin<T> &arbol){
    // caso base


    return creaSimetrico(arbol, arbol.getRaiz());

}

/****************************************************************************/
//Ejercicio 3


template <typename T>
void recorridoZigzag(const Arbin<T> &a, char direccion){
    if (direccion != 'I' && direccion != 'D'){
        cout << "Error indicando la direccion" << endl;
        return;
    }

    if (a.esVacio()) return;

    stack<typename Arbin<T>::Iterador> pilaActual;
    stack<typename Arbin<T>::Iterador> pilaSiguiente;

    pilaActual.push(a.getRaiz());
    char dirActual = direccion;

    while (!pilaActual.empty()) {
        typename Arbin<T>::Iterador ic = pilaActual.top();
        pilaActual.pop();

        cout << ic.observar() << " ";

        // Metemos los hijos en la pilaSiguiente según la dirección actual
        if (dirActual == 'I') {
            if (!a.subDer(ic).arbolVacio()) pilaSiguiente.push(a.subDer(ic)); // Derecho primero
            if (!a.subIzq(ic).arbolVacio()) pilaSiguiente.push(a.subIzq(ic)); // Izquierdo después (saldrá 1º)
        } else {
            if (!a.subIzq(ic).arbolVacio()) pilaSiguiente.push(a.subIzq(ic)); // Izquierdo primero
            if (!a.subDer(ic).arbolVacio()) pilaSiguiente.push(a.subDer(ic)); // Derecho después (saldrá 1º)
        }

        // Si la pilaActual se vacía, significa que hemos terminado de imprimir este nivel
        if (pilaActual.empty()) {
            pilaActual.swap(pilaSiguiente); // Pasamos los nodos del siguiente nivel a la pila actual
            dirActual = (dirActual == 'I') ? 'D' : 'I'; // Cambiamos el sentido para el nivel que entra
        }
    }
}


/******************************************************************************/
//Ejercicio 4
template <typename T>
int contarCompensado(const Arbin<T>& arbol, typename Arbin<T>::Iterador it) {
    if (it.arbolVacio()) {
        return 0; // Un árbol vacío tiene 0 nodos y está compensado
    }

    // Calculamos los nodos de los subárboles
    int nodosIzq = contarCompensado(arbol, arbol.subIzq(it));
    int nodosDer = contarCompensado(arbol, arbol.subDer(it));

    // Si alguno de los hijos devolvió -1, significa que no está compensado más abajo
    if (nodosIzq == -1 || nodosDer == -1) {
        return -1;
    }

    // Comprobamos la condición de compensación en este nodo:
    // La diferencia de número de nodos de los hijos <= 1
    if (abs(nodosIzq - nodosDer) > 1) {
        return -1; // No está compensado
    }

    // Si todo está bien, devuelvo mi número total de nodos 
    // (mis hijos + yo mismo)
    return nodosIzq + nodosDer + 1;
}


template <typename T>
bool compensado(const Arbin<T> &a){
    if (a.esVacio()) return true;
    
    return contarCompensado(a, a.getRaiz()) != -1;
}

/*****************************************************************************/
//Ejercicio 5

template <typename T>
void contarPalabrasAux(const Arbin<T>& a, typename Arbin<T>::Iterador it, string palabraActual) {
    if (it.arbolVacio()) {
        return; // Caso base de seguridad
    }

    // 1. Añadimos la letra del nodo actual a nuestra cadena
    palabraActual += it.observar();

    // 2. Comprobamos si somos una hoja (fin de camino)
    bool esHoja = a.subIzq(it).arbolVacio() && a.subDer(it).arbolVacio();
    
    if (esHoja) {
        // Imprimimos la palabra final formada
        cout << palabraActual << endl;
    } else {
        // 3. Continuamos el camino por los hijos pasándoles la palabra que llevamos reunida
        contarPalabrasAux(a, a.subIzq(it), palabraActual);
        contarPalabrasAux(a, a.subDer(it), palabraActual);
    }
}

// Función principal envoltorio
template <typename T>
void palabras(const Arbin<T>& a) {
    if (!a.esVacio()) {
        contarPalabrasAux(a, a.getRaiz(), ""); // Empezamos con una cadena vacía
    }
}

/******************************************************************************/
//Ejercicio 6
int siguienteMayorAux(const ABB<int>& a, const ABB<int>::Iterador& it, int x) {
    if (it.arbolVacio()) {
        return -1; // No encontramos ningún mayor en esta rama
    }

    int valorActual = it.observar();

    // Si el nodo actual es menor o igual a x, el siguiente mayor (si existe) 
    // TIENE que estar por fuerza en el subárbol derecho.
    if (valorActual <= x) {
        return siguienteMayorAux(a, a.subDer(it), x);
    } 
    // Si el nodo actual es mayor que x, ESTE podría ser nuestro candidato, 
    // pero también podría haber uno más pequeño (que siga siendo > x) en el subárbol izquierdo.
    else {
        int candidatoIzq = siguienteMayorAux(a, a.subIzq(it), x);
        
        // Si a la izquierda encontramos un mejor candidato, nos quedamos con ese.
        // Si a la izquierda no había nada o todo era <= x, nos quedamos con nuestro valorActual.
        if (candidatoIzq != -1) {
            return candidatoIzq;
        } else {
            return valorActual;
        }
    }
}

int siguienteMayor(const ABB<int>& a, int x) { // throw(NoHaySiguienteMayor)
    int resultado = siguienteMayorAux(a, a.getRaiz(), x);
    
    if (resultado == -1) {
        throw NoHaySiguienteMayor();
    }
    
    return resultado;
}



/******************************************************************************/
//Ejercicio 7
template <typename T>
void posicionInordenAux(const ABB<T>& a, typename ABB<T>::Iterador it, const T& elemento, int& contador, int& posicion) {
    // Si el árbol está vacío o ya hemos encontrado el elemento (posicion != 0), podamos la búsqueda
    if (it.arbolVacio() || posicion != 0) {
        return; 
    }

    // 1. Visitamos el subárbol izquierdo (recorrido inorden)
    posicionInordenAux(a, a.subIzq(it), elemento, contador, posicion);

    // 2. Procesamos el nodo actual (sólo si aún no hemos encontrado lo que buscábamos)
    if (posicion == 0) {
        contador++; // Aumentamos la posición inorden actual
        if (it.observar() == elemento) {
            posicion = contador; // ¡Lo hemos encontrado!
            return;
        }
        
        // 3. Visitamos el subárbol derecho (recorrido inorden)
        posicionInordenAux(a, a.subDer(it), elemento, contador, posicion);
    }
}

template <typename T>
int posicionInorden(const ABB<T>& a, const T& elemento) {
    int contador = 0; // Llevará la cuenta de por qué nodo temporal vamos
    int posicion = 0; // Guardará el resultado final
    
    posicionInordenAux(a, a.getRaiz(), elemento, contador, posicion);
    
    return posicion; // Devolverá 0 si el elemento nunca se encuentra
}

/******************************************************************************/
//Ejercicio 8
bool haySumaCaminoAux(const Arbin<int>& a, typename Arbin<int>::Iterador it, int sumaRestante) {
    // Restamos el valor del nodo actual a lo que nos queda por sumar
    int nuevaSuma = sumaRestante - it.observar();
    
    bool izqVacio = a.subIzq(it).arbolVacio();
    bool derVacio = a.subDer(it).arbolVacio();
    
    // Si somos una hoja, comprobamos si hemos logrado llegar exactamente a 0
    if (izqVacio && derVacio) {
        return nuevaSuma == 0;
    }

    // Si no somos hoja, lanzamos la búsqueda por las ramas válidas
    bool encontrado = false;
    
    if (!izqVacio) {
        encontrado = haySumaCaminoAux(a, a.subIzq(it), nuevaSuma);
    }
    
    // Si ya lo encontramos por la izquierda, no hace falta buscar por la derecha (poda)
    if (!encontrado && !derVacio) {
        encontrado = haySumaCaminoAux(a, a.subDer(it), nuevaSuma);
    }
    
    return encontrado;
}

bool haySumaCamino(const Arbin<int>& a, int suma) {
    if (a.esVacio()) {
        return suma == 0;
    }
    return haySumaCaminoAux(a, a.getRaiz(), suma);
}

/****************************************************************************/
/****************************************************************************/
int main(int argc, char *argv[])
{
    Arbin<char> A('t', Arbin<char>('m', Arbin<char>(),
                                        Arbin<char>('f', Arbin<char>(), Arbin<char>())),
                       Arbin<char>('k', Arbin<char>('d', Arbin<char>(), Arbin<char>()),
                                        Arbin<char>()));

    Arbin<char> B('t', Arbin<char>('n', Arbin<char>(),
                                        Arbin<char>('d', Arbin<char>('e', Arbin<char>(), Arbin<char>()),
                                                         Arbin<char>())),
                       Arbin<char>('m', Arbin<char>('f', Arbin<char>(), Arbin<char>()),
                                        Arbin<char>('n', Arbin<char>(), Arbin<char>())));

    Arbin<char> D('t', Arbin<char>('k', Arbin<char>('d', Arbin<char>(), Arbin<char>()),
                                        Arbin<char>()),
                       Arbin<char>('m', Arbin<char>(),
                                        Arbin<char>('f', Arbin<char>(), Arbin<char>())));

    Arbin<char> E('o', Arbin<char>('r', Arbin<char>(),
                                        Arbin<char>('o', Arbin<char>(), Arbin<char>())),
                       Arbin<char>('l', Arbin<char>('a', Arbin<char>(), Arbin<char>()),
                                        Arbin<char>('e', Arbin<char>(), Arbin<char>())));

    Arbin<int> F(2, Arbin<int>(7, Arbin<int>(2, Arbin<int>(), Arbin<int>()),
                                  Arbin<int>(6, Arbin<int>(5, Arbin<int>(), Arbin<int>()),
                                                Arbin<int>(11, Arbin<int>(), Arbin<int>()))),
                    Arbin<int>(5, Arbin<int>(),
                                  Arbin<int>(9, Arbin<int>(),
                                                  Arbin<int>(4, Arbin<int>(), Arbin<int>()))));

    ABB<int> BB6, BB7;



    // NUMERO HOJAS //
    cout << "Arbol B: \n";
    pintarArbol(B);
    cout << "\nNum. hojas del arbol B: " << numHojas(B) << endl << endl;

    cout << "Arbol E: \n";
    pintarArbol(E);
    cout << "\nNum. hojas del arbol E: " << numHojas(E) << endl << endl;

    // COPIA SIMETRICA //
    Arbin<char> C = simetrico(B);
    cout << "Recorrido en inorden del arbol B: " << endl;
    inorden(B, B.getRaiz());
    cout << endl << "Recorrido en inorden del arbol C: " << endl;
    inorden(C, C.getRaiz());
    cout << endl << endl;


    // RECORRIDO EN ZIG-ZAG //
    cout << "Recorrido en zigzag I de B:\n";
    recorridoZigzag(B, 'I');
    cout << endl;
    cout << "Recorrido en zigzag D de C:\n";
    recorridoZigzag(C, 'D');
    cout << endl << endl;

    // COMPENSADO //
    cout << "Esta A compensado?:";
    cout << (compensado(A) ? " SI" : " NO") << endl;
    cout << "Esta B compensado?:";
    cout << (compensado(B) ? " SI" : " NO") << endl << endl;


    // PALABRAS DE UN ARBOL //
    cout << "PALABRAS DE A:\n";
    palabras(E);
    cout << "PALABRAS DE B:\n";
    palabras(B);
    cout << endl;

    // SIGUIENTE MAYOR
    BB6.insertar(8); BB6.insertar(3); BB6.insertar(10); BB6.insertar(1); BB6.insertar(6);
    BB6.insertar(14); BB6.insertar(4); BB6.insertar(7); BB6.insertar(13);
    try
    {
        cout << "Siguiente mayor en BB6 de 5: " << siguienteMayor(BB6, 5) << endl;
        cout << "Siguiente mayor en BB6 de 8: " << siguienteMayor(BB6, 8) << endl;
        cout << "Siguiente mayor en BB6 de 13: " << siguienteMayor(BB6, 13) << endl;
        cout << "Siguiente mayor en BB6 de 14: " << siguienteMayor(BB6, 14) << endl;
    }
    catch(const NoHaySiguienteMayor& e)
    {
        cout << e.Mensaje() << endl << endl;
    }

    // POSICION INORDEN //
    BB7.insertar(5); BB7.insertar(1); BB7.insertar(3); BB7.insertar(8); BB7.insertar(6);
    cout << "Posicion Inorden en BB7 de 3: ";
    cout << posicionInorden(BB7, 3);
    cout << endl << "Posicion Inorden en BB7 de 8: ";
    cout << posicionInorden(BB7, 8);
    cout << endl << "Posicion Inorden en BB7 de 7: ";
    cout << posicionInorden(BB7, 7);
    cout << endl << endl;

    // SUMA CAMINO
    cout << "Hay un camino de suma 26 en F?:";
    cout << (haySumaCamino(F, 26) ? " SI" : " NO") << endl;
    cout << "Hay un camino de suma 9 en F?:";
    cout << (haySumaCamino(F, 9) ? " SI" : " NO") << endl;

    system("PAUSE");
    return 0;
}
