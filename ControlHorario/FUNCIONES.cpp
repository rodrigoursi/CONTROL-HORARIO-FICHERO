#include <cstring>
#include <string>
#include <iostream>
using namespace std;
#include "rlutil.h"
#include "administrador.h"
#include "FUNCIONES.h"
#include "Reportes.h"
#include "Empleados.h"
#include "jornada.h"
#include "fecha.h"
#include "calendario.h"
#include <iomanip>

int mesCantDias(int mes){

    switch(mes){

        case 1: return 31;
        break;
        case 2: return 28;
        break;
        case 3: return 31;
        break;
        case 5: return 31;
        break;
        case 7: return 31;
        break;
        case 8: return 31;
        break;
        case 10: return 31;
        break;
        case 12: return 31;
        break;
        default: return 30;

    }

}

bool validarLoginEmpleado(int legajo, int PIN) {

    Empleados empleado;
    for(int pos=0;pos<empleado.contarRegistros();pos++){
        empleado.LeerDeDisco(pos);
        if(legajo==empleado.getleg()&&PIN==empleado.getpin()){
            return true;
        }
    }
    return false;
}

void MenuAdministrador(){
    bool password=false;
    int opcion;
    Empleados obj;
    char confirmarSalida;
    if(password==false){password=pedirContrasenia();}   ///ACA VALIDO ELUSUARIO ADMINISTRADOR.
    while(password){
        rlutil::setColor(rlutil::WHITE);
        rlutil::setBackgroundColor(rlutil::DARKGREY);
        rlutil::cls();
        cout << "\t\t\t\t\t\t\t  *** MENU ADMINISTRADOR ***" << endl << endl;
        cout << "\t\t\t\t\t\t*******************************************" << endl << endl;
        cout << "\t\t\t\t\t\t\t1 - CARGAR NUEVO EMPLEADO. " << endl << endl;
        cout << "\t\t\t\t\t\t\t2 - EDITAR EMPLEADO. " << endl << endl;
        cout << "\t\t\t\t\t\t\t3 - ELIMINAR EMPLEADO. " << endl << endl;
        cout << "\t\t\t\t\t\t\t4 - RESET PIN. " << endl << endl;
        cout << "\t\t\t\t\t\t\t5 - CALENDARIO EMPLEADO. " << endl << endl;
        cout << "\t\t\t\t\t\t\t6 - REPORTES. " << endl << endl;
        cout << "\t\t\t\t\t\t\t7 - LISTADOS. " << endl << endl;
        cout << "\t\t\t\t\t\t\t0 - VOLVER. " << endl << endl;
        cout << "\t\t\t\t\t\t*******************************************" << endl << endl;
        cout << "\t\t\t\t\t\t\tSELECCIONE OPCION: ";
        cin  >> opcion;
        rlutil::locate(60,23);
        if(opcion >= 1 && opcion < 7){
            system("cls");
        }
        switch(opcion){
            case 1: CargarEmpleado();
                break;
            case 2: editar_empleados();
                break;
            case 3: EliminarEmpleado();
                break;
            case 4: resetPIN();
                break;
            case 5: CalendarioDeHorarios();
                break;
            case 6: Reportes();
                break;
            case 7: Listados();
                break;
            case 0 : cout << endl << endl << "\t\t\t\t\t\t¿Confirma salir? (S/N) ";
                    cin >> confirmarSalida;
                    if (tolower(confirmarSalida) == 's'){
                        password=false;
                    }
                break;
        }
    }
}

