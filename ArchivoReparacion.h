#ifndef ARCHIVOREPARACION_H
#define ARCHIVOREPARACION_H

#include "Reparacion.h"
#include <cstdio>

class ArchivoReparacion {
private:
    char nombreArchivo[30];
    int tamRegistro;

public:
    // Constructor
    ArchivoReparacion(const char* nombre = "reparaciones.dat");

    // M�todos b�sicos del archivo
    bool generarNuevo();
    int agregarRegistro(const Reparacion r);
    bool listarRegistros();
    int buscarReparacion(int id);
    Reparacion leerRegistro(int pos);
    int modificarRegistro(const Reparacion r, int pos);
    int contarRegistros();

    // M�todos auxiliares
    bool existeReparacion(int id);
    int obtenerProximoID();

    // M�todos de consulta espec�ficos
    bool listarReparacionesPorCliente(int idCliente);
    bool listarReparacionesPorEstado(int estado);
    bool listarReparacionesPendientesPago();
};

#endif // ARCHIVOREPARACION_H
