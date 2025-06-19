#include <iostream>
#include <cstring>
#include "Cliente.h"

using namespace std;

// Constructor por defecto
Cliente::Cliente() : Persona() {
    IDCliente = 0;
    strcpy(CUIT, "");
    strcpy(Email, "");
    TipoCliente = 1; // Por defecto particular
    strcpy(Direccion, "");
    estado = true;
}

// Constructor parametrizado
Cliente::Cliente(const char* nom, const char* ape, int dni, int tel, int idCliente,
                 const char* cuit, const char* email, int tipo, const char* dir, bool est)
    : Persona(nom, ape, dni, tel) {
    IDCliente = idCliente;
    strncpy(CUIT, cuit, sizeof(CUIT) - 1);
    CUIT[sizeof(CUIT) - 1] = '\0';
    strncpy(Email, email, sizeof(Email) - 1);
    Email[sizeof(Email) - 1] = '\0';
    TipoCliente = tipo;
    strncpy(Direccion, dir, sizeof(Direccion) - 1);
    Direccion[sizeof(Direccion) - 1] = '\0';
    estado = est;
}

void Cliente::cargarCliente() {
    cout << "=== CARGAR NUEVO CLIENTE ===" << endl;

    // Cargar datos de Persona
    cargarDatosPersona();

    cin.ignore();

    cout << "Ingrese email: ";
    cin.getline(Email, 50);

    cout << "Tipo de cliente (1-Particular, 2-Empresa): ";
    do {
        cin >> TipoCliente;
        if (TipoCliente < 1 || TipoCliente > 2) {
            cout << "Tipo invalido. Ingrese 1 para Particular o 2 para Empresa: ";
        }
    } while (TipoCliente < 1 || TipoCliente > 2);

    cin.ignore();

    cout << "Ingrese CUIT (opcional para particulares): ";
    cin.getline(CUIT, 15);

    cout << "Ingrese direccion: ";
    cin.getline(Direccion, 100);

    estado = true; // Cliente activo por defecto


}

void Cliente::mostrarCliente() const {
    cout << "=== DATOS DEL CLIENTE ===" << endl;
    mostrarDatosPersona();
    cout << "ID CLIENTE: " << IDCliente << endl;
    cout << "CUIT: " << (strlen(CUIT) > 0 ? CUIT : "No especificado") << endl;
    cout << "EMAIL: " << Email << endl;
    cout << "TIPO: " << getTipoClienteTexto() << endl;
    cout << "DIRECCION: " << Direccion << endl;
    cout << "ESTADO: " << (estado ? "ACTIVO" : "INACTIVO") << endl;
    cout << "=========================" << endl;
}

void Cliente::actualizarCliente() {
    int opcion;
    cout << "=== ACTUALIZAR CLIENTE ===" << endl;
    cout << "1. Actualizar datos personales" << endl;
    cout << "2. Actualizar email" << endl;
    cout << "3. Actualizar direccion" << endl;
    cout << "4. Actualizar CUIT" << endl;
    cout << "5. Cambiar tipo de cliente" << endl;
    cout << "Seleccione una opcion: ";
    cin >> opcion;

    switch (opcion) {
        case 1:
            cout << "Actualizando datos personales..." << endl;
            actualizarNombreApellido ();
            cout << "El DNI no puede ser modificado." << endl;
            break;
        case 2:
            cout << "Nuevo email: ";
            cin.ignore();
            cin.getline(Email, 50);
            break;
        case 3:
            cout << "Nueva direccion: ";
            cin.ignore();
            cin.getline(Direccion, 100);
            break;
        case 4:
            cout << "Nuevo CUIT: ";
            cin.ignore();
            cin.getline(CUIT, 15);
            break;
        case 5:
            cout << "Nuevo tipo (1-Particular, 2-Empresa): ";
            do {
                cin >> TipoCliente;
                if (TipoCliente < 1 || TipoCliente > 2) {
                    cout << "Tipo invalido. Ingrese 1 o 2: ";
                }
            } while (TipoCliente < 1 || TipoCliente > 2);
            break;
        default:
            cout << "Opcion invalida." << endl;
            return;
    }

}

void Cliente::eliminarCliente() {
    estado = false;
    cout << "Cliente marcado como inactivo." << endl;
}

// Getters
int Cliente::getIDCliente() const {
    return IDCliente;
}

const char* Cliente::getCUIT() const {
    return CUIT;
}

const char* Cliente::getEmail() const {
    return Email;
}

int Cliente::getTipoCliente() const {
    return TipoCliente;
}

const char* Cliente::getDireccion() const {
    return Direccion;
}

bool Cliente::getEstado() const {
    return estado;
}

// Setters
void Cliente::setIDCliente(int id) {
    IDCliente = id;
}

void Cliente::setCUIT(const char* cuit) {
    strncpy(CUIT, cuit, sizeof(CUIT) - 1);
    CUIT[sizeof(CUIT) - 1] = '\0';
}

void Cliente::setEmail(const char* email) {
    strncpy(Email, email, sizeof(Email) - 1);
    Email[sizeof(Email) - 1] = '\0';
}

void Cliente::setTipoCliente(int tipo) {
    if (tipo >= 1 && tipo <= 2) {
        TipoCliente = tipo;
    }
}

void Cliente::setDireccion(const char* dir) {
    strncpy(Direccion, dir, sizeof(Direccion) - 1);
    Direccion[sizeof(Direccion) - 1] = '\0';
}

void Cliente::setEstado(bool est) {
    estado = est;
}

// Métodos auxiliares
const char* Cliente::getTipoClienteTexto() const {
    switch (TipoCliente) {
        case 1: return "Particular";
        case 2: return "Empresa";
        default: return "Desconocido";
    }
}

bool Cliente::esEmpresa() const {
    return TipoCliente == 2;
}

bool Cliente::esParticular() const {
    return TipoCliente == 1;
}
