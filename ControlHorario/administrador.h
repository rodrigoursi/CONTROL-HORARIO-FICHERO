#ifndef ADMINISTRADOR_H_INCLUDED
#define ADMINISTRADOR_H_INCLUDED


class Administrador{
    private:
        char _Usuario [30], _Contrasenia[4];
    public:
        Administrador();
        void setUsuarioAdmin(char *Usuario);
        void setContraseniaAdmin(char *Contrasenia);
        char *getUsuarioAdmin();
        char *getContraseniaAdmin();
        bool grabarEnDisco();
        bool leerDeDisco(int pos);
};

///FUNCIONES GLOBALES

void CargarEmpleado();
void resetPIN();

#endif // ADMINISTRADOR_H_INCLUDED
