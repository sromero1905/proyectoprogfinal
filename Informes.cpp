#include <iostream>
#include <cstring>
#include <cstdio>
#include <iomanip>
#include "Informes.h"

using namespace std;

Informes::Informes() {}

void Informes::mostrarEncabezado(const char* titulo) {
    cout << "\n======== " << titulo << " ========" << endl;
}

// ===== RECAUDACIÓN =====

void Informes::recaudacionMensual() {
    mostrarEncabezado("RECAUDACION MENSUAL");

    int anio;
    cout << "Anio: ";
    cin >> anio;

    const char* meses[] = {"Ene", "Feb", "Mar", "Abr", "May", "Jun",
                           "Jul", "Ago", "Sep", "Oct", "Nov", "Dic"};

    float total = 0;
    cout << fixed << setprecision(2);

    for (int mes = 1; mes <= 12; mes++) {
        float recaud = calcularRecaudacionMes(mes, anio);
        cout << meses[mes-1] << ": $" << recaud << endl;
        total += recaud;
    }
    cout << "TOTAL: $" << total << endl;
}

void Informes::recaudacionAnual() {
    mostrarEncabezado("RECAUDACION ANUAL");

    int anio;
    cout << "Anio: ";
    cin >> anio;

    float total = calcularRecaudacionAnio(anio);
    cout << fixed << setprecision(2);
    cout << "Total " << anio << ": $" << total << endl;
}

void Informes::recaudacionPorCliente() {
    mostrarEncabezado("RECAUDACION POR CLIENTE");

    FILE* archivo = fopen("facturas.dat", "rb");
    if (!archivo) {
        cout << "No hay facturas." << endl;
        return;
    }

    int clientes[50], cantidades[50];
    float totales[50];
    int cantClientes = 0;

    Factura factura;
    while (fread(&factura, sizeof(Factura), 1, archivo) && cantClientes < 50) {
        int pos = -1;
        // Buscar cliente existente
        for (int i = 0; i < cantClientes; i++) {
            if (clientes[i] == factura.IDCliente) {
                pos = i;
                break;
            }
        }

        if (pos == -1) { // Cliente nuevo
            clientes[cantClientes] = factura.IDCliente;
            totales[cantClientes] = factura.ImporteTotal;
            cantidades[cantClientes] = 1;
            cantClientes++;
        } else { // Cliente existente
            totales[pos] += factura.ImporteTotal;
            cantidades[pos]++;
        }
    }
    fclose(archivo);

    cout << fixed << setprecision(2);
    cout << "Cliente | Total     | Facturas" << endl;
    cout << "--------------------------------" << endl;
    for (int i = 0; i < cantClientes; i++) {
        cout << setw(6) << clientes[i] << "  | $" << setw(8) << totales[i]
             << " | " << cantidades[i] << endl;
    }
}

// ===== REPARACIONES =====

void Informes::reparacionesPorVehiculo() {
    mostrarEncabezado("REPARACIONES POR VEHICULO");

    char patente[20];
    cout << "Patente: ";
    cin >> patente;

    FILE* archivo = fopen("reparaciones.dat", "rb");
    if (!archivo) {
        cout << "No hay reparaciones." << endl;
        return;
    }

    Reparacion rep;
    int contador = 0;
    float total = 0;

//busca reparacion y valor de servicio
    while (fread(&rep, sizeof(Reparacion), 1, archivo)) {
        if (strcmp(rep.getPatente(), patente) == 0) {
            contador++;
            total += rep.getImporte();
            cout << "Rep #" << rep.getIDReparacion()
                 << " - $" << rep.getImporte() << endl;
        }
    }
    fclose(archivo);

    cout << fixed << setprecision(2);
    cout << "Total: " << contador << " reparaciones - $" << total << endl;
}

void Informes::reparacionesPorEmpleado() {
    mostrarEncabezado("REPARACIONES POR EMPLEADO");

    int idEmpleado;
    cout << "ID Empleado: ";
    cin >> idEmpleado;

    FILE* archivo = fopen("reparaciones.dat", "rb");
    if (!archivo) {
        cout << "No hay reparaciones." << endl;
        return;
    }

    Reparacion rep;
    int contador = 0;
    float total = 0;

    while (fread(&rep, sizeof(Reparacion), 1, archivo)) {
        if (rep.getIDEmpleado() == idEmpleado) {
            contador++;
            total += rep.getImporte();
            cout << "Patente: " << rep.getPatente()
                 << " - $" << rep.getImporte() << endl;
        }
    }
    fclose(archivo);

    cout << fixed << setprecision(2);
    cout << "Total: " << contador << " reparaciones - $" << total << endl;
}