void mostrar(){
Empleados obj;
cout<<endl<<obj.contarRegistros();
int pos;

    for(pos=0;pos<obj.contarRegistros();pos++){
            obj.LeerDeDisco(pos);
            cout<<"\t\t\t\t\t\tLISTADO --->"<<endl<<endl;
            cout << "\t\t\t\t\t\t" << "LEGAJO          : " << obj.getleg() << endl ;
            cout << "\t\t\t\t\t\t" << "NOMBRE          : " << obj.getnombre() << endl;
            cout << "\t\t\t\t\t\t" << "APELLIDO        : " << obj.getapellido() << endl;
            cout << "\t\t\t\t\t\t" << "DNI             : " << obj.getdni() << endl;
            cout << "\t\t\t\t\t\t" << "DOMICILIO       : " << obj.getdomicilio() << endl;
            cout << "\t\t\t\t\t\t" << "LOCALIDAD       : " << obj.getlocalidad() << endl;
            cout << "\t\t\t\t\t\t" << "PROVINCIA       : " << obj.getprovincia() << endl;
            cout << "\t\t\t\t\t\t" << "PAIS            : " << obj.getpais() << endl;
            cout << "\t\t\t\t\t\t" << "FECHA NACIMIENTO: " << obj.getFnacimiento().getDia() << "/" << obj.getFnacimiento().getMes() << "/" << obj.getFnacimiento().getAnio() <<endl;
            cout << "\t\t\t\t\t\t" << "GENERO          : " << obj.getgenero() << endl;
            cout << "\t\t\t\t\t\t" << "CARGA HORARIA   : " << obj.getcargaHoraria() << endl;
            cout << "\t\t\t\t\t\t" << "ROL             : ";
            if(obj.getRol() == true){
                cout << "Administrador." << endl;
            }
            else{
                cout << "Empleado." << endl;
            }
            cout << "\t\t\t\t\t" << "EMPLEADO ACTIVO : ";
            if(obj.getEliminado() == true){
             cout << "Si." << endl;
            }
            else{
                cout << "No." << endl;
            }
            cout << "\t\t\t\t\t\t------------------------------------------" << endl;
    }
    cout<<obj.contarRegistros()<<endl;
    cout << endl << "\t\t\t\t\t\t" << system ("pause");
}

void mostrarActivos(){
Empleados obj;
int pos;
    cout<<"\t\t\t\t\t\tLISTADO --->"<<endl<<endl;
    for(pos=0;pos<obj.contarRegistros();pos++){
            obj.LeerDeDisco(pos);
            if(obj.getEliminado()){
                cout << "\t\t\t\t\t\t" << "LEGAJO          : " << obj.getleg() << endl ;
                cout << "\t\t\t\t\t\t" << "NOMBRE          : " << obj.getnombre() << endl;
                cout << "\t\t\t\t\t\t" << "APELLIDO        : " << obj.getapellido() << endl;
                cout << "\t\t\t\t\t\t" << "DNI             : " << obj.getdni() << endl;
                cout << "\t\t\t\t\t\t" << "DOMICILIO       : " << obj.getdomicilio() << endl;
                cout << "\t\t\t\t\t\t" << "LOCALIDAD       : " << obj.getlocalidad() << endl;
                cout << "\t\t\t\t\t\t" << "PROVINCIA       : " << obj.getprovincia() << endl;
                cout << "\t\t\t\t\t\t" << "PAIS            : " << obj.getpais() << endl;
                cout << "\t\t\t\t\t\t" << "FECHA NACIMIENTO: " << obj.getFnacimiento().getDia() << "/" << obj.getFnacimiento().getMes() << "/" << obj.getFnacimiento().getAnio() <<endl;
                cout << "\t\t\t\t\t\t" << "GENERO          : " << obj.getgenero() << endl;
                cout << "\t\t\t\t\t\t" << "CARGA HORARIA   : " << obj.getcargaHoraria() << endl;
                cout << "\t\t\t\t\t\t" << "ROL             : ";
                if(obj.getRol() == true){
                    cout << "Administrador." << endl;
                }
                else{
                    cout << "Empleado." << endl;
                }
                cout << "\t\t\t\t\t\t" << "EMPLEADO ACTIVO : ";
                if(obj.getEliminado() == true){
                 cout << "Si." << endl;
                }
                else{
                    cout << "No." << endl;
                }
                cout << "\t\t\t\t\t\t------------------------------------------" << endl;
           }
    }
    cout << endl << "\t\t\t\t\t\t" << system ("pause");
}

