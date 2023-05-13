#include <iostream>
#include <string>
#include "FUNCIONES.h"
#include "rlutil.h"
#include "administrador.h"
#include "Empleados.h"
using namespace std;


Administrador::Administrador(){}

void Administrador::setUsuarioAdmin(char *Usuario){
    strcpy(_Usuario, Usuario);
}

void Administrador::setContraseniaAdmin(char *Contrasenia){
    strcpy(_Contrasenia, Contrasenia);
}

char *Administrador::getUsuarioAdmin(){
    return _Usuario;
}

char *Administrador::getContraseniaAdmin(){
    return _Contrasenia;
}

bool Administrador::grabarEnDisco(){

    FILE *p;
    p = fopen("Administradores.dat","ab");
    if(p == NULL){
        cout << "\t\t\t\t\t\t\tNO SE PUDO ABRIR EL ARCHIVO.";
        return false;
    }
    bool ok = fwrite(this,sizeof(Administrador),1,p);
    if (ok == true){
        cout << endl << "\t\t\t\t\t\t\tREGISTRO GUARDADO."<< endl << endl;
    }
    else{
        cout << endl << "\t\t\t\t\t\t\tNO SE PUDO GUARDAR EL REGISTRO."<< endl << endl;
    }
    fclose(p);
    return ok;
}

bool Administrador::leerDeDisco(int pos){
    FILE *p;
    p = fopen("Administradores.dat","rb");
    if(p == NULL){
        cout << endl << endl << "\t\t\t\t\t\t\tNO HAY USUARIOS REGISTRADOS." << endl << endl;
        cout << "\t\t\t\t\t\t\t" << system("pause");
        system("cls");
        return false;
    }
    else{
        fseek(p,sizeof(Administrador)* pos,SEEK_SET);
        bool ok = fread(this, sizeof(Administrador), 1, p);
        fclose(p);
        return ok;
    }
}

void CargarEmpleado(){

    string apellido, nombre, domicilio, localidad, provincia, pais, genero;
    int DNI, legajo, pin, dia, mes, anio, carga, genNum;
    bool ok, admin, stop=false;

    cout << "\t\t\t\t\t\t\t  *** INGRESE LOS DATOS ***" << endl << endl;
    cout << "\t\t\t\t\t\t*******************************************" << endl << endl;
    cout << "\t\t\t\t\t\t\t** LEGAJO       : ";
    cin  >> legajo;
    if(ValidarLegajoExistente(legajo) == false){   ///ESTE VALIDA SI EL LEGAJO YA ESTA EN USO POR OTRO EMPLEADO,
        system("pause");
        return;
        //MenuAdministrador();                       ///PERO A VERDAD Q ESTA DE MAS PORQ TENDRIA Q USAR LA FUNCION BUSCAREMPLEADO.
        //cout << endl << "\t\t\t\t\t\t" << system ("pause");
    }
    cout << "\t\t\t\t\t\t\t** NOMBRE       : ";
    cin.ignore();
    getline(cin,nombre);
    cout << "\t\t\t\t\t\t\t** APELLIDO     : ";
    getline(cin,apellido);
    cout << "\t\t\t\t\t\t\t** DNI          : ";
    cin  >> DNI;
    cout << "\t\t\t\t\t\t\t** DOMICILIO    : ";
    cin.ignore();
    getline(cin,domicilio);
    cout << "\t\t\t\t\t\t\t** LOCALIDAD    : ";
    getline(cin,localidad);
    cout << "\t\t\t\t\t\t\t** PROVINCIA    : ";
    getline(cin,provincia);
    cout << "\t\t\t\t\t\t\t** PAIS         : ";
    getline(cin,pais);
    cout << "\t\t\t\t\t\t\t** FECHA NACIMIENTO dd/mm/aaaa: ";
    //rlutil::locate(73,13);
    cin  >> dia;
    rlutil::locate(91,13);
    cout << "/";
    //rlutil::locate(76,13);
    cin  >> mes;
    rlutil::locate(94,13);
    cout << "/";
    //rlutil::locate(79,13);
    cin  >> anio;
    if(!ValidarDiaMes(dia,mes)){   ///VALIDA Q NO PONGAN UN MES INCORRECTO Y Q TAMPOCO COLOQUEN UN DIA Q NO CORRESPONDA AL MES
        dia=1;mes=1;               ///COMO POR EJEMPLO 30 DE FEBRERO.
        cout<<"FECHA INGRESADA INVALIDA. SE COLOCARA UNA FECHA POR DEFECTO";
        system("pause");
    }
    cout << "\t\t\t\t\t\t\t** 1 para Masculino 2 para Femenino"<<endl;
    cout << "\t\t\t\t\t\t\t** GENERO       : ";
    cin  >> genNum;
    while(stop==false){
        if(genNum==1||genNum==2){
            if(genNum==1){
                genero="m";
            }else genero="F";
            stop=true;
        }
        else{
            cout << "\t\t\t\t\t\t\t** El genero es representado con un 1 para Masculino y 2 para Femenino."<<endl;
            cout << "\t\t\t\t\t\t\t** GENERO       : ";
            cin  >> genNum;
        }
    }
    cout << "\t\t\t\t\t\t\t** CARGA HORARIA: ";
    cin  >> carga;
    cout << "\t\t\t\t\t\t\t** ROL ADMIN    : ";
    cin  >> admin;
    FechaHora fnac(anio,mes,dia);
    FechaHora ingreso;
    Empleados obj(legajo,pin,nombre,apellido,DNI,domicilio,localidad,provincia,pais,fnac,genero,ingreso,carga,admin);
    ok = obj.GuardarEnDisco();
    cout << endl << "\t\t\t\t\t\t\t" << system("pause");
    system("cls");
    return;
}

void resetPIN(){

    int legajo;
    rlutil::setColor(rlutil::WHITE);
    rlutil::setBackgroundColor(rlutil::DARKGREY);
    rlutil::cls();
    cout << "\t\t\t\t\t\t\t  *** RESET PIN ***" << endl << endl;
    cout << "\t\t\t\t\t\t*******************************************" << endl << endl;
    cout << "\t\t\t\t\t\tINGRESE EL LEGAJO DEL EMPLEADO: ";cin>>legajo;
    if(ValidarActivo(legajo)==false){
        cout<<"EL EMPLEADO NO ESTA ACTIVO....!"<<endl;
        system("pause");return;      ///ACA PIENSO Q LO PODRIA MEJORAR YA Q UTILIZO VALIDAR ACITIVO, Y VALIDR ACTIVO YA TIENE
    }                                ///BUSCAREMPLEADO, Y MAS ABAJO VUELVO A USAR BUSCAREMPLEADO
    int registro=buscarEmpleado(legajo);
    Empleados empleado;
    empleado.LeerDeDisco(registro);
    empleado.setpin(1234);
    empleado.GuardarEnDisco(registro);
    cout<<"\t\t\t\t\t\tSE REALIZO EL RESET DE PIN, AHORA EL NUEVO PIN ES 1234"<<endl;
    system("pause");return;
}



