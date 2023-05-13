#include <cstring>
#include <iostream>
using namespace std;
#include "Empleados.h"
#include "fecha.h"
#include "jornada.h"
#include "FUNCIONES.h"
#include "rlutil.h"
#include "calendario.h"
#include <iomanip>

///CONSTRUCTOR

Empleados::Empleados(int legajo,int _pin,string _nombre,string _apellido,int _dni,string _domicilio,string _localidad,string _provincia,string _pais,FechaHora fnac,string _genero,FechaHora ingreso,int carga_horaria,bool admin, bool act){

leg=legajo; pin=1234; strcpy(nombre, _nombre.c_str());strcpy(apellido, _apellido.c_str()); dni=_dni; strcpy(domicilio, _domicilio.c_str()); strcpy(localidad, _localidad.c_str()); strcpy(provincia, _provincia.c_str()); strcpy(pais, _pais.c_str());
fNacimiento=fnac; strcpy(genero, _genero.c_str()); fechaIngreso=ingreso; cargaHoraria=carga_horaria; adm=admin; activo=act;
}

Empleados::Empleados(){}
///GET


string Empleados::getnombre(){
    string nom;
    nom=nombre;
    return nom;}

string Empleados::getapellido(){
    string apell(apellido);
    return  apell;}

int Empleados::getleg(){return leg;}
int Empleados::getpin(){return pin;}
int Empleados::getdni(){return dni;}
string Empleados::getdomicilio(){string dom(domicilio); return dom;}
string Empleados::getlocalidad(){string loc(localidad); return loc;}
string Empleados::getprovincia(){string prov(provincia); return prov;}
string Empleados::getpais(){string p(pais); return p;}
FechaHora Empleados::getFnacimiento(){return fNacimiento;}
string Empleados::getgenero(){string gen(genero); return gen;}
FechaHora Empleados::getFechaIngreso(){return fechaIngreso;}
int Empleados::getcargaHoraria(){return cargaHoraria;}
bool Empleados::getRol(){return adm;}
bool Empleados::getEliminado(){return activo;}


///SETS
    void Empleados::setnombre(string nom){strcpy(nombre, nom.c_str());}
    void Empleados::setapellido(string ape){strcpy(apellido, ape.c_str());}
    void Empleados::setleg(int legajo){leg=legajo;}
    void Empleados::setpin(int p){pin=p;}
    void Empleados::setdni(int doc){dni=doc;}
    void Empleados::setdomicilio(string dom){strcpy(domicilio, dom.c_str());}
    void Empleados::setlocalidad(string loc){strcpy(localidad, loc.c_str());}
    void Empleados::setprovincia(string prov){strcpy(provincia, prov.c_str());}
    void Empleados::setpais(string p){strcpy(pais, p.c_str());}
    void Empleados::setFnacimiento(FechaHora nac){fNacimiento=nac;}
    void Empleados::setgenero(string g){strcpy(genero, g.c_str());}
    void Empleados::setcargaHoraria(int carga){cargaHoraria=carga;}
    void Empleados::setRol(bool admin){adm=admin;}
    void Empleados::setEliminado(bool on){activo=on;}


///METODO DE LA CLASE

int Empleados::contarRegistros(){
    FILE *p = fopen("datos/Empleados.dat", "rb");
    if (p == NULL){
        return 0;
    }
    size_t bytes;
    int cant_reg;

    fseek(p, 0, SEEK_END);
    bytes = ftell(p);
    fclose(p);
    cant_reg = bytes / sizeof(Empleados);
    return cant_reg;
}

bool Empleados::LeerDeDisco(int nroRegistro){
    FILE *p = fopen("datos/Empleados.dat", "rb");
    if (p == NULL){
        return false;
    }
    fseek(p, nroRegistro * sizeof(Empleados), SEEK_SET);
    bool ok = fread(this, sizeof(Empleados), 1, p);
    fclose(p);
    return ok;
}

bool Empleados::GuardarEnDisco(){
    FILE *p = fopen("datos/Empleados.dat", "ab");
    if (p == NULL){
        cout << "\t\t\t\t\tNo se pudo abrir el archivo.";
        return false;
    }
    bool guardo = fwrite(this, sizeof(Empleados), 1, p);
    if(guardo == true){
        cout << endl << endl << "\t\t\t\t\tRegistro guardado.";
    }
    fclose(p);
    return guardo;
}