void mostrarEliminados(){
Empleados obj;
int pos;
    cout<<"\t\t\t\t\t\tLISTADO --->"<<endl<<endl;
    for(pos=0;pos<obj.contarRegistros();pos++){
            obj.LeerDeDisco(pos);
            if(obj.getEliminado()==false){
                cout << "\t\t\t\t\t\t" << "LEGAJO          : " << obj.getleg() << endl ;
                cout << "\t\t\t\t\t\t" << "NOMBRE          : " << obj.getnombre() << endl;
                cout << "\t\t\t\t\t\t" << "APELLIDO        : " << obj.getapellido() << endl;
                cout << "\t\t\t\t\t\t" << "DNI             : " << obj.getdni() << endl;
                cout << "\t\t\t\t\t\t" << "DOMICILIO       : " << obj.getdomicilio() << endl;
                cout << "\t\t\t\t\t\t" << "LOCALIDAD       : " << obj.getlocalidad() << endl;
                cout << "\t\t\t\t\t\t" << "PROVINCIA       : " << obj.getprovincia() << endl;
                cout << "\t\t\t\t\t\t" << "PAIS            : " << obj.getpais() << endl;
                cout << "\t\t\t\t\t\t" << "FECHA NACIMIENTO: " << obj.getFnacimiento().getDia() << "/" << obj.getFnacimiento().getMes() << "/" << obj.getFnacimiento().getAnio() <<endl;
                cout << "\t\t\t\t\t\t" << "GENERO          : " << obj.getgenero() << endl;
                cout << "\t\t\t\t\t\t" << "CARGA HORARIA   : " << obj.getcargaHoraria() << endl;
                cout << "\t\t\t\t\t\t" << "ROL             : ";
                if(obj.getRol() == true){
                    cout << "Administrador." << endl;
                }
                else{
                    cout << "Empleado." << endl;
                }
                cout << "\t\t\t\t\t\t" << "EMPLEADO ACTIVO : ";
                if(obj.getEliminado() == true){
                 cout << "Si." << endl;
                }
                else{
                    cout << "No." << endl;
                }
                cout << "\t\t\t\t\t\t------------------------------------------" << endl;
           }
    }
    cout << endl << "\t\t\t\t\t\t" << system ("pause");
}

bool pedirContrasenia(){
    int legajo,PIN;
    cout << "\t\t\t\t\t\t  *** INGRESE USUARIO DE ADMINISTRADOR ***" << endl << endl;
    cout << "\t\t\t\t\t\t*******************************************" << endl << endl;
    cin.ignore();
    cout << "\t\t\t\t\t\t\tLEGAJO    : ";
    rlutil::setColor(rlutil::WHITE);
    cin>>legajo;
    cout << endl;
    cout << "\t\t\t\t\t\t\tPIN: ";
    rlutil::setColor(rlutil::DARKGREY);
    cin>>PIN;
    rlutil::setColor(rlutil::WHITE);

    Empleados empleado;
    for(int pos=0;pos<empleado.contarRegistros();pos++){
        empleado.LeerDeDisco(pos);
        if(legajo==empleado.getleg()&&PIN==empleado.getpin()&&empleado.getRol()){
            cout << endl;
            cout << "\t\t\t\t\t\t\tBIENVENIDO!!! " << endl << endl;
            cout << "\t\t\t\t\t\t\tPresione una TECLA para continuar " << endl << endl;
            system("pause > nul");
            system("cls");
            return true;
        }
    }
        cout << endl << "\t\t\t\t\t\t\tUSUARIO INVALIDO!!!" << endl << endl<<"\t\t\t\t\t\t\tPresione una tecla";
        system("pause > nul");
        system("cls");
        return false;
}

