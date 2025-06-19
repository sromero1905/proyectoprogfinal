#include <iostream>
#include <cstring>
#include <cstdio>
#include "Factura.h"
using namespace std;

Factura::Factura() {
    NFactura = 0;
    NReparacion = 0;
    Importe = 0;
    FechaEntrega = Fecha();
    strcpy(NPatente, "");
    IDCliente = 0;
    ImporteTotal = 0;
}

Factura::Factura(int nFact, int nRep, int imp, Fecha fecha, const char* pat, int idCli, int impTotal) {
    NFactura = nFact;
    NReparacion = nRep;
    Importe = imp;
    FechaEntrega = fecha;
    strncpy(NPatente, pat, sizeof(NPatente) - 1);
    NPatente[sizeof(NPatente) - 1] = '\0';
    IDCliente = idCli;
    ImporteTotal = impTotal;
}

void Factura::generarFactura() {
    cout << "=== GENERAR NUEVA FACTURA ===" << endl;
    cout << "Ingrese numero de factura: ";
    cin >> NFactura;
    cout << "Ingrese numero de reparacion: ";
    cin >> NReparacion;
    cout << "Ingrese importe: ";
    cin >> Importe;
    cout << "Ingrese fecha de entrega:" << endl;
    FechaEntrega.cargarFecha();
    cout << "Ingrese patente: ";
    cin.ignore();
    cin.getline(NPatente, 20);
    cout << "Ingrese ID del cliente: ";
    cin >> IDCliente;
    cout << "Ingrese importe total: ";
    cin >> ImporteTotal;

    // Guarda en archivo
    guardarEnArchivo();
    cout << "Factura generada y guardada exitosamente!" << endl;
}

void Factura::mostrarFactura() {
    int numFactura;
    cout << "INGRESE NUMERO DE FACTURA A BUSCAR: ";
    cin >> numFactura;

    FILE* archivo = fopen("facturas.dat", "rb");
    if (archivo == NULL) {
        cout << "ERROR: No se puede abrir el archivo de facturas!" << endl;
        cout << "Puede que no existan facturas guardadas aun." << endl;
        return;
    }

    Factura factTemp;
    bool encontrada = false;

    // Busca en el archivo
    while (fread(&factTemp, sizeof(Factura), 1, archivo)) {
        if (factTemp.NFactura == numFactura) {
            encontrada = true;
            break;
        }
    }

    fclose(archivo);

    if (encontrada) {
        cout << "\n=== FACTURA ENCONTRADA ===" << endl;
        cout << "NUMERO DE FACTURA: " << factTemp.NFactura << endl;
        cout << "NUMERO DE REPARACION: " << factTemp.NReparacion << endl;
        cout << "IMPORTE: $" << factTemp.Importe << endl;
        cout << "FECHA DE ENTREGA: ";
        factTemp.FechaEntrega.mostrarFecha();
        cout << endl;
        cout << "PATENTE: " << factTemp.NPatente << endl;
        cout << "ID CLIENTE: " << factTemp.IDCliente << endl;
        cout << "IMPORTE TOTAL: $" << factTemp.ImporteTotal << endl;
    } else {
        cout << "FACTURA #" << numFactura << " NO ENCONTRADA!" << endl;
    }
}

void Factura::guardarEnArchivo() {
    FILE* archivo = fopen("facturas.dat", "ab");
    if (archivo == NULL) {
        cout << "ERROR: No se puede crear/abrir el archivo de facturas!" << endl;
        return;
    }

    fwrite(this, sizeof(Factura), 1, archivo);
    fclose(archivo);
}

void Factura::mostrarTodasLasFacturas() {
    FILE* archivo = fopen("facturas.dat", "rb");
    if (archivo == NULL) {
        cout << "No existen facturas guardadas." << endl;
        return;
    }

    Factura factTemp;
    cout << "\n=== TODAS LAS FACTURAS ===" << endl;
    cout << "-------------------------" << endl;

    while (fread(&factTemp, sizeof(Factura), 1, archivo)) {
        cout << "FACTURA #" << factTemp.NFactura << " - Cliente: " << factTemp.IDCliente
             << " - Total: $" << factTemp.ImporteTotal << endl;
    }

    fclose(archivo);
}
