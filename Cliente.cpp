#include <iostream>
#include <cstring>
#include "Cliente.h"

using namespace std;

// Constructor por defecto
Cliente::Cliente() : Persona() {
    IDCliente = 0;
    strcpy(CUIT, "");
    strcpy(Email, "");
    TipoCliente = 1;
    strcpy(Direccion, "");
    estado = true;
}

// Constructor parametrizado
Cliente::Cliente(const char* nom, const char* ape, int dni, int tel, int idCliente,
                 const char* cuit, const char* email, int tipo, const char* dir, bool est)
    : Persona(nom, ape, dni, tel) {
    IDCliente = idCliente;
    strcpy(CUIT, cuit);
    strcpy(Email, email);
    TipoCliente = tipo;
    strcpy(Direccion, dir);
    estado = est;
}

void Cliente::cargarCliente() {
    cout << "=== CARGAR CLIENTE ===" << endl;
    cargarDatosPersona();
    cin.ignore();

    cout << "Email: ";
    cin.getline(Email, 50);

    cout << "Tipo (1-Particular, 2-Empresa): ";
    cin >> TipoCliente;
    cin.ignore();

    cout << "CUIT: ";
    cin.getline(CUIT, 15);

    cout << "Direccion: ";
    cin.getline(Direccion, 100);

    estado = true;
}

void Cliente::mostrarCliente() const {
    cout << "ID: " << IDCliente << endl;
    cout << "Nombre: ";
    mostrarDatosPersona();
    cout << "Email: " << Email << endl;
    cout << "CUIT: " << (strlen(CUIT) > 0 ? CUIT : "No especificado") << endl;
    cout << "Tipo: " << getTipoClienteTexto() << endl;
    cout << "Direccion: " << Direccion << endl;
    cout << "Estado: " << (estado ? "ACTIVO" : "INACTIVO") << endl;
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
}

// Getters
int Cliente::getIDCliente() const { return IDCliente; }
const char* Cliente::getCUIT() const { return CUIT; }
const char* Cliente::getEmail() const { return Email; }
int Cliente::getTipoCliente() const { return TipoCliente; }
const char* Cliente::getDireccion() const { return Direccion; }
bool Cliente::getEstado() const { return estado; }

// Setters
void Cliente::setIDCliente(int id) { IDCliente = id; }
void Cliente::setCUIT(const char* cuit) { strcpy(CUIT, cuit); }
void Cliente::setEmail(const char* email) { strcpy(Email, email); }
void Cliente::setTipoCliente(int tipo) { TipoCliente = tipo; }
void Cliente::setDireccion(const char* dir) { strcpy(Direccion, dir); }
void Cliente::setEstado(bool est) { estado = est; }

const char* Cliente::getTipoClienteTexto() const {
    return (TipoCliente == 1) ? "Particular" : "Empresa";
}