void Listados(){
    int opcion;
    char confirmarSalida;

    rlutil::setColor(rlutil::WHITE);
    rlutil::setBackgroundColor(rlutil::DARKGREY);
    rlutil::cls();
    cout << "\t\t\t\t\t\t\t  *** LISTADOS ***" << endl << endl;
    cout << "\t\t\t\t\t\t*******************************************" << endl << endl;
    cout << "\t\t\t\t\t\t\t1 - LISTAR EMPLEADOS ACTIVOS. " << endl << endl;
    cout << "\t\t\t\t\t\t\t2 - LISTAR EMPLEADOS DADOS DE BAJA. " << endl << endl;
    cout << "\t\t\t\t\t\t\t3 - LISTAR FICHA EMPLEADO. " << endl << endl;
    cout << "\t\t\t\t\t\t\t4 - LISTAR JORNADA EMPLEADO POR MES. " << endl << endl;
    cout << "\t\t\t\t\t\t\t5 - LISTAR JORNADA POR FECHA TODOS LOS EMPLEADOS. " << endl << endl;
    cout << "\t\t\t\t\t\t\t6 - LISTAR HORARIO EMPLEADO POR MES. " << endl << endl;
    cout << "\t\t\t\t\t\t\t7 - LISTAR TODOS LOS HORARIO POR FECHA. " << endl << endl;
    cout << "\t\t\t\t\t\t\t8 - LISTAR AUSENCIA POR DIA. " << endl << endl;
    cout << "\t\t\t\t\t\t\t0 - VOLVER. " << endl << endl;
    cout << "\t\t\t\t\t\t*******************************************" << endl << endl;
    cout << "\t\t\t\t\t\t\tSELECCIONE OPCION: ";
    cin  >> opcion;
    rlutil::locate(60,17);
    if(opcion >= 1 && opcion < 6){
        system("cls");
    }
    switch(opcion){
        case 1: mostrarActivos(); //LISTAR EMPLEADOS ACTIVOS
            break;
        case 2: mostrarEliminados(); //LISTAR EMPLEADOS DADOS DE BAJA
            break;
        case 3: mostrarEmpleado();
            break;
        case 4: mostrarJorEmpXMes();
            break;
        case 5: mostrarJorXFec();
            break;
        case 6: mostrarHorarioXMes();
            break;
        case 7: mostrarHorarioXFec();
            break;
        case 8: ausencias();
            break;
        case 0 : cout << endl << endl << endl << endl << endl << endl
                << endl << endl << endl << endl << "\t\t\t\t\t\t\t¿Confirma salir? (S/N) ";
                cin >> confirmarSalida;
                if (tolower(confirmarSalida) == 's'){
                    system("cls");
                }
            break;
        default : rlutil::locate(41,21);
                cout << "OPCION INVALIDA!!!" << endl << endl;
                system("pause > nul");
                system("cls");
            break;
    }
}

horas_A_minutos(int hora){

return hora*60;

}

