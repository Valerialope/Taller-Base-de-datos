
#ifndef FUNCIONES_H
#define FUNCIONES_H

extern int numClientes; 

void registrarClientes(char listaClientes[][2][40], int maxClientes);
void buscarPorTipo(int *numHabitacion, char habitaciones[][3][40], double costos[]);
void buscarHotelPorNombre(int *numHabitacion, char habitaciones[][3][40], double costos[]);
void hacerReserva(char habitaciones[][3][40], char listaClientes[][2][40], int reservas[][4], double costos[], int maxClientes);
void buscarReservaPorCedula(int *numReserva, char listaClientes[][2][40], int reservas[][4], int maxClientes);
void mostrarReserva(int numReserva, int reservas[][4], char habitaciones[][3][40], double costos[], char listaClientes[][2][40], int maxClientes);
void pagarReserva(int numReserva, int reservas[][4], char habitaciones[][3][40], double costos[], char listaClientes[][2][40], int maxClientes);

#endif 