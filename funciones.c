#include "funciones.h"
#include <stdio.h>
#include <string.h>

int numClientes = 0;

void registrarClientes(char listaClientes[][2][40], int maxClientes) {
    int cantidad;
    printf("Ingrese la cantidad de clientes a registrar:\n");
    scanf("%d", &cantidad);
    if (numClientes + cantidad > maxClientes) {
        printf("Error: No hay suficiente espacio para %d clientes.\n", cantidad);
        fflush(stdin);
        return;
    }
    for (int indice = numClientes; indice < numClientes + cantidad; indice++) {
        printf("Ingrese el nombre del cliente %d:\n", indice + 1);
        fflush(stdin);
        scanf("%s", listaClientes[indice][0]);
        printf("Ingrese la cedula del cliente %d:\n", indice + 1);
        scanf("%s", listaClientes[indice][1]);
        fflush(stdin);
        int duplicado = 0;
        for (int j = 0; j < numClientes; j++) {
            if (strcmp(listaClientes[j][1], listaClientes[indice][1]) == 0) {
                duplicado = 1;
                break;
            }
        }
        if (duplicado) {
            printf("La cedula ya ha sido ingresada anteriormente.\n");
            indice--;
            fflush(stdin);
        }
    }
    numClientes += cantidad;
}

void buscarPorTipo(int *numHabitacion, char habitaciones[][3][40], double costos[]) {
    char tipo[40];
    printf("Ingrese el tipo de habitacion (Ej: Simple, Doble, Suite):\n");
    scanf("%s", tipo);
    int encontrado = 0;
    for (int i = 0; i < 9; i++) {
        if (strcmp(habitaciones[i][1], tipo) == 0) {
            printf("Habitacion %d: %s, tipo: %s, costo: %.2f\n", i + 1, habitaciones[i][0], tipo, costos[i]);
            encontrado = 1;
        }
    }
    if (!encontrado) {
        printf("No se encontraron habitaciones del tipo %s.\n", tipo);
    }
}

void buscarHotelPorNombre(int *numHabitacion, char habitaciones[][3][40], double costos[]) {
    char nombre[40];
    printf("Ingrese el nombre del hotel:\n");
    scanf("%s", nombre);
    int encontrado = 0;
    for (int i = 0; i < 9; i++) {
        if (strcmp(habitaciones[i][2], nombre) == 0) {
            printf("Habitacion %d: %s, tipo: %s, costo: %.2f\n", i + 1, habitaciones[i][0], habitaciones[i][1], costos[i]);
            *numHabitacion = i + 1;
            encontrado = 1;
        }
    }
    if (!encontrado) {
        printf("No se encontró el hotel %s.\n", nombre);
    }
}

void hacerReserva(char habitaciones[][3][40], char listaClientes[][2][40], int reservas[][4], double costos[], int maxClientes) {
    int numHabitacion;
    char cedula[40];

    printf("Ingrese el numero de habitacion que desea reservar: ");
    scanf("%d", &numHabitacion);

    int i;
    for (i = 0; i < maxClientes; i++) {
        if (reservas[i][0] == numHabitacion) {
            printf("La habitación %d ya está reservada.\n", numHabitacion);
            return;
        }
    }

    
    printf("Ingrese su cedula: ");
    scanf("%s", cedula);

    int clienteIndice = -1;
    for (int j = 0; j < numClientes; j++) {
        if (strcmp(listaClientes[j][1], cedula) == 0) {
            clienteIndice = j;
            break;
        }
    }

    if (clienteIndice == -1) {
        printf("No se encontró un cliente con la cedula %s.\n", cedula);
        return;
    }

    for (i = 0; i < maxClientes; i++) {
        if (reservas[i][0] != -1 && reservas[i][2] == clienteIndice + 1) {
            printf("Usted ya tiene una reserva.\n");
            return;
        }
    }

    for (i = 0; i < maxClientes; i++) {
        if (reservas[i][0] == -1) {
            reservas[i][0] = numHabitacion;
            reservas[i][1] = numHabitacion; 
            reservas[i][2] = clienteIndice + 1;
            printf("Reserva realizada con exito.\n");

            FILE *archivo = fopen("reservas.txt", "a");
            if (archivo != NULL) {
                fprintf(archivo, "Reserva %d:\n", i + 1);
                fprintf(archivo, "Cliente: %s, cedula: %s\n", listaClientes[clienteIndice][0], listaClientes[clienteIndice][1]);
                fprintf(archivo, "Habitacion: %s, tipo: %s, costo: %.2f\n\n", habitaciones[numHabitacion - 1][0], habitaciones[numHabitacion - 1][1], costos[numHabitacion - 1]);
                fclose(archivo);
            } else {
                printf("Error al abrir el archivo para guardar la reserva.\n");
            }

            return;
        }
    }
}

