#include "calendario.h"
#include "Empleados.h"
#include <cstring>
#include <string>
#include "FUNCIONES.h"
#include "rlutil.h"
#include "fecha.h"
#include "franco.h"
#include "jornada.h"
#include <iomanip>

#include <iostream>

    Calendario::Calendario(FechaHora fecha, Empleados legajo, FechaHora horaEnt, FechaHora horaSalida,float horaTotal){
    _fecha=fecha;
    _legajo=legajo;
    _horaEntrada=horaEnt;
    _horaSalida=horaSalida;
    _horaTotal=horaTotal;
}

/// ///GET///

    FechaHora Calendario::getFecha(){return _fecha;}
    Empleados Calendario::getLegajo(){return _legajo;}
    FechaHora Calendario::getHoraEntrada(){return _horaEntrada;}
    FechaHora Calendario::getHoraSalida(){return _horaSalida;}
    float Calendario::getHoraTotal(){return _horaTotal;}

/// ///SET///

void Calendario::setFecha(FechaHora fecha){_fecha=fecha;}
void Calendario::setLegajo(Empleados legajo){_legajo=legajo;}
void Calendario::setHoraEntrada(FechaHora entrada){_horaEntrada=entrada;}
void Calendario::setHoraSalida(FechaHora salida){_horaSalida=salida;}
void Calendario::setHoraTotal(float total){_horaTotal=total;}

/// ///DISCO///

bool Calendario::guardarEnDisco(){
    FILE *p = fopen("datos/calendario.dat","ab");
        if(p==NULL){
            return false;
        }
        bool guardo= fwrite(this,sizeof (Calendario),1,p);
        fclose(p);
        return guardo;
}

bool Calendario::guardarEnDisco(int pos){
    FILE *p = fopen("datos/calendario.dat","rb+");
        if(p==NULL){
            return false;
        }
        fseek(p,pos*sizeof(Calendario),SEEK_SET);
        bool guardo= fwrite(this,sizeof (Calendario),1,p);
        fclose(p);
        return guardo;
}

bool Calendario::leerDeDisco(int pos){
    FILE *p=fopen("datos/calendario.dat","rb");
    if(p==NULL){
        false;
    }
    fseek(p,pos*sizeof(Calendario),SEEK_SET);
    bool ok= fread(this,sizeof(Calendario),1,p);
    fclose(p);
    return ok;
}

int  Calendario::contarRegistros(){
    FILE *p = fopen("datos/calendario.dat", "rb");
    if (p == NULL){
        return 0;
    }
    size_t bytes;
    int cant_reg;

    fseek(p, 0, SEEK_END);
    bytes = ftell(p);
    fclose(p);
    cant_reg = bytes / sizeof(Calendario);
    return cant_reg;
}

