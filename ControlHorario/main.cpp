#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;
#include "rlutil.h"
using namespace rlutil;
#include "fecha.h"
#include "Empleados.h"
#include "administrador.h"
#include "FUNCIONES.h"
#include "jornada.h"
///////////////////////////
#include <stdio.h>
#include <stdlib.h>       /// ESTAS LIBRERIA SON PARA QUE FUNCIONE LA FUNCION DE MANEJAR EL TAMAÑO DE LA CONSOLA
#include <windows.h>
HANDLE wHnd;
///////////////////////////

///
int main(){

    ////////////////////////////////////////////
   /* wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT windowSize = {0, 0, 1366, 768};    /// ESTO CONTROLA EL TAMAÑO DE LA CONSOLA, el tercer valor es el ancho y el cuanto valor es el alto
    SetConsoleWindowInfo(wHnd, 1, &windowSize);*/
    ////////////////////////////////////////////
    int  opcion;
    char confirmarSalida;
    while(true){
        rlutil::setColor(rlutil::WHITE);
        rlutil::setBackgroundColor(rlutil::DARKGREY);
        rlutil::cls();
        cout << "\t\t\t\t\t\t\t  *** MENU PRINCIPAL ***" << endl << endl;
        cout << "\t\t\t\t\t\t*******************************************" << endl << endl;
        cout << "\t\t\t\t\t\t\t1 - FICHAR. " << endl << endl;
        cout << "\t\t\t\t\t\t\t2 - ADMINISTRADOR. " << endl << endl;
        cout << "\t\t\t\t\t\t\t3 - CAMBIO DE PIN. " << endl << endl;
        cout << "\t\t\t\t\t\t\t0 - CERRAR PROGRAMA. " << endl << endl;
        cout << "\t\t\t\t\t\t*******************************************" << endl << endl;
        cout << "\t\t\t\t\t\t\tSELECCIONE OPCION: ";
        cin  >> opcion;
        rlutil::locate(60,11);
        if(opcion >= 0 && opcion < 3){
            system("cls");
        }
        switch(opcion){
            case 1: fichar();
                break;
            case 2: MenuAdministrador();
                break;
            case 3: cambiarPIN();
                break;
            case 0: Cerrar_Programa();
                break;
        }
        cin.ignore();
    }
}