bool Empleados::GuardarEnDisco(int nroRegistro){
    FILE *p = fopen("datos/Empleados.dat", "rb+");
    if (p == NULL){
        return false;
    }
    fseek(p, nroRegistro * sizeof(Empleados), SEEK_SET);
    bool guardo = fwrite(this, sizeof(Empleados), 1, p);
    fclose(p);
    return guardo;
}

/// FUNCIONES DE LA CLASE

int buscarEmpleado(int legajo){
    Empleados aux;
    for(int pos=0;pos<aux.contarRegistros();pos++){
        aux.LeerDeDisco(pos);
        if(aux.getleg()==legajo){
            return pos;
        }
    }
    return -1;
}

bool editar_empleados(){

    Empleados reg;
    FechaHora fnac;
    int legajo, pos, opcion, dia, mes, anio;
    char confirmarSalida;


    cout << "\t\t\t\t\t\t\t\t***EDITAR EMPLEADO***" << endl << endl;
    cout << "\t\t\t\t\t\t\t*******************************************" << endl << endl;
    cout << "\t\t\t\t\t\t\t\tINGRESE LEGAJO: ";
    cin  >> legajo;

    pos = buscarEmpleado(legajo);
    cout << endl << endl << "\t\t\t\t\t\t\t" << system("pause");
    if(pos == -1){
        cout << endl << endl,
        cout << "\t\t\t\t\t\t\tNO EXISTE EL LEGAJO INGRESADO." << endl << endl,
        cout << "\t\t\t\t\t\t\t" << system("pause");
        system("cls");
        return false;
    }

    rlutil::setColor(rlutil::WHITE);
    rlutil::setBackgroundColor(rlutil::DARKGREY);
    rlutil::cls();
    cout << "\t\t\t\t\t\t\t  *** MENU EDITAR LEGAJO "<<legajo<<" ***" << endl << endl;
    cout << "\t\t\t\t\t\t*******************************************" << endl << endl;
    cout << "\t\t\t\t\t\t\t1  - NOMBRE. " << endl << endl;
    cout << "\t\t\t\t\t\t\t2  - APELLIDO. " << endl << endl;
    cout << "\t\t\t\t\t\t\t3  - DNI. " << endl << endl;
    cout << "\t\t\t\t\t\t\t4  - DOMICILIO. " << endl << endl;
    cout << "\t\t\t\t\t\t\t5  - LOCALIDAD. " << endl << endl;
    cout << "\t\t\t\t\t\t\t6  - PROVINCIA. " << endl << endl;
    cout << "\t\t\t\t\t\t\t7  - PAIS. " << endl << endl;
    cout << "\t\t\t\t\t\t\t8  - FECHA NACIMIENTO. " << endl << endl;
    cout << "\t\t\t\t\t\t\t9  - GENERO. " << endl << endl;
    cout << "\t\t\t\t\t\t\t10 - CARGA HORARIA. " << endl << endl;
    cout << "\t\t\t\t\t\t\t11 - ROL. " << endl << endl;
    cout << "\t\t\t\t\t\t\t0  - VOLVER. " << endl << endl;
    cout << "\t\t\t\t\t\t*******************************************" << endl << endl;
    cout << "\t\t\t\t\t\t\tSELECCIONE OPCION: ";
    cin  >> opcion;
    string cambio;
    int entero;
    reg.LeerDeDisco(pos);
    rlutil::locate(60,31);
    if(opcion >= 0 && opcion < 12){
        system("cls");
    } else{
        cout<<"OPCION ERRONEA...!"; system("pause");MenuAdministrador();
    }
    switch(opcion){
        case 1:
            cout<<"\t\t\t\t\t\t\tINTRODUCE NOMBRE NUEVO: ";
            cin.ignore();
            getline(cin,cambio);
            reg.setnombre(cambio);
            break;
        case 2:
            cout<<"\t\t\t\t\t\t\tINTRODUCE APELLIDO NUEVO: ";
            cin.ignore();
            getline(cin,cambio);
            reg.setapellido(cambio);
            break;
        case 3:
            cout<<"\t\t\t\t\t\t\tINTRODUCE DNI NUEVO: ";
            cin>>entero;
            reg.setdni(entero);
            break;
        case 4:
            cout<<"\t\t\t\t\t\t\tINTRODUCE DOMICILIO NUEVO: ";
            cin.ignore();
            getline(cin,cambio);
            reg.setdomicilio(cambio);
            break;
        case 5:
            cout<<"\t\t\t\t\t\t\tINTRODUCE LOCALIDAD NUEVA: ";
            cin.ignore();
            getline(cin,cambio);
            reg.setlocalidad(cambio);
            break;
        case 6:
            cout<<"\t\t\t\t\t\t\tINTRODUCE PROVINCIA NUEVA: ";
            cin.ignore();
            getline(cin,cambio);
            reg.setprovincia(cambio);
            break;
        case 7:
            cout<<"\t\t\t\t\t\t\tINTRODUCE DOMICILIO PAIS: ";
            cin.ignore();
            getline(cin,cambio);
            reg.setpais(cambio);
            break;
        case 8:
            cout<<"\t\t\t\t\t\t\tINTRODUCE DIA DE NACIMIENTO NUEVO: ";
            cin>>dia;
            cout<<endl<<"\t\t\t\t\t\t\tINTRODUCE MES DE NACIMIENTO NUEVO: ";
            cin>>mes;
            cout<<endl<<"\t\t\t\t\t\t\tINTRODUCE YEAR DE NACIMIENTO NUEVO: ";
            cin>>anio;
            if(!ValidarDiaMes(dia,mes)){
                return 0;
            }
            fnac.setAnio(anio);fnac.setMes(mes);fnac.setDia(dia);
            reg.setFnacimiento(fnac);
            break;
        case 9:
            cout<<"\t\t\t\t\t\t\tINTRODUCE GENERO NUEVO: ";
            cin.ignore();
            getline(cin,cambio);
            reg.setgenero(cambio);
            break;
        case 10:
            cout<<"\t\t\t\t\t\t\tINTRODUCE CARGA HORARIA NUEVA: ";
            cin>>entero;
            reg.setcargaHoraria(entero);
            break;
        case 11:
            if(reg.getRol()){reg.setRol(false);
            }else reg.setRol(true);
            reg.GuardarEnDisco(pos);
            break;
        case 0 : cout << endl << endl << "\t\t\t\t\t\t\t¿Confirma salir? (S/N) ";
                cin >> confirmarSalida;
                if (tolower(confirmarSalida) == 's'){
                    MenuAdministrador();
                }
            break;
        default:
            MenuAdministrador();
    }
    reg.GuardarEnDisco(pos);cout<<endl<<"\t\t\t\t\t\t\tCAMBIO REALIZADO CON EXITO...!"<<endl;
    cout<<endl<<endl<<"\t\t\t\t\t\t\t"<<system("pause");
}

