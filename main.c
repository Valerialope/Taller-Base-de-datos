#include <stdio.h>
#include "funciones.h"

#define maxClientes 10

int main() {
    char listaClientes[maxClientes][2][40];
    char habitaciones[9][3][40] = {
        {"1", "simple", "Dan Carlton"},
        {"2", "doble", "Dan Carlton"},
        {"3", "triple", "Dan Carlton"},
        {"4", "simple", "Swissotel"},
        {"5", "doble", "Swissotel"},
        {"6", "triple", "Swissotel"},
        {"7", "simple", "Sheraton"},
        {"8", "doble", "Sheraton"},
        {"9", "triple", "Sheraton"}
    };

    double costos[9] = {90, 120, 160, 65, 100, 140, 85, 110, 150};
    int reservas[10][4] = {{-1, -1, -1, 0}, {-1, -1, -1, 0}, {-1, -1, -1, 0}, {-1, -1, -1, 0}, {-1, -1, -1, 0}, {-1, -1, -1, 0}, {-1, -1, -1, 0}, {-1, -1, -1, 0}, {-1, -1, -1, 0}, {-1, -1, -1, 0}};
    
    int opcion, subopcion, numHabitacion, numReserva, continuar;

    do {
        printf("Escoja una opcion:\n1. Registrar clientes\n2. Buscar habitacion\n3. Hacer reserva\n4. Ver reservas\n5. Pagar reserva\n>>");
        scanf("%d", &opcion);
        switch (opcion) {
            case 1:
                registrarClientes(listaClientes, maxClientes);
                break;
            case 2:
                printf("1. Por tipo\n2. Por hotel\n>>");
                scanf("%d", &subopcion);
                switch (subopcion) {
                    case 1:
                        printf("Tipos de habitaciones:\n1. Simple\n2. Doble\n3. Triple\n>>");
                        buscarPorTipo(&numHabitacion, habitaciones, costos);
                        break;
                    case 2:
                        printf("Hoteles:\n1. Dan Carlton\n2. Swissotel\n3. Sheraton\n>>");
                        buscarHotelPorNombre(&numHabitacion, habitaciones, costos);
                        break;
                    default:
                        break;
                }
                break;
            case 3:
                hacerReserva(habitaciones, listaClientes, reservas, costos, maxClientes);
                break;
            case 4:
                buscarReservaPorCedula(&numReserva, listaClientes, reservas, maxClientes);
                mostrarReserva(numReserva, reservas, habitaciones, costos, listaClientes, maxClientes);
                break;
            case 5:
                buscarReservaPorCedula(&numReserva, listaClientes, reservas, maxClientes);
                pagarReserva(numReserva, reservas, habitaciones, costos, listaClientes, maxClientes);
                break;
            default:
                break;
        }
        printf("Desea elegir otra opcion    \n1 = si\t2 = no\n");
        scanf("%d", &continuar);
    } while (continuar == 1);

    return 0;
}