void cargarCalendario(){

    system("cls");
    FechaHora fechaMes;
    Empleados empleado;
    int legajo, hora=0, minuto=0, dia,mes,anio;
    cout<<"COLOQUE EL LEGAJO DEL EMPLEADO Q DESEA CARGAR EL CALENDARIO DE TRABAJO...!"<<endl;
    cout<<"Legajo: ";cin>>legajo;
    int legajoPos=buscarEmpleado(legajo);
    if(legajoPos==-1){
        cout<<endl<<"LEGAJO NO ENCONTRADO.!"<<endl;
        system("pause");
        return;
    }
    cout<<endl<<"COLOQUE LA FECHA DE INICIO DE LA CARGA DE HORARIO DEL EMPLEADO...!"<<endl;
    cout<<"DIA: ";cin>>dia;cout<<endl<<"MES: ";cin>>mes;
    if(ValidarDiaMes(dia, mes)){
        cout<<endl<<"YEAR: ";cin>>anio;
        if(anio<fechaMes.getAnio()){
            cout<<"FECHA INVALIDA!"<<endl;system ("pause");return;
        }
        if(anio==fechaMes.getAnio()&&mes<fechaMes.getMes()){
            cout<<"FECHA INVALIDA!"<<endl;system ("pause");return;
        }
        if(anio==fechaMes.getAnio()&&mes==fechaMes.getMes()&&dia<=fechaMes.getDia()){
        cout<<"FECHA INVALIDA!"<<endl;system ("pause");return;
        }
    } else return;
    cout<<"COLOQUE EL HORARIO DEL EMPLEADO"<<endl;
    cout<<"HORA: ";cin>>hora; cout<<endl<<"MINUTO: ";cin>>minuto;
    if(!ValidarHoraMinutos(hora,minuto)){
        return;
    }
    cout<<endl<<"COLOQUE EL DIA DE LA SEMANA DEL DIA FRANCO/LIBRE DEL EMPLEADO ELIGIENDO UN NUMERO"<<endl;
    cout<<"0-(Domingo), 1-(Lunes), 2-(Martes), 3-(Miercoles), 4-(Jueves), 5-(Viernes), 6-(Sabado)"<<endl;
    int franco=0;
    cout<<"ESCRIBA EL NUMERO SELECCIONADO: ";cin>>franco;
    if(franco<0||franco>6){
        franco=0;
        cout<<"COLOCO UN NUMERO ERRONEO, POR LO TANTO SE LE OTORGO FRANCO DOMINGO POR DEFAULT AL EMPLEADO";
        system("nul");
    }
    Calendario check;
    int pos=0;
    while(check.leerDeDisco(pos++)){
        if(mes!=1){
            if(check.getFecha().getAnio()==anio
               &&check.getFecha().getMes()==mes//-1
               &&check.getLegajo().getleg()==legajo){
                cout<<endl<<"ESTE EMPLEADO YA FUE CARGADO PREVIAMENTE...!";
                system("pause");
                return;
            }
        }
        else {
          if(check.getFecha().getAnio()==anio-1
                &&check.getFecha().getMes()==12
                &&check.getLegajo().getleg()==legajo){
                cout<<endl<<"ESTE EMPLEADO YA FUE CARGADO PREVIAMENTE...!";
                system("pause");
                return;
            }
        }
    }
    int tam=mesCantDias(mes);
    for(dia;dia<=tam;dia++){
        FechaHora fSalida, fec;
        empleado.LeerDeDisco(legajoPos);
        float fin=0;
        if(diaSemana(dia,mes,anio)!=franco){
            fSalida.setHora(hora+empleado.getcargaHoraria()); fSalida.setMinuto(minuto);
            fec.setDia(dia); fec.setMes(mes); fec.setAnio(anio); fec.setHora(hora);fec.setMinuto(minuto);
        }
        else{
            fSalida.setHora(-1);
            fec.setDia(dia); fec.setMes(mes); fec.setAnio(anio); fec.setHora(-1);
        }
         int mnSalida=minuto+horas_A_minutos(hora+empleado.getcargaHoraria());
         int mnEntrada=minuto+horas_A_minutos(hora);
         fin=(mnSalida-mnEntrada)/60;
         if((mnSalida-mnEntrada)%60>29){
            fin+=0.5;
         }

         if(fSalida.getHora()>23){
            fSalida.setHora(fSalida.getHora()-24);
         }

         Calendario calendario(fec,empleado,fec,fSalida,fin);
         calendario.guardarEnDisco();
         Franco fechaFranco(empleado,franco);
         int resulPos= buscarRegistro(legajo);
         if(resulPos==-1){
            fechaFranco.guardarEnDisco();
         } else{
            fechaFranco.guardarEnDisco(resulPos);
         }

    }
    cout<<"HORARIO DE EMPLEADO CARGADO CON EXITO...!"<<endl;
    cout<<"SE GUARDO EL HORARIO DEL RESTO DEL MES.!"<<endl<<system("pause");
}