bool EliminarEmpleado(){

    Empleados reg;
    int legajo, pos;

    cout << "\t\t\t\t\t\t\t***ELIMINAR EMPLEADO***" << endl << endl;
    cout << "\t\t\t\t\t\t*******************************************" << endl << endl;
    cout << "\t\t\t\t\t\t\tINGRESE LEGAJO: ";
    cin  >> legajo;

    pos = buscarEmpleado(legajo);
    cout << endl << "\t\t\t\t\t\t\t" << system("pause");
    if(pos == -1){
        cout << endl << endl,
        cout << "\t\t\t\t\t\t\tNO EXISTE EL LEGAJO INGRESADO." << endl << endl,
        cout << "\t\t\t\t\t\t\t";system("pause");
        system("cls");
        return false;
    }
    reg.LeerDeDisco(pos);
    reg.setEliminado(false);
    reg.GuardarEnDisco(pos);
    cout << endl << "\t\t\t\t\t\t\tEMPLEADO DADO DE BAJA." << endl << endl,
    cout << "\t\t\t\t\t\t\t";system("pause");
    system("cls");
    return true;
}

void mostrarEmpleado(){
int pos, legajo;
Empleados obj;
cout << "\t\t\t\t\t   ---------------------------------------------------" << endl;
cout<<"\t\t\t\t\t    Cual es el legajo del empleado que buscas? -> ";
cin>>legajo;
cout << "\t\t\t\t\t   ---------------------------------------------------" << endl;
pos=buscarEmpleado(legajo);
if(pos==-1){return;}
obj.LeerDeDisco(pos);
        cout << endl;
        cout << "\t\t\t\t\t\t-------------- Empleado " << legajo << " --------------" << endl;
        cout << "\t\t\t\t\t\t------------------------------------------" << endl;
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
system("pause");
system("cls");
Listados();
}

