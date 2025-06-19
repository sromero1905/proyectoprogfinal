#include <iostream>
#include <cstring>
#include "Vehiculo.h"
#include "ArchivoVehiculo.h"

using namespace std;

ArchivoVehiculo::ArchivoVehiculo(const char* n) {
    strcpy(nombreArchivo, n);
    tamRegistro = sizeof(Vehiculo);
}
Vehiculo::Vehiculo() {
    patente[0] = '\0';
    marca[0] = '\0';
    modelo[0] = '\0';
    anio = 0;
    falla[0] = '\0';
    tipoVehiculo = 0;
    IDCliente = 0;
    estado = false;
}


Vehiculo::Vehiculo (const char *patente, const char *marca, const char *modelo, int anio, const char* falla, int tipoVehiculo, int IDCliente){

setPatente (patente);
setMarca (marca);
setModelo (modelo);
setAnio (anio);
setFalla (falla);
setTipoVehiculo (tipoVehiculo);
setIDCliente (IDCliente);
estado = true;
}


// Getters
const char* Vehiculo::getPatente() const {
    return patente;
}

const char* Vehiculo::getMarca() const {
    return marca;
}

const char* Vehiculo::getModelo() const {
    return modelo;
}

int Vehiculo::getAnio() {
    return anio;
}

const char* Vehiculo::getFalla() const {
    return falla;
}

Fecha Vehiculo::getFechaIngreso() const {
    return fechaIngreso;
}

int Vehiculo::getTipoVehiculo() {
    return tipoVehiculo;
}

int Vehiculo::getIDCliente() {
    return IDCliente;
}

bool Vehiculo::getEstado() const {
    return estado;
}

//Setters
void Vehiculo::setPatente(const char* nuevaPatente) {
    strncpy(patente, nuevaPatente, sizeof(patente) - 1);
    patente[sizeof(patente) - 1] = '\0';
}

void Vehiculo::setMarca(const char* m) {
    strncpy(marca, m, sizeof(marca) - 1);
    marca[sizeof(marca) - 1] = '\0';
}

void Vehiculo::setModelo(const char* mod) {
    strncpy(modelo, mod, sizeof(modelo) - 1);
    modelo[sizeof(modelo) - 1] = '\0';
}

void Vehiculo::setAnio(int a) {
    anio = a;
}

void Vehiculo::setFalla(const char* f) {
    strncpy(falla, f, sizeof(falla) - 1);
    falla[sizeof(falla) - 1] = '\0';
}

void Vehiculo::setFechaIngreso(const Fecha& f) {
    fechaIngreso = f;
}

void Vehiculo::setTipoVehiculo(int t) {
    tipoVehiculo = t;
}

void Vehiculo::setIDCliente(int id) {
    IDCliente = id;
}

void Vehiculo::setEstado(bool e) {
    estado = e;
}


//FUNCIONES
void Vehiculo::cargarVehiculo() {
      cin.ignore();
    cout << "Ingrese patente: ";
    cin.getline(patente, 10);
    cout << "Ingrese marca: ";
    cin.getline(marca, 30);
    cout << "Ingrese modelo: ";
    cin.getline(modelo, 30);
    cout << "Ingrese anio: ";
    cin >> anio;
    cin.ignore();
    cout << "Ingrese falla o servicio: ";
    cin.getline(falla, 200);
    cout << "Ingrese tipo de vehiculo(1=Auto 2=Moto 3=Camioneta 4=Camion: " ;
    cin >> tipoVehiculo;
    cout << "Ingrese ID del cliente: ";
    cin >> IDCliente;
    cout << "Ingrese estado (1 = activo, 0 = inactivo): ";
    cin >> estado;
}

void Vehiculo::mostrarVehiculo() const {
    cout << "Patente: " << patente << endl;
    cout << "Marca: " << marca << endl;
    cout << "Modelo: " << modelo << endl;
    cout << "Anio: " << anio << endl;
    cout << "Falla: " << falla << endl;
    cout << "Tipo de vehiculo: " << tipoVehiculo << endl;
    cout << "ID Cliente: " << IDCliente << endl;
    cout << "Estado: " << (estado ? "Activo" : "Inactivo") << endl;
    cout << endl;
}

void Vehiculo::ModificarVehiculo() {
    int opcion;
    char nuevoTexto[200];
    int nuevoInt;
    bool salir = false;

    do {
        cout << "\nSeleccione el campo a modificar:" << endl;
        cout << "1. Marca [" << marca << "]" << endl;
        cout << "2. Modelo [" << modelo << "]" << endl;
        cout << "3. Anio [" << anio << "]" << endl;
        cout << "4. Falla/Servicio [" << falla << "]" << endl;
        cout << "5. Tipo de Vehículo [" << tipoVehiculo << "]" << endl;
        cout << "6. ID Cliente [" << IDCliente << "]" << endl;
        cout << "7. Estado [" << (estado ? "Activo" : "Inactivo") << "]" << endl;
        cout << "0. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                cout << "Nueva marca: ";
                cin.getline(nuevoTexto, 30);
                setMarca(nuevoTexto);
                break;
            case 2:
                cout << "Nuevo modelo: ";
                cin.getline(nuevoTexto, 30);
                setModelo(nuevoTexto);
                break;
            case 3:
                cout << "Nuevo anio: ";
                cin >> nuevoInt;
                setAnio(nuevoInt);
                cin.ignore();
                break;
            case 4:
                cout << "Nueva falla/servicio: ";
                cin.getline(nuevoTexto, 200);
                setFalla(nuevoTexto);
                break;
            case 5:
                cout << "Nuevo tipo de vehículo (1=Auto 2=Moto 3=Camioneta 4=Camion): ";
                cin >> nuevoInt;
                setTipoVehiculo(nuevoInt);
                cin.ignore();
                break;
            case 6:
                cout << "Nuevo ID Cliente: ";
                cin >> nuevoInt;
                setIDCliente(nuevoInt);
                cin.ignore();
                break;
            case 7:
                cout << "Nuevo estado (1=Activo, 0=Inactivo): ";
                cin >> nuevoInt;
                setEstado(nuevoInt != 0);
                cin.ignore();
                break;
            case 0:
                salir = true;
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo." << endl;
        }
    } while (!salir);
}

