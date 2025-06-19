#include <iostream>
#include "Empleado.h"
#include "ArchivoEmpleado.h"
#include "Persona.h"
#include <cstring>
using namespace std;


Empleado::Empleado () {
setNombre (" ");
setApellido(" ");
setDNI (0);
setTelefono(0);
_idEmpleado = 0;
strcpy(_especialidad,  "");
}

Empleado::Empleado(const char* nombre, const char* apellido, int dni, int telefono, int idEmpleado, const char* especialidad) {

setNombre (nombre);
setApellido (apellido);
setDNI(dni);
setTelefono (telefono);
_idEmpleado = idEmpleado;
strcpy (_especialidad, especialidad);
_activo = true;
}

//setters
void Empleado::setIDEmpleado(int id) {
    _idEmpleado = id;
}

void Empleado::setEspecialidad(const char* esp) {
    strcpy(_especialidad, esp);
}

void Empleado::setActivo(bool a) {
    _activo = a;
}


//getters
int Empleado::getIDEmpleado() {
    return _idEmpleado;
}

const char* Empleado::getEspecialidad() {
    return _especialidad;
}

bool Empleado::estaActivo() {
    return _activo;
}


void Empleado::mostrarEmpleado () {
    cout << endl;
    cout << "ID Empleado: " << getIDEmpleado() << endl;
    cout << "Nombre: " << getNombre() << endl;
    cout << "Apellido: " << getApellido() << endl;
    cout << "DNI: " << getDNI() << endl;
    cout << "Telefono: " << getTelefono() << endl;
    cout << "Especialidad: " << getEspecialidad() << endl;
    cout << "Estado: " << (estaActivo() ? "Activo" : "Baja") << endl;
}

void Empleado::cargarEmpleado () {
  char nombre[50], apellido[50], especialidad[50];
    int dni, telefono;

    cout << "INGRESE EL NOMBRE: ";
    cin >> nombre;
    setNombre (nombre);

     cout << "INGRESE EL APELLIDO: ";
     cin >> apellido;
     setApellido (apellido);

     cout << "INGRESE DNI: ";
    cin >> dni;
    setDNI(dni);

      cout << "INGRESE TELEFONO: ";
    cin >> telefono;
    setTelefono(telefono);

    cout << "INGRESE ESPECIALIDAD: ";
    cin >> especialidad;
    setEspecialidad (especialidad);

    setActivo (true);
}

void Empleado::actualizarEmpleado ( ){
char nuevoNombre [50];
int nuevoValor;

cout << "Nombre ["<< getNombre () <<  "]: ";
cin  >> nuevoNombre;
setNombre (nuevoNombre);

cout << "Apellido [" << getApellido () << "]: ";
cin >> nuevoNombre;
setApellido (nuevoNombre);

 cout << "DNI [" << getDNI() << "] (NO MODIFICABLE)" << endl;

cout << "Telefono [" << getTelefono() << "]: ";
cin >> nuevoValor;
setTelefono (nuevoValor);

cout << "Especialidad [" << getEspecialidad() << "]: ";
cin >> nuevoNombre;
setEspecialidad (nuevoNombre);

}
