#ifndef ARCHIVO_CLIENTE_H
#define ARCHIVO_CLIENTE_H

#include "Cliente.h"
#include <cstdio>

class ArchivoCliente {
    char NombreArchivo[30];
    int TamRegistro;

public:
    ArchivoCliente(const char* nombre = "Clientes.dat");
    bool GenerarNuevo();
    void AgregarCliente();
    void MostrarCliente();
    void ModificarCliente();
    void EliminarCliente();
    Cliente BuscarClientePorID(int id);
    bool ExisteCliente(int id);
    int ObtenerProximoID();
};

#endif // ARCHIVO_CLIENTE_H
