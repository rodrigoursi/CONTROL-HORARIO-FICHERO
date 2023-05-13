#ifndef JORNADA_H_INCLUDED
#define JORNADA_H_INCLUDED

#include <string>
#include <cstring>
#include "fecha.h"
#include "Empleados.h"


using namespace std;

class Jornada{

private:
    FechaHora _fecha;
    Empleados _legajo;
    FechaHora _horaEntrada;
    FechaHora _horaSalida;
    float _horaTotal;
    int estado; /// 0 ok llego en horario, -1 llego tarde
    bool _ausente;

public:
    ///constructor
    Jornada(FechaHora, Empleados, FechaHora, FechaHora, float, int est=0, bool ausente=0);
    Jornada(){};
    ///
    ///get
    FechaHora getFecha();
    Empleados getLegajo();
    FechaHora getHoraEntrada();
    FechaHora getHoraSalida();
    float getHoraTotal();
    int getEstado();
    bool getAusente();
    ///
    ///set
    void setFecha(FechaHora);
    void setLegajo(Empleados);
    void setHoraEntrada(FechaHora);
    void setHoraSalida(FechaHora);
    void setHoraTotal(float);
    void setEstado(int);
    void setAusente(bool);
    ///
    bool guardarEnDisco();
    bool guardarEnDisco(int);
    bool leerDeDisco(int pos);
    int contarRegistros();

};

///DECLARACION DE FUNCIONES GLOBALES

void fichar();//

#endif // JORNADA_H_INCLUDED
