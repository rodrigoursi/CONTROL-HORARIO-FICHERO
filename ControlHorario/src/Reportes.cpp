#include <iostream>
#include "Reportes.h"
#include "../administrador.h"
#include "rlutil.h"
#include "../FUNCIONES.h"


using namespace std;

void Reportes(){

    int opcion;
    char confirmarSalida;

        rlutil::setColor(rlutil::WHITE);
        rlutil::setBackgroundColor(rlutil::DARKGREY);
        rlutil::cls();
        cout << "\t\t\t\t\t\t\t  *** REPORTES ADMINISTRADOR ***" << endl << endl;
        cout << "\t\t\t\t\t\t*******************************************" << endl << endl;
        cout << "\t\t\t\t\t\t\t1 - REPORTE BALANCE POR PERIODO. " << endl << endl;
        cout << "\t\t\t\t\t\t\t0 - VOLVER. " << endl << endl;
        cout << "\t\t\t\t\t\t*******************************************" << endl << endl;
        cout << "\t\t\t\t\t\t\tSELECCIONE OPCION: ";
        rlutil::locate(75,11);  //60
        cin  >> opcion;

        if(opcion >= 1 && opcion < 2){
            system("cls");
        }
        switch(opcion){
            case 1: reporte1();
                break;
            case 0 : cout << endl << endl << "\t\t\t\t\t\t\t¿Confirma salir? (S/N) ";
                cin >> confirmarSalida;
                if (tolower(confirmarSalida) == 's'){
                    system("pause > nul");
                    system("cls");
                    MenuAdministrador();
                }
                break;
            default : rlutil::locate(41,13);
                    cout << "OPCION INVALIDA!!!" << endl << endl;
                    system("pause > nul");
                    system("cls");
                    Reportes();
                break;
        }
}



