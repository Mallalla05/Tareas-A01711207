/*
 * Mariana Hernández Díaz
 * A0171107
 * 14 / Agosto / 2024
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

//Se definen las clases de las funciones segun el metodo de suma.
class Funciones {
public:
    int sumaIterativa(int);
    int sumaRecursiva(int);
    int sumaDirecta(int);
};

// En esta parte se implementa el codigo para la suma iterativa.
int Funciones::sumaIterativa(int n) {
    int acum = 0;
    if (n > 1) {
        for (int i = 0; i <= n; i++) {
            acum += i;
        }
    } else if (n == 1) {
        acum = n;
    }
    return acum;
}

//En esta parte se implementa el codigo para la suma recursiva.
int Funciones::sumaRecursiva(int n) {
    if (n > 1) {
        return n + sumaRecursiva(n - 1);
    } else if (n == 1) {
        return n;
    } else {
        return 0;
    }
}

// En esta parte se implementa el codigo para la suma directa.
int Funciones::sumaDirecta(int n) {
    if (n >= 0) {
        return n * (n + 1) / 2;
    } else {
        return 0;
    }
}

#endif // FUNCIONES_H