void mostrarJorEmpXMes(){

    int mes, anio,legajo;
    cout<<"COLOQUE EL LEGAJO DEL EMPLEADO QUE DESEA VER EL LISTADO...!"<<endl;
    cout<<"Legajo: ";cin>>legajo;
    if(buscarEmpleado(legajo)==-1){
        cout<<"Legajo inexistente...!"<<endl;
        system("pause");
        return;
    }
    cout<<"INDIQUE EL PERIODO QUE DESEA VER (MES Y ANIO)"<<endl;
    cout<<"MES: ";cin>>mes;cout<<endl<<"ANIO: ";cin>>anio;
    if(mes>12||mes<1||anio<1900){
        cout<<"Fecha invalida...!"<<endl;
        system("pause");
        return;
    }
    Jornada jornada;
    Calendario calendario;
    int pos=0;
    system("cls");
    cout<<"LEGAJO "<<legajo<<"\t\t\t\t\t\t\t\tPERIODO "<<mes<<"-"<<anio<<endl;
    cout<<endl<<"----------------------------------------------------------------"<<endl;
    cout<<"DIA"<<" ||"<<" HORA TEORICA"<<" ||"<<" HORA ENTRADA"<<" ||"<<" HORA SALIDA"<<" ||"<<" ESTADO"<<endl;
    while(jornada.leerDeDisco(pos++)){
        if(anio==jornada.getFecha().getAnio()
           &&mes==jornada.getFecha().getMes()
           &&legajo==jornada.getLegajo().getleg()){
            int teoHora=0, teoMin=0, p=0;
            while(calendario.leerDeDisco(p++)){
                if(jornada.getFecha().getAnio()==calendario.getFecha().getAnio()
                   &&jornada.getFecha().getMes()==calendario.getFecha().getMes()
                   &&jornada.getFecha().getDia()==calendario.getFecha().getDia()
                   &&jornada.getLegajo().getleg()==calendario.getLegajo().getleg()){
                    teoHora=calendario.getHoraEntrada().getHora();
                    teoMin=calendario.getHoraEntrada().getMinuto();
                   }
            }
            /*cout<<endl<<"-------------------------------------------------------------"<<endl;
            cout<<"DIA"<<" ||"<<" HORA TEORICA"<<" ||"<<" HORA ENTRADA"<<" ||"<<" HORA SALIDA"<<" ||"<<" ESTADO"<<endl;*/
            cout<<setw(3)<<jornada.getFecha().getDia()<<" ||"<<setw(2)<<teoHora<<":"<<setw(2)<<teoMin<<"         || "<<setw(2)<<jornada.getHoraEntrada().getHora()<<
            ":"<<setw(2)<<jornada.getHoraEntrada().getMinuto()<<"        || "<<setw(2)<<jornada.getHoraSalida().getHora()<<
            ":"<<setw(2)<<jornada.getHoraSalida().getMinuto()<<"       || "<<Estado(jornada.getEstado())<<endl<<
            "----------------------------------------------------------------"<<endl;
           }
    }
    cout<<endl;
    system("pause");
    Listados();
}

