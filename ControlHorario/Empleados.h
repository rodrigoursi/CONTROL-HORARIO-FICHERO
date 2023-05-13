#ifndef EMPLEADOS_H_INCLUDED
#define EMPLEADOS_H_INCLUDED
#include <string>
#include <cstring>
#include "fecha.h"

using namespace std;

class Empleados{
private:
    int leg;
    int pin;
    char nombre[50];
    char apellido[50];
    int dni;
    char domicilio[50];
    char localidad[50];
    char provincia[50];
    char pais[50];
    FechaHora fNacimiento;
    char genero[1];
    FechaHora fechaIngreso;
    int cargaHoraria;
    bool adm;
    bool activo;
public:
    ///CONSTRUCTOR
    Empleados(int,int,string,string,int,string,string,string,string,FechaHora,string,FechaHora,int,bool,bool=true);
    Empleados(int,int, string);
    Empleados();
    ///GETS
    string getnombre();
    string getapellido();
    int getleg();
    int getpin();
    int getdni();
    string getdomicilio();
    string getlocalidad();
    string getprovincia();
    string getpais();
    FechaHora getFnacimiento();
    string getgenero();
    FechaHora getFechaIngreso();
    int getcargaHoraria();
    bool getRol();
    bool getEliminado();

    ///////////////////////////////////////////////
    ///////////////////////////////////////////////

    ///SETS
    void setnombre(string);
    void setapellido(string);
    void setleg(int);
    void setpin(int);
    void setdni(int);
    void setdomicilio(string);
    void setlocalidad(string);
    void setprovincia(string);
    void setpais(string);
    void setFnacimiento(FechaHora);
    void setgenero(string);
    void setcargaHoraria(int);
    void setRol(bool);
    void setEliminado(bool);

    ///METODOS DE LA CLASE
    int contarRegistros();
    bool LeerDeDisco(int nroRegistro);
    bool GuardarEnDisco();
    bool GuardarEnDisco(int nroRegistro);
};

///DECLARACION DE FUNCIONES DE LA CLASE
int buscarEmpleado(int legajo);//
bool editar_empleados();//
bool EliminarEmpleado();//
void mostrarEmpleado();//
void mostrarJorEmpXMes();
void mostrarJorXFec();
void cambiarPIN();

#endif // EMPLEADOS_H_INCLUDED