void actualizarCalendario(){

    system("cls");
    cout<<"ESTE PROCESO PUEDE DEMORAR VARIOS MINUTOS, NO CERRAR EL PROGRAMA"<<endl<<endl;
    system("pause");cout<<endl;
    FechaHora fecha;
    int anio=fecha.getAnio();
    int mes;
    if(fecha.getMes()==12){
        mes=1;
        anio++;
    } else mes=fecha.getMes()+1;
    int diasS=mesCantDias(mes);
    Empleados empleado;

    int pos=0;
    while(empleado.LeerDeDisco(pos++)){
        bool grabarOk=1;
        if(ValidarActivo(empleado.getleg())){
            Calendario calendario;
            int dias=mesCantDias(fecha.getMes());
            int hora=0,minuto=0;
            for(dias;dias>=1;dias--){
                int posicion=0;
                while(calendario.leerDeDisco(posicion++)){
                    if(calendario.getFecha().getAnio()==anio
                       &&calendario.getFecha().getMes()==mes
                       &&calendario.getFecha().getDia()==dias
                       &&calendario.getLegajo().getleg()==empleado.getleg()){
                        grabarOk=0;
                    }

                    if(calendario.getFecha().getAnio()==fecha.getAnio()
                       &&calendario.getFecha().getMes()==fecha.getMes()
                       &&calendario.getFecha().getDia()==dias
                       &&calendario.getLegajo().getleg()==empleado.getleg()){
                        hora=calendario.getHoraEntrada().getHora();
                        minuto=calendario.getHoraEntrada().getMinuto();
                        if(hora!=-1){
                            dias=0;  ///SE TRANSFORMA EN -1 POREL -- DEL CICLO FOR
                        }
                    }
                }
            }
            /////
            if(dias==-1){
              Franco franco;
              franco.leerDeDisco(buscarRegistro(empleado.getleg()));
              for(int dia=1;dia<=diasS;dia++){
                float fin=0;
                FechaHora fSalida,fec;
                if(diaSemana(dia,mes,anio)!=franco.getDiaFranco()){
                    fSalida.setHora(hora+empleado.getcargaHoraria()); fSalida.setMinuto(minuto);
                    fec.setDia(dia); fec.setMes(mes); fec.setAnio(anio); fec.setHora(hora);fec.setMinuto(minuto);
                }
                else{
                    fSalida.setHora(-1);
                    fec.setDia(dia); fec.setMes(mes); fec.setAnio(anio); fec.setHora(-1);
                }
                int mnSalida=minuto+horas_A_minutos(hora+empleado.getcargaHoraria());
                int mnEntrada=minuto+horas_A_minutos(hora);
                fin=(mnSalida-mnEntrada)/60;
                if((mnSalida-mnEntrada)%60>29){
                    fin+=0.5;
                }
                Calendario calen(fec,empleado,fec,fSalida,fin);
                if(grabarOk){
                    calen.guardarEnDisco();
                }
              }
            }
        }
    }
    cout<<endl<<"PROCESO TERMINADO CORRECTAMENTE...!"<<endl<<endl;
    system("pause");
}

void editarCalendario(){

    int legajo=0,dia=0,mes=0,anio=0, pos=0;
    system("cls");
    cout << "\t\t\t\t\t\t\t***EDITAR CALENDARIO EMPLEADO***" << endl << endl;
    cout << "\t\t\t\t\t\t**********************************************" << endl << endl;
    cout << "\t\t\t\t\t\t\tINGRESE LEGAJO: ";
    cin  >> legajo;
    cout<<endl<<endl<< "\t\t\t\t\t\t\tINGRESE FECHA QUE DESEA EDITAR EL HORARIO"<<endl;
    cout<<"\t\t\t\t\t\t\tPRIMERO INGRESE ANIO: ";cin>>anio;
    cout<<"\t\t\t\t\t\t\tAHORA INGRESE MES: ";cin>>mes;
    cout<<"\t\t\t\t\t\t\tY POR ULTIMO INGRESE DIA: ";cin>>dia;
    cout << endl << endl << "\t\t\t\t\t";
    if(buscarEmpleado(legajo) == -1){
        cout << endl << endl,
        cout << "\t\t\t\t\t\t\tNO EXISTE EL LEGAJO INGRESADO." << endl << endl,
        cout << "\t\t\t\t\t\t\t" << system("pause");
        system("cls");
        return;
    }
    Calendario calendario;
    FechaHora Hora;
    int posicion=-1;
    int hora=0, minutos=0;
    while(calendario.leerDeDisco(pos++)){
        if(anio==calendario.getFecha().getAnio()
           &&mes==calendario.getFecha().getMes()
           &&dia==calendario.getFecha().getDia()
           &&legajo==calendario.getLegajo().getleg()){
            rlutil::setColor(rlutil::WHITE);
            rlutil::setBackgroundColor(rlutil::DARKGREY);
            rlutil::cls();
            cout << "\t\t\t\t\t\t\t  *** MENU EDITAR CALENDARIO EMPLEADO "<<legajo<<" ***" << endl << endl;
            cout << "\t\t\t\t\t\t\t*******************************************" << endl << endl;
            cout << "\t\t\t\t\t\t\t\t1  - HORA ENTRADA. " << endl << endl;
            cout << "\t\t\t\t\t\t\t\t2  - HORA SALIDA. " << endl << endl;
            cout << "\t\t\t\t\t\t\t\t0  - VOLVER. " << endl << endl;
            cout << "\t\t\t\t\t\t\t*******************************************" << endl << endl;
            cout << "\t\t\t\t\t\t\t\tSELECCIONE OPCION: ";
            char opcion, confirmarSalida;
            cin  >> opcion;

            switch(opcion){
                case '1':
                    cout<<"\t\t\t\t\t\t\tINTRODUCE NUEVO HORARIO."<<endl;
                    cout<<endl<<"\t\t\t\t\t\t\tHORA-> ";cin>>hora;
                    cout<<endl<<"\t\t\t\t\t\t\tMINUTOS-> ";cin>>minutos;
                    Hora.setHora(hora);Hora.setMinuto(minutos);
                    calendario.setHoraEntrada(Hora);
                break;
                case '2':
                    cout<<"\t\t\t\t\t\t\tINTRODUCE NUEVO HORARIO."<<endl;
                    cout<<endl<<"\t\t\t\t\t\t\tHORA-> ";cin>>hora;
                    cout<<endl<<"\t\t\t\t\t\t\tMINUTOS-> ";cin>>minutos;
                    Hora.setHora(hora);Hora.setMinuto(minutos);
                    calendario.setHoraSalida(Hora);
                break;
                default : cout << endl << endl << "\t\t\t\t\t\t\t¿Confirma salir? (S/N) ";
                cin >> confirmarSalida;
                if (tolower(confirmarSalida) == 's'){
                    return;
                }
           }
           pos--;
           calendario.guardarEnDisco(pos);
           cout<<endl<<"\t\t\t\t\t\t\tPROCESO GUARDADO CORRECTAMENTE...!"<<endl<<"\t\t\t\t\t\t\t";
           system("pause");
           return;
        }
    }
    cout<<endl<<"NO SE ENCONTRO HORARIO ESTABLECIDO EN ESA FECHA PARA ESE EMPLEADO...!";
    system("pause");
}

