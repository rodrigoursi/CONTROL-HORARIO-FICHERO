#include "franco.h"
#include "calendario.h"
#include "FUNCIONES.h"
#include "rlutil.h"


#include <iostream>

Franco::Franco(Empleados legajo, int dia){
    diaFranco=dia;
    _legajo=legajo;
}

/// ///GET///

    int Franco::getDiaFranco(){return diaFranco;}
    Empleados Franco::getLegajo(){return _legajo;}

/// ///SET///

void Franco::setDiaFranco(int dia){diaFranco=dia;}
void Franco::setLegajo(Empleados legajo){_legajo=legajo;}

/// ///DISCO///

bool Franco::guardarEnDisco(){
    FILE *p = fopen("datos/franco.dat","ab");
        if(p==NULL){
            return false;
        }
        bool guardo= fwrite(this,sizeof (Franco),1,p);
        fclose(p);
        return guardo;
}

bool Franco::guardarEnDisco(int pos){
    FILE *p = fopen("datos/franco.dat","rb+");
        if(p==NULL){
            return false;
        }
        fseek(p,pos*sizeof(Franco),SEEK_SET);
        bool guardo= fwrite(this,sizeof (Franco),1,p);
        fclose(p);
        return guardo;
}

bool Franco::leerDeDisco(int pos){
    FILE *p=fopen("datos/franco.dat","rb");
    if(p==NULL){
        false;
    }
    fseek(p,pos*sizeof(Franco),SEEK_SET);
    bool ok= fread(this,sizeof(Franco),1,p);
    fclose(p);
    return ok;
}

int buscarRegistro(int legajo){
    Franco aux;
    int pos=0;
    while(aux.leerDeDisco(pos++)){
        if(aux.getLegajo().getleg()==legajo){
            return pos-1;
        }
    }
    return -1;
}