void guardarFichada(int legajo){

    FechaHora hora;
    Empleados empleado;
    Jornada aux;
    float fin=0;
    bool salir=0;
    for(int pos=0;pos<aux.contarRegistros();pos++){
        aux.leerDeDisco(pos);
        if(hora.getAnio()==aux.getFecha().getAnio()&&
           hora.getMes()==aux.getFecha().getMes()&&
           hora.getDia()==aux.getFecha().getDia()&&
           legajo==aux.getLegajo().getleg()){
            aux.setHoraSalida(hora);
            int mnSalida=aux.getHoraSalida().getMinuto()+horas_A_minutos(aux.getHoraSalida().getHora());
            int mnEntrada=aux.getHoraEntrada().getMinuto()+horas_A_minutos(aux.getHoraEntrada().getHora());
            fin=(mnSalida-mnEntrada)/60;
            if((mnSalida-mnEntrada)%60>29){
                fin+=0.5;
            }
            aux.setHoraTotal(fin);
            aux.guardarEnDisco(pos);
            cout<<endl<<"\t\t\t\t\t\t\tSALIDA GUARDADA"<<endl<<endl;
            cout<<endl<<"\t\t\t\t\t\t\tFICHASTE A LAS "<<aux.getHoraSalida().getHora()<<":"<<aux.getHoraSalida().getMinuto()<<endl;
            cout<< "\t\t\t\t\t\t\t"; system("pause");
            /*cout<<endl<<endl<<"\t\t\t\t\t\t\t"<<aux.getFecha().getDia()<<"/"<<aux.getFecha().getMes()<<"/"<<aux.getFecha().getAnio()<<endl
            <<"\t\t\t\t\t\t\tLegajo : "<<aux.getLegajo().getleg()<<endl
            <<"\t\t\t\t\t\t\tEntrada: "<<aux.getHoraEntrada().getHora()<<":"<<aux.getHoraEntrada().getMinuto()<<endl
            <<"\t\t\t\t\t\t\tSalida : "<<aux.getHoraSalida().getHora()<<":"<<aux.getHoraSalida().getMinuto()<<endl
            <<"\t\t\t\t\t\t\tTotal  : "<<aux.getHoraTotal()<<endl
            <<"\t\t\t\t\t\t\tEstado : "<<aux.getEstado()<<endl<<endl;
            cout << "\t\t\t\t\t\t\t" << system("pause");*/
            salir=1;
           }
    }
    if(salir==0){
        Calendario calendario;
        int estado=0, auxHora, auxMin ,pos=0;
        while(calendario.leerDeDisco(pos++)){
            if(hora.getAnio()==calendario.getFecha().getAnio()&&
               hora.getMes()==calendario.getFecha().getMes()&&
               hora.getDia()==calendario.getFecha().getDia()&&
               legajo==calendario.getLegajo().getleg()){
                auxHora=calendario.getFecha().getHora();
                auxMin=calendario.getFecha().getMinuto();
                break;
               }
        }
        int resultado;
        auxHora=horas_A_minutos(auxHora);
        resultado=(horas_A_minutos(hora.getHora())+hora.getMinuto())-(auxHora+auxMin);
        if(resultado>15){estado=-1;}
        empleado.LeerDeDisco(buscarEmpleado(legajo));
        Jornada jornada(hora,empleado,hora,hora,fin,estado);
        jornada.guardarEnDisco();
        cout<<endl<<"\t\t\t\t\t\t\tENTRADA GUARDADA"<<endl<<endl;
        cout<<endl<<"\t\t\t\t\t\t\tFICHASTE A LAS "<<jornada.getHoraEntrada().getHora()<<":"<<jornada.getHoraEntrada().getMinuto()<<endl;
        cout<<"\t\t\t\t\t\t\t" << system("pause");
        /*cout<<endl<<endl<<"\t\t\t\t\t\t\t"<<jornada.getFecha().getDia()<<"/"<<jornada.getFecha().getMes()<<"/"<<jornada.getFecha().getAnio()<<endl
        <<"\t\t\t\t\t\t\tLegajo : "<<jornada.getLegajo().getleg()<<endl
        <<"\t\t\t\t\t\t\tEntrada: "<<jornada.getHoraEntrada().getHora()<<":"<<jornada.getHoraEntrada().getMinuto()<<endl
        <<"\t\t\t\t\t\t\tSalida : "<<jornada.getHoraSalida().getHora()<<":"<<jornada.getHoraSalida().getMinuto()<<endl
        <<"\t\t\t\t\t\t\tTotal  : "<<jornada.getHoraTotal()<<endl
        <<"\t\t\t\t\t\t\tAusente: "<<jornada.getAusente()<<endl
        <<"\t\t\t\t\t\t\tEstado : "<<jornada.getEstado()<<endl<<endl;
        cout << "\t\t\t\t\t\t" << system("pause");*/
    }

}

void Leg_pin_incorrecto(){
    cout<<endl;
    cout<<"\t\t\t\t\t\t\t ========================="<<endl;
    cout<<"\t\t\t\t\t\t\t| Legajo o PIN incorrecto |"<<endl;
    cout<<"\t\t\t\t\t\t\t ========================="<<endl;
    cout<<endl;cout<<endl;cout<<endl;
    cout<<"\t\t\t\t\t\t\t----------------------------------"<<endl;
    cout<<"\t\t\t\t\t\t\t";
    cout << system ("pause");
    cout<<"-------------------------"<<endl;
    system ("cls");
}