void CalendarioDeHorarios(){
    char opcion;
    Empleados obj;
    char confirmarSalida;
    while(true){
        rlutil::setColor(rlutil::WHITE);
        rlutil::setBackgroundColor(rlutil::DARKGREY);
        rlutil::cls();
        cout << "\t\t\t\t\t\t\t  *** MENU CALENDARIO ***" << endl << endl;
        cout << "\t\t\t\t\t\t*******************************************" << endl << endl;
        cout << "\t\t\t\t\t\t\t1 - CARGAR NUEVO HORARIO. " << endl << endl;
        cout << "\t\t\t\t\t\t\t2 - EDITAR HORARIO. " << endl << endl;
        cout << "\t\t\t\t\t\t\t3 - ACTUALIZAR HORARIO. " << endl << endl;
        cout << "\t\t\t\t\t\t\t0 - VOLVER. " << endl << endl;
        cout << "\t\t\t\t\t\t*******************************************" << endl << endl;
        cout << "\t\t\t\t\t\t\tSELECCIONE OPCION: ";
        cin  >> opcion;
        rlutil::locate(60,15);
        if(opcion >= 0 && opcion < 4){
            system("cls");
        }
        switch(opcion){
            case '1': cargarCalendario();
                break;
            case '2': editarCalendario();
                break;
            case '3': actualizarCalendario();
                break;
            case '0' : cout << endl << endl << "\t\t\t\t\t\t\t¿Confirma salir? (S/N) ";
                    cin >> confirmarSalida;
                    if (tolower(confirmarSalida) == 's'){
                        system("pause > nul");
                        system("cls");
                        return;
                    }
                break;
        }
    }
}

