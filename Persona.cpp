#include <cstring>
#include <iostream>
#include "Persona.h"
using namespace std;

Persona::Persona() {
    strcpy(_Nombre, "");
    strcpy(_Apellido, "");
    _dni = 0;
    _Telefono = 0;
}

// ← AGREGAR ESTE CONSTRUCTOR QUE FALTA
Persona::Persona(const char* nom, const char* ape, int dni, int tel) {
    setNombre(nom);
    setApellido(ape);
    setDNI(dni);
    setTelefono(tel);
}

// ← AGREGO ESTE MÉTODO QUE FALTA
void Persona::cargarDatosPersona() {
    cout << "INGRESAR NOMBRE: ";
    cin.ignore();
    cin.getline(_Nombre, 50);
    cout << "INGRESAR APELLIDO: ";
    cin.getline(_Apellido, 50);
    cout << "INGRESAR DNI: ";
    cin >> _dni;
    cout << "INGRESAR TELEFONO: ";
    cin >> _Telefono;
}

// ← AGREGO ESTE MÉTODO QUE FALTA
void Persona::mostrarDatosPersona() const {
    cout << "NOMBRE: " << _Nombre << endl;
    cout << "APELLIDO: " << _Apellido << endl;
    cout << "DNI: " << _dni << endl;
    cout << "TELEFONO: " << _Telefono << endl;
}

void Persona::actualizarNombreApellido() {
    char nuevoNombre[50];
    int nuevoTelefono;
    cout << "Nuevo nombre [" << _Nombre << "]: ";
    cin.ignore();
    cin.getline(nuevoNombre, 50);
    setNombre(nuevoNombre);

    cout << "Nuevo apellido [" << _Apellido << "]: ";
    cin.getline(nuevoNombre, 50);
    setApellido(nuevoNombre);

   cout << "Nuevo Telefono [" << _Telefono<< "]: ";
    cin>> nuevoTelefono;
    setTelefono(nuevoTelefono);
}


//setters
void Persona::setNombre(const char* nombre) {
    strcpy(_Nombre, nombre);
}
void Persona::setApellido(const char* apellido) {
    strcpy(_Apellido, apellido);
}
void Persona::setDNI(int d) {
    _dni = d;
}
void Persona::setTelefono(int t) {
    _Telefono = t;
}

//getters
const char* Persona::getNombre() {
    return _Nombre;
}
const char* Persona::getApellido() {
    return _Apellido;
}
int Persona::getDNI() {
    return _dni;
}
int Persona::getTelefono() {
    return _Telefono;
}