void Cerrar_Programa(){
Empleados reg;
int leg, pin;
bool activo;
system ("cls");
cout << "\t\t\t\t\t\t\t  *** CERRAR PROGRAMA ***" << endl << endl;
cout << "\t\t\t\t\t\t*******************************************" << endl << endl;
cout<<"\t\t\t\t\t\t Legajo de admin -> ";
rlutil::setColor(rlutil::WHITE);
rlutil::setColor(rlutil::DARKGREY);
cin>>leg;
cout<<endl;
rlutil::setColor(rlutil::WHITE);
cout<<"\t\t\t\t\t\t PIN de admin -> ";
rlutil::setColor(rlutil::DARKGREY);
cin>>pin;
rlutil::setColor(rlutil::WHITE);
cout<<endl;
activo=validarLoginEmpleado(leg,pin);
    if(activo==true){
    int pos;
    pos=buscarEmpleado(leg);
    reg.LeerDeDisco(pos);
        if(reg.getleg()==leg && pin==reg.getpin()&&reg.getRol()){
        exit (0);
        }
        else{
        cout<<"\t\t\t\t\t\t ==============================="<<endl;
        cout<<"\t\t\t\t\t\t| No tiene rol de administrador |"<<endl;
        cout<<"\t\t\t\t\t\t ==============================="<<endl;
        cout << endl << "\t\t\t\t\t\t" << system("pause");
        }
    }
    if(activo!=true){
    Leg_pin_incorrecto();
    }
}

bool ValidarLegajoExistente(int legajo){

    Empleados obj;
    int pos = 0;
    while (obj.LeerDeDisco(pos++)){
        if ( obj.getleg() == legajo){
            cout << "\t\t\t\t\t\t\tEL LEGAJO YA ESTA UTILIZADO." << endl << endl;
            return false;
        }
    }
    return true;
}

bool ValidarDiaMes(int dia, int mes){

    if ( mes <= 0 || mes > 12){
        cout << endl << "\t\t\t\t\t\t\tNUMERO DE MES INVALIDO." << endl << endl;
        cout << endl << "\t\t\t\t\t\t"; system ("pause");
        return false;
    }
    if(mes == 4 || mes == 6 || mes == 9 || mes == 11){
        if ( dia <= 0 || dia > 30){
            cout << endl << "\t\t\t\t\t\t\tNUMERO DE DIA INVALIDO." << endl << endl;
            cout << endl << "\t\t\t\t\t\t"; system ("pause");
            return false;
        }
    }
    if(mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12){
        if ( dia <= 0 || dia > 31){
            cout << endl << "NUMERO DE DIA INVALIDO." << endl << endl;
            cout << endl << "\t\t\t\t\t\t"; system ("pause");
            return false;
        }
    }
    if(mes == 2){
        if ( dia <= 0 || dia > 28){
            cout << endl << "NUMERO DE DIA INVALIDO." << endl << endl;
            cout << endl << "\t\t\t\t\t\t"; system ("pause");
            return false;
        }
    }
    return true;
}

bool ValidarHoraMinutos(int hora, int minutos){

    if ( minutos < 0 || minutos > 59){
        cout << endl << "\t\t\t\t\t\t\tMINUTOS INVALIDOS." << endl << endl;
        cout << endl << "\t\t\t\t\t\t" << system ("pause");
        return false;
    }
    if ( hora < 0 || hora > 23){
        cout << endl << "\t\t\t\t\t\tHORA INVALIDA." << endl << endl;
        cout << endl << "\t\t\t\t\t\t" << system ("pause");
        return false;
    }
    return true;
}

bool ValidarActivo(int legajo){

    Empleados obj;
    int registro;
    registro=buscarEmpleado(legajo);
    if(registro==-1){
        cout<<"NO EXISTE EMPLEADO CON ESE LEGAJO...!"<<endl;
        system("pause");
        return false;
    }
    obj.LeerDeDisco(registro);
    return obj.getEliminado();
}

int diaSemana(int dia,int mes,int anio){
    int d    = dia   ; //Day     1-31
    int m    = mes    ; //Month   1-12`
    int y    = anio ; //Year    2013`

    int weekday  = (d += m < 3 ? y-- : y - 2, 23*m/9 + d + 4 + y/4- y/100 + y/400)%7;
    return weekday;
}