void mostrarHorarioXMes(){

    system("cls");
    int legajo, mes, anio;
    cout<<"COLOQUE EL LEGAJO DEL EMPLEADO QUE DESEA VER EL LISTADO...!"<<endl;
    cout<<"Legajo: ";cin>>legajo;
    if(buscarEmpleado(legajo)==-1){
        cout<<"Legajo inexistente...!"<<endl;
        system("pause");
        return;
    }
    cout<<endl<<"INDIQUE EL PERIODO QUE DESEA VER (MES Y AÑO)"<<endl;
    cout<<"MES: ";cin>>mes;cout<<endl<<"ANIO: ";cin>>anio;
    if(mes>12||mes<1||anio<1900){
        cout<<"Fecha invalida...!"<<endl;
        system("pause");
        return;
    }
    Calendario calendario;
    int pos=0;
    system("cls");
    cout<<"LEGAJO "<<legajo<<"\t\t\t\t\t\t\t\tPERIODO "<<mes<<"-"<<anio<<endl;
    cout<<"\t\t\t\t\tHORARIOS TEORICOS"<<endl;
    cout<<endl<<"----------------------------------------------"<<endl;
    cout<<"FECHA"<<"||"<<"HORARIO ENTRADA"<<"||"<<"HORARIO SALIDA"<<endl;
    while(calendario.leerDeDisco(pos++)){
        if(anio==calendario.getFecha().getAnio()
            &&mes==calendario.getFecha().getMes()
            &&legajo==calendario.getLegajo().getleg()){
            //cout<<"\t\t\tHORARIOS TEORICOS"<<endl;
            /*cout<<endl<<"----------------------------------------------"<<endl;
            cout<<"FECHA"<<"||"<<"HORARIO ENTRADA"<<"||"<<"HORARIO SALIDA"<<endl;*/

            if(calendario.getHoraEntrada().getHora()==-1&&calendario.getHoraSalida().getHora()==-1){
                cout<<setw(3)<<calendario.getFecha().getDia()<< "  || "
                <<setw(2)<<"LI"<<"B"<<setw(2)<<"RE"
                <<"         || "<<setw(2)<<"LI"<<"B"<<setw(2)<<"RE"
                <<endl<<"----------------------------------------------"<<endl;
            }else{
               cout<<setw(3)<<calendario.getFecha().getDia()<< "  || "
                <<setw(2)<<calendario.getHoraEntrada().getHora()<<":"<<setw(2)<<calendario.getHoraEntrada().getMinuto()
                <<"         || "<<setw(2)<<calendario.getHoraSalida().getHora()<<":"<<setw(2)<<calendario.getHoraSalida().getMinuto()
                <<endl<<"----------------------------------------------"<<endl;
            }

            /*cout<<setw(3)<<calendario.getFecha().getDia()<< "  || "
            <<setw(2)<<calendario.getHoraEntrada().getHora()<<":"<<setw(2)<<calendario.getHoraEntrada().getMinuto()
            <<"         || "<<setw(2)<<calendario.getHoraSalida().getHora()<<":"<<setw(2)<<calendario.getHoraSalida().getMinuto()
            <<endl<<"----------------------------------------------"<<endl;*/
       }
    }
    cout<<endl;
    system("pause");
    Listados();
}

void mostrarHorarioXFec(){

    int dia=0,mes=0,anio=0;
    system ("cls");
    cout<<"COLOQUE LA FECHA DEL LISTADO JDE HORARIO Q NECESITA VER...!"<<endl;
    cout<<"DIA: ";cin>>dia;
    cout<<endl<<"MES: ";cin>>mes;
    cout<<endl<<"YEAR: ";cin>>anio;

    Calendario calendario;
    int pos=0;
    system("cls");
    cout<<endl<<"---------EMPLEADOS DEL DIA "<<dia<<"/"<<mes<<"/"<<anio<<"----------"<<endl;
    cout<<endl<<"----------------------------------------------"<<endl;
    cout<<"LEGAJO"<<" ||"<<"HORA ENTRADA"<<" ||"<<"HORA SALIDA"<<endl;
    while(calendario.leerDeDisco(pos++)){
        if(calendario.getFecha().getAnio()==anio&&
           calendario.getFecha().getMes()==mes&&
           calendario.getFecha().getDia()==dia){
            /*cout<<endl<<"----------------------------------------------"<<endl;
            cout<<"LEGAJO"<<"||"<<"HORA ENTRADA"<<"||"<<"HORA SALIDA"<<endl;*/

            if(calendario.getHoraEntrada().getHora()==-1&&calendario.getHoraSalida().getHora()==-1){
                cout<<setw(4)<<calendario.getLegajo().getleg()<<"   ||"<<"    "<<setw(2)<<"LI"<<
                "B"<<setw(2)<<"RE"<<"    ||"<<"    "<<setw(2)<<"LI"<<
                "B"<<setw(2)<<"RE"<<endl<<"----------------------------------------------"<<endl;
            }else{
                cout<<setw(4)<<calendario.getLegajo().getleg()<<"   ||"<<"    "<<setw(2)<<calendario.getHoraEntrada().getHora()<<
                ":"<<setw(2)<<calendario.getHoraEntrada().getMinuto()<<"    ||"<<"    "<<setw(2)<<calendario.getHoraSalida().getHora()<<
                ":"<<setw(2)<<calendario.getHoraSalida().getMinuto()<<endl<<"----------------------------------------------"<<endl;
            }

            /*cout<<setw(4)<<calendario.getLegajo().getleg()<<"   ||"<<"    "<<setw(2)<<calendario.getHoraEntrada().getHora()<<
            ":"<<setw(2)<<calendario.getHoraEntrada().getMinuto()<<"    ||"<<"    "<<setw(2)<<calendario.getHoraSalida().getHora()<<
            ":"<<setw(2)<<calendario.getHoraSalida().getMinuto()<<endl<<"----------------------------------------------"<<endl;*/
           }
    }
    cout<<endl;
    system("pause");
    Listados();
}
