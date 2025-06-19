#include <iostream>
#include <cstring>
#include "ArchivoCliente.h"

using namespace std;

ArchivoCliente::ArchivoCliente(const char* nombre) {
    strcpy(NombreArchivo, nombre);
    TamRegistro = sizeof(Cliente);
}

int ArchivoCliente::ObtenerProximoID() {
    FILE* archivo = fopen(NombreArchivo, "rb");
    if (archivo == nullptr) {
        return 1; // Primer ID si no existe el archivo
    }

    Cliente cliente;
    int maxID = 0;

    while (fread(&cliente, TamRegistro, 1, archivo) == 1) {
        if (cliente.getIDCliente() > maxID) {
            maxID = cliente.getIDCliente();
        }
    }

    fclose(archivo);
    return maxID + 1;
}

bool ArchivoCliente::GenerarNuevo() {
    FILE* archivo = fopen(NombreArchivo, "wb");
    if (archivo == nullptr) {
        cout << "Error: No se pudo crear el archivo " << NombreArchivo << endl;
        return false;
    }
    fclose(archivo);
    cout << "Archivo " << NombreArchivo << " creado exitosamente." << endl;
    return true;
}

void ArchivoCliente::AgregarCliente() {
    Cliente cliente;
    cliente.cargarCliente();

    // Asignar ID autoincremental
    int nuevoID = ObtenerProximoID();
    cliente.setIDCliente(nuevoID);

    FILE* archivo = fopen(NombreArchivo, "ab");
    if (archivo == nullptr) {
        cout << "Error: No se pudo abrir el archivo para escritura." << endl;
        return;
    }

    int resultado = fwrite(&cliente, TamRegistro, 1, archivo);
    fclose(archivo);

    if (resultado == 1) {
        cout << "Cliente agregado exitosamente! ID asignado: " << cliente.getIDCliente() << endl;
    } else {
        cout << "Error: No se pudo guardar el cliente." << endl;
    }
}

void ArchivoCliente::MostrarCliente() {
    int id;
    cout << "Ingrese ID del cliente a mostrar: ";
    cin >> id;

    Cliente cliente = BuscarClientePorID(id);
    if (cliente.getIDCliente() == 0) {
        cout << "Cliente no encontrado." << endl;
    } else {
        cliente.mostrarCliente();
    }
}

void ArchivoCliente::ModificarCliente() {
    int id;
    cout << "Ingrese ID del cliente a modificar: ";
    cin >> id;

    FILE* archivo = fopen(NombreArchivo, "r+b");
    if (archivo == nullptr) {
        cout << "Error: No se pudo abrir el archivo." << endl;
        return;
    }

    Cliente cliente;
    bool encontrado = false;
    long posicion = 0;

    while (fread(&cliente, TamRegistro, 1, archivo) == 1) {
        if (cliente.getIDCliente() == id && cliente.getEstado()) {
            encontrado = true;
            break;
        }
        posicion = ftell(archivo);
    }

    if (!encontrado) {
        cout << "Cliente no encontrado o inactivo." << endl;
        fclose(archivo);
        return;
    }

    cout << "Cliente encontrado:" << endl;
    cliente.mostrarCliente();

    char confirma;
    cout << "¿Desea modificar este cliente? (s/n): ";
    cin >> confirma;

    if (confirma == 's' || confirma == 'S') {
        cliente.actualizarCliente();

        fseek(archivo, posicion - TamRegistro, SEEK_SET);
        int resultado = fwrite(&cliente, TamRegistro, 1, archivo);

        if (resultado == 1) {
            cout << "Cliente modificado exitosamente!" << endl;
        } else {
            cout << "Error: No se pudo modificar el cliente." << endl;
        }
    }

    fclose(archivo);
}

void ArchivoCliente::EliminarCliente() {
    int id;
    cout << "Ingrese ID del cliente a eliminar: ";
    cin >> id;

    FILE* archivo = fopen(NombreArchivo, "r+b");
    if (archivo == nullptr) {
        cout << "Error: No se pudo abrir el archivo." << endl;
        return;
    }

    Cliente cliente;
    bool encontrado = false;
    long posicion = 0;

    while (fread(&cliente, TamRegistro, 1, archivo) == 1) {
        if (cliente.getIDCliente() == id && cliente.getEstado()) {
            encontrado = true;
            break;
        }
        posicion = ftell(archivo);
    }

    if (!encontrado) {
        cout << "Cliente no encontrado o ya inactivo." << endl;
        fclose(archivo);
        return;
    }

    cout << "Cliente encontrado:" << endl;
    cliente.mostrarCliente();

    char confirma;
    cout << "¿Está seguro que desea eliminar este cliente? (s/n): ";
    cin >> confirma;

    if (confirma == 's' || confirma == 'S') {
        cliente.eliminarCliente(); // Marca como inactivo

        fseek(archivo, posicion - TamRegistro, SEEK_SET);
        int resultado = fwrite(&cliente, TamRegistro, 1, archivo);

        if (resultado == 1) {
            cout << "Cliente eliminado exitosamente!" << endl;
        } else {
            cout << "Error: No se pudo eliminar el cliente." << endl;
        }
    }

    fclose(archivo);
}

Cliente ArchivoCliente::BuscarClientePorID(int id) {
    Cliente cliente;
    FILE* archivo = fopen(NombreArchivo, "rb");

    if (archivo == nullptr) {
        cout << "Error: No se pudo abrir el archivo." << endl;
        return cliente; // Retorna cliente vacio (ID = 0)
    }

    while (fread(&cliente, TamRegistro, 1, archivo) == 1) {
        if (cliente.getIDCliente() == id && cliente.getEstado()) {
            fclose(archivo);
            return cliente;
        }
    }

    fclose(archivo);
    // Si no se encontro, retornar cliente vacio
    Cliente clienteVacio;
    return clienteVacio;
}

bool ArchivoCliente::ExisteCliente(int id) {
    Cliente cliente = BuscarClientePorID(id);
    return cliente.getIDCliente() != 0;
}

