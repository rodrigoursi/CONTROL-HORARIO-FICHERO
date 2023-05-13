#include "fecha.h"
#include <ctime>
using namespace std;

int  FechaHora::getDia(){
    return _dia;
}

int  FechaHora::getMes(){
    return _mes;
}

int  FechaHora::getAnio(){
    return _anio;
}

int  FechaHora::getHora(){
    return _hora;
}

int  FechaHora::getMinuto(){
    return _minuto;
}

void FechaHora::setDia(int dia){
    _dia = dia;
}

void FechaHora::setMes(int mes){
    _mes = mes;
}

void FechaHora::setAnio(int anio){
    _anio = anio;
}

void FechaHora::setHora(int hora){
    _hora = hora;
}

void FechaHora::setMinuto(int minuto){
    _minuto = minuto;
}

FechaHora::FechaHora(int dia, int mes, int anio, int hora, int minuto){
    _dia = dia;
    _mes = mes;
    _anio = anio;
    _hora = hora;
    _minuto = minuto;
}

FechaHora::FechaHora(int anio, int mes, int dia){
    _dia = dia;
    _mes = mes;
    _anio = anio;

}
FechaHora::FechaHora(){
    time_t rawtime;
    struct tm timeinfo;

    time (&rawtime);
    timeinfo = *(localtime (&rawtime));

    _dia = timeinfo.tm_mday;
    _mes = timeinfo.tm_mon + 1;
    _anio = timeinfo.tm_year + 1900;
    _hora = timeinfo.tm_hour;
    _minuto = timeinfo.tm_min;
}

string FechaHora::toString(){
    string fechaHora;
    fechaHora = to_string(_dia) + "/" + to_string(_mes) + "/" + to_string(_anio) + " " + to_string(_hora) + ":" + to_string(_minuto);
    return fechaHora;
}