void mostrarJorXFec(){
    int dia,mes,anio;
    system ("cls");
    cout<<"COLOQUE LA FECHA DEL LISTADO JORNAL Q NECESITA VER...!"<<endl;
    cout<<"DIA: ";cin>>dia;
    cout<<endl<<"MES: ";cin>>mes;
    cout<<endl<<"YEAR: ";cin>>anio;
    Calendario calendario;
    Jornada jornada;
    int pos=0;
    system("cls");
    cout<<endl<<"---------EMPLEADOS DEL DIA "<<dia<<"/"<<mes<<"/"<<anio<<"----------"<<endl<<endl;
    cout<<"LEGAJO || HS ENT TEORICA || HS ENTRADA || HS SALIDA || ESTADO"<<endl;
    while(jornada.leerDeDisco(pos++)){
        if(jornada.getFecha().getAnio()==anio&&
           jornada.getFecha().getMes()==mes&&
           jornada.getFecha().getDia()==dia){
               int teoHora=0, teoMin=0, p=0;
                while(calendario.leerDeDisco(p++)){
                    if(jornada.getFecha().getAnio()==calendario.getFecha().getAnio()
                       &&jornada.getFecha().getMes()==calendario.getFecha().getMes()
                       &&jornada.getFecha().getDia()==calendario.getFecha().getDia()
                       &&jornada.getLegajo().getleg()==calendario.getLegajo().getleg()){
                        teoHora=calendario.getHoraEntrada().getHora();
                        teoMin=calendario.getHoraEntrada().getMinuto();
                       }
               }
            //cout<<endl<<"-------------------------------------------------------------"<<endl;
            //cout<<"LEGAJO"<<"||"<<"HORA ENTRADA"<<"||"<<"HORA SALIDA"<<"||"<<"ESTADO"<<endl;
            //cout<<"LEGAJO || HS ENT TEORICA || HS ENTRADA || HS SALIDA || ESTADO"<<endl;
            cout<<setw(6)<<jornada.getLegajo().getleg()<<" || "<<setw(2)<<teoHora<<":"<<setw(2)<<teoMin<<"          || "
            <<setw(2)<<jornada.getHoraEntrada().getHora()<<":"<<setw(2)<<jornada.getHoraEntrada().getMinuto()<<"      || "
            <<setw(2)<<jornada.getHoraSalida().getHora()<<":"<<setw(2)<<jornada.getHoraSalida().getMinuto()<<"     || "
            <<Estado(jornada.getEstado())<<endl<<"----------------------------------------------------------------"<<endl;
           }
    }
    cout<<endl;
    system("pause");
    Listados();
}


void cambiarPIN(){

    system("cls");
    int legajo, PIN;
    Empleados empleado;
    rlutil::setColor(rlutil::WHITE);
    rlutil::setBackgroundColor(rlutil::DARKGREY);
    rlutil::cls();
    cout << "\t\t\t\t\t\t\t  *** CAMBIAR PIN ***" << endl << endl;
    cout << "\t\t\t\t\t\t*******************************************" << endl << endl;
    cout << "\t\t\t\t\t\t\tCOLOQUE SU LEGAJO: ";cin>>legajo;
    cout << endl << "\t\t\t\t\t\t\tCOLOQUE SU PIN ACTUAL: ";rlutil::setColor(rlutil::DARKGREY);cin>>PIN;rlutil::setColor(rlutil::WHITE);
    int pos=buscarEmpleado(legajo);
    if(pos==-1){
        cout<<endl<<"\t\t\t\t\t\t\tERROR...! LEGAJO NO ENCONTRADO."<<endl<<endl; system("pause"); return;
    }
    if(!ValidarActivo(legajo)){
        cout<<endl<<"EMPLEADO DADO DE BAJA"<<endl;
        system("pause");return;
    }
    int pin;
    empleado.LeerDeDisco(pos);
    if(legajo==empleado.getleg()&&PIN==empleado.getpin()){
        cout<<endl<<endl<<"\t\t\t\t\t\t\tCOLOCA TU NUEVO PIN DE 4 DIGITOS: ";rlutil::setColor(rlutil::DARKGREY);cin>>pin;
        rlutil::setColor(rlutil::WHITE);
        if(pin>999&&pin<10000){
            cout<<endl<<"\t\t\t\t\t\t\tREPITA SU NUEVO PIN PARA CONFIRMAR: ";rlutil::setColor(rlutil::DARKGREY);cin>>PIN;
            rlutil::setColor(rlutil::WHITE);
            if(pin==PIN){
                empleado.setpin(pin);
                empleado.GuardarEnDisco(pos);
                cout<<endl<<"\t\t\t\t\t\t\tPIN CAMBIADO CORRECTAMENTE"<<endl;system("pause");
            }else{
                cout<<endl<<"\t\t\t\t\t\t\tERROR AL REPETIR PIN...!"<<endl<<endl;system("pause");
            }

        }else{
            cout<<endl<<"\t\t\t\t\t\t\tERROR AL CARGAR PIN NUEVO...! RECUERDE QUE DEBE SER DE 4 DIGITOS UNICAMENTE."<<endl<<endl;
            system("pause");
        }
    }else{
        cout<<endl<<"\t\t\t\t\t\t\tPIN ACTUAL INCORRECTO...!"<<endl;system("pause");
    }
}

