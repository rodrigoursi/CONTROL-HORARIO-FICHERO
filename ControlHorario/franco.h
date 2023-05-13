#ifndef FRANCO_H_INCLUDED
#define FRANCO_H_INCLUDED

#include <string>
#include <cstring>
#include "fecha.h"
#include "Empleados.h"

using namespace std;

class Franco{

private:
    Empleados _legajo;
    int diaFranco;

public:
    ///constructor
    Franco(Empleados, int);
    Franco(){};
    ///
    ///get
    Empleados getLegajo();
    int getDiaFranco();
    ///
    ///set
    void setLegajo(Empleados);
    void setDiaFranco(int);
    ///utilidades
    bool guardarEnDisco();
    bool guardarEnDisco(int);
    bool leerDeDisco(int pos);
};

int buscarRegistro(int legajo);

#endif // FRANCO_H_INCLUDED