void reporte1(){

    int mes,anio;
    cout<<"INGRESE EL NUMERO DE MES QUE DESEA VER: ";cin>>mes;
    cout<<endl<<"INGRESE EL YEAR QUE DESEA VER: ";cin>>anio;
    if(mes<1||mes>12){
        cout<<endl<<"MES INCORRECTO...!"; system("pause");return;
    }
    system ("cls");
    cout<<"\t\t\t\t\t\t\t\tPERIODO: "<<mes<<"-"<<anio<<endl<<endl<<endl;
    int posicion=0;
    int can=mesCantDias(mes);
    Empleados empleado;
    while(empleado.LeerDeDisco(posicion++)){
        bool mostrar=false;
        int teorico=0;
        int fichada=0;
        float hsFichada=0;
        int hsTeorico=0;
        int legajo=empleado.getleg();
        for(int i=1;i<=can;i++){
            int pos=0;
            Calendario calendario;
            while(calendario.leerDeDisco(pos++)){
                if(legajo==calendario.getLegajo().getleg()
                   &&anio==calendario.getFecha().getAnio()
                   &&mes==calendario.getFecha().getMes()
                   &&i==calendario.getFecha().getDia()
                   &&calendario.getHoraEntrada().getHora()!=-1){
                    teorico++;
                    //hsTeorico+=calendario.getHoraSalida().getHora()-calendario.getHoraEntrada().getHora();
                    hsTeorico+=calendario.getHoraTotal();
                    mostrar=true;
                    ///break;
                }
            }
            Jornada jornada;
            pos=0;
            while(jornada.leerDeDisco(pos++)){
                if(legajo==jornada.getLegajo().getleg()
                   &&anio==jornada.getFecha().getAnio()
                   &&mes==jornada.getFecha().getMes()
                   &&i==jornada.getFecha().getDia()){
                    fichada++;
                    hsFichada+=jornada.getHoraTotal();
                    //hsFichada+=jornada.getHoraSalida().getHora()-jornada.getHoraEntrada().getHora();
                    ///break;
                }
            }
        }
        if(mostrar){
            int balance=hsFichada-hsTeorico;
            cout<<"-----------------------------------------------------------------"<<endl;
            cout<<setw(7)<<"LEGAJO"<<" ||"<<setw(10)<<"AUSENCIAS"<<" ||"<<setw(12)<<"HS TEORICAS"<<" ||"<<setw(15)<<" HS REGISTRADAS"<<" ||"<<" BALANCE"<<endl;
            cout<<endl<<setw(7)<<legajo<<" ||"<<setw(10)<<teorico-fichada<<" ||"<<setw(12)<<hsTeorico<<" ||"<<setw(15)<<hsFichada<<" ||"<<balance<<endl;
            cout<<"-----------------------------------------------------------------"<<endl;
        }
    }
    system("pause");
}

void ausencias(){

    system("cls");
    int pos=0, anio, mes, dia;
    Calendario calendario;
    Jornada jornada;

    cout<<"INGRESE LA FECHA QUE DESEA VER"<<endl;
    cout<<"ANIO: ";cin>>anio;cout<<endl<<"MES: ";cin>>mes;cout<<endl<<"DIA: ";cin>>dia;
    if(!ValidarDiaMes(dia,mes)){
        return;
    }
    //bool ausencia=true;
    while(calendario.leerDeDisco(pos++)){
            bool ausencia=true;
        if(calendario.getFecha().getAnio()==anio&&
           calendario.getFecha().getMes()==mes&&
           calendario.getFecha().getDia()==dia){//cout<<endl<<"paso por acaaa"<<endl;
            if(calendario.getHoraEntrada().getHora()==-1){
                ausencia=false;
            }
            int p=0;
            while(jornada.leerDeDisco(p++)){
                if(calendario.getLegajo().getleg()==jornada.getLegajo().getleg()&&
                jornada.getFecha().getAnio()==anio&&
                jornada.getFecha().getMes()==mes&&
                jornada.getFecha().getDia()==dia){
                    ausencia=false;
                }
            }
            //system ("cls");
            //cout<<endl<<ausencia;
            if(ausencia){
                cout<<endl<<"-------------------------------------------------------------"<<endl;
                cout<<"LEGAJO: "<<calendario.getLegajo().getleg()<<"\t\tAUSENTE."<<endl
                <<"-------------------------------------------------------------"<<endl;
            }
        }
    }
    system("pause");
    Listados();
}

string Estado(int estado){
    string texto;
    switch(estado){

        case -1: texto="TARDE";
        break;
        case 0: texto="CORRECTO";
        break;
    }
return texto;
}