void buscarReservaPorCedula(int *numReserva, char listaClientes[][2][40], int reservas[][4], int maxClientes) {
    char cedula[40];
    printf("Ingrese la cedula del cliente:\n");
    scanf("%s", cedula);

    int encontrado = 0;
    for (int i = 0; i < maxClientes; i++) {
        for (int j = 0; j < numClientes; j++) {
            if (strcmp(listaClientes[j][1], cedula) == 0 && reservas[i][2] == j + 1) {
                *numReserva = i;
                encontrado = 1;
                break;
            }
        }
        if (encontrado) {
            break;
        }
    }

    if (!encontrado) {
        printf("No se encontró una reserva con la cedula %s.\n", cedula);
    }
}

void mostrarReserva(int numReserva, int reservas[][4], char habitaciones[][3][40], double costos[], char listaClientes[][2][40], int maxClientes) {
    int cliente = reservas[numReserva][2];
    int habitacion = reservas[numReserva][0];
    printf("Reserva %d:\n", numReserva + 1);
    printf("Cliente: %s, cedula: %s\n", listaClientes[cliente - 1][0], listaClientes[cliente - 1][1]);
    printf("Habitacion: %s, tipo: %s, costo: %.2f\n", habitaciones[habitacion - 1][0], habitaciones[habitacion - 1][1], costos[habitacion - 1]);
    if (reservas[numReserva][3] == 1) {
        printf("Estado de pago: PAGADO\n");
    } else {
        printf("Estado de pago: PENDIENTE\n");
    }

    FILE *archivo = fopen("reservas.txt", "a");
    if (archivo != NULL) {
        fprintf(archivo, "Reserva %d:\n", numReserva + 1);
        fprintf(archivo, "Cliente: %s, cedula: %s\n", listaClientes[cliente - 1][0], listaClientes[cliente - 1][1]);
        fprintf(archivo, "Habitacion: %s, tipo: %s, costo: %.2f\n", habitaciones[habitacion - 1][0], habitaciones[habitacion - 1][1], costos[habitacion - 1]);
        if (reservas[numReserva][3] == 1) {
            fprintf(archivo, "Estado de pago: PAGADO\n\n");
        } else {
            fprintf(archivo, "Estado de pago: PENDIENTE\n\n");
        }
        fclose(archivo);
    } else {
        printf("Error al abrir el archivo para guardar la reserva.\n");
    }
}

void pagarReserva(int numReserva, int reservas[][4], char habitaciones[][3][40], double costos[], char listaClientes[][2][40], int maxClientes) {
    int cliente = reservas[numReserva][2];
    int habitacion = reservas[numReserva][0];
    double costo = costos[habitacion - 1];

    printf("Reserva %d:\n", numReserva + 1);
    printf("Cliente: %s, cedula: %s\n", listaClientes[cliente - 1][0], listaClientes[cliente - 1][1]);
    printf("Habitacion: %s, tipo: %s, costo: %.2f\n", habitaciones[habitacion - 1][0], habitaciones[habitacion - 1][1], costo);

    printf("Ingrese el monto a pagar: ");
    double monto;
    scanf("%lf", &monto);

    if (monto < costo) {
        printf("El monto ingresado es insuficiente. Monto pendiente: %.2f\n", costo - monto);
        return;
    }

    printf("Pago realizado con exito. Cambio: %.2f\n", monto - costo);

    
    reservas[numReserva][3] = 1;

    FILE *archivo = fopen("reservas.txt", "r+");
    if (archivo != NULL) {
      
        char buffer[1000];
        while (fgets(buffer, sizeof(buffer), archivo)) {
            if (strncmp(buffer, "Reserva", 7) == 0 && buffer[7] == ' ') {
                int reservaNum;
                sscanf(buffer, "Reserva %d:", &reservaNum);
                if (reservaNum == numReserva + 1) {
                    fseek(archivo, -strlen(buffer), SEEK_CUR);
               
                    fprintf(archivo, "Estado de pago: PAGADO\n\n");
                    break;
                }
            }
        }
        fclose(archivo);
    } else {
        printf("Error al abrir el archivo para actualizar el estado de pago.\n");
    }
}