void Informes::vehiculoMasReparado() {
    mostrarEncabezado("VEHICULO MAS REPARADO");

    FILE* archivo = fopen("reparaciones.dat", "rb");
    if (!archivo) {
        cout << "No hay reparaciones." << endl;
        return;
    }

    char patentes[50][20];
    int cantidades[50];
    int cantVehiculos = 0;

    Reparacion rep;
    while (fread(&rep, sizeof(Reparacion), 1, archivo) && cantVehiculos < 50) {
        int pos = -1;
        // Buscar patente existente
        for (int i = 0; i < cantVehiculos; i++) {
            if (strcmp(patentes[i], rep.getPatente()) == 0) {
                pos = i;
                break;
            }
        }

        if (pos == -1) { // Patente nueva
            strcpy(patentes[cantVehiculos], rep.getPatente());
            cantidades[cantVehiculos] = 1;
            cantVehiculos++;
        } else { // Patente existente
            cantidades[pos]++;
        }
    }
    fclose(archivo);

    // Encontrar el máximo
    int maxRep = 0, indiceMax = 0;
    for (int i = 0; i < cantVehiculos; i++) {
        if (cantidades[i] > maxRep) {
            maxRep = cantidades[i];
            indiceMax = i;
        }
    }

    cout << "Vehiculo mas reparado:" << endl;
    cout << "Patente: " << patentes[indiceMax] << endl;
    cout << "Reparaciones: " << maxRep << endl;

    // TOP 3
    cout << "\nTOP 3:" << endl;
    for (int i = 0; i < 3 && i < cantVehiculos; i++) {
        // Buscar el siguiente máximo
        int maxTemp = 0, indiceTemp = 0;
        for (int j = 0; j < cantVehiculos; j++) {
            if (cantidades[j] > maxTemp) {
                maxTemp = cantidades[j];
                indiceTemp = j;
            }
        }
        cout << (i+1) << ". " << patentes[indiceTemp]
             << " (" << maxTemp << " rep)" << endl;
        cantidades[indiceTemp] = 0; // Para no repetir
    }
}

// ===== AUXILIARES =====

float Informes::calcularRecaudacionMes(int mes, int anio) {
    FILE* archivo = fopen("facturas.dat", "rb");
    if (!archivo) return 0;

    Factura factura;
    float total = 0;

    while (fread(&factura, sizeof(Factura), 1, archivo)) {
        if (factura.FechaEntrega.getMes() == mes &&
            factura.FechaEntrega.getAnio() == anio) {
            total += factura.ImporteTotal;
        }
    }
    fclose(archivo);
    return total;
}

float Informes::calcularRecaudacionAnio(int anio) {
    FILE* archivo = fopen("facturas.dat", "rb");
    if (!archivo) return 0;

    Factura factura;
    float total = 0;

    while (fread(&factura, sizeof(Factura), 1, archivo)) {
        if (factura.FechaEntrega.getAnio() == anio) {
            total += factura.ImporteTotal;
        }
    }
    fclose(archivo);
    return total;
}

void Informes::mostrarMenuInformes() {
    int opcion;
    do {
        cout << "\n===== INFORMES =====" << endl;
        cout << "1. Recaudacion Mensual" << endl;
        cout << "2. Recaudacion Anual" << endl;
        cout << "3. Recaudacion por Cliente" << endl;
        cout << "4. Reparaciones por Vehiculo" << endl;
        cout << "5. Reparaciones por Empleado" << endl;
        cout << "6. Vehiculo Mas Reparado" << endl;
        cout << "0. Volver" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: recaudacionMensual(); break;
            case 2: recaudacionAnual(); break;
            case 3: recaudacionPorCliente(); break;
            case 4: reparacionesPorVehiculo(); break;
            case 5: reparacionesPorEmpleado(); break;
            case 6: vehiculoMasReparado(); break;
            case 0: break;
            default: cout << "Opcion invalida." << endl;
        }

        if (opcion != 0) {
            cout << "\nEnter para continuar...";
            cin.ignore();
            cin.get();
        }

    } while (opcion != 0);
}
