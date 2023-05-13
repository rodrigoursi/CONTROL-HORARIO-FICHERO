#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <string>
#include <cstring>
using namespace std;

int  mesCantDias(int);
bool validarLoginEmpleado(int, int);//
void MenuAdministrador();//
void mostrar();//
void mostrarActivos();//
void mostrarEliminados();//
bool pedirContrasenia();//
void Listados();//
int  horas_A_minutos(int);
void guardarFichada(int);//
void Leg_pin_incorrecto();//
void Cerrar_Programa();//
bool ValidarLegajoExistente(int legajo);
bool ValidarDiaMes(int dia, int mes);
bool ValidarHoraMinutos(int hora, int minutos);
bool ValidarActivo(int legajo);
int  diaSemana(int,int,int);
void reporte1();
void ausencias();
string Estado(int);

#endif // FUNCIONES_H_INCLUDED
