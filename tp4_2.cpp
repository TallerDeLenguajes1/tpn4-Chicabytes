#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Tar{
    int TareaID; //Numerado en ciclo iterativo
    char *Descripcion; //
    int Duracion; // entre 10 – 100
}Tarea; 

void CargaTarea(Tarea **TareasPendientes, int cantidad);
void CambioTareas(Tarea **TareasPendientes, Tarea **TareasRealizadas, int cant); 
void Mostrar(Tarea **TareaAMostrar, int cant);
Tarea **BuscarPorPalabra(Tarea **TareaPend, Tarea **TareaReal, int cant_t);

int main (void){
    srand(time(NULL));
    int canti_tareas = 0;
    while(canti_tareas == 0 || canti_tareas > 10)
    {
        printf("Ingrese la cantidad de tareas a realizar: ");
        scanf("%d", &canti_tareas);
        fflush(stdin);
    }
    Tarea **TareasPendientes = (Tarea **)malloc(sizeof(Tarea*)*canti_tareas);
    Tarea **TareasRealizadas = (Tarea **)malloc(sizeof(Tarea*)*canti_tareas);
    Tarea **BusqPalabra;
    CargaTarea(TareasPendientes, canti_tareas);
    CambioTareas(TareasPendientes, TareasRealizadas, canti_tareas);
    Mostrar(TareasPendientes, canti_tareas);
    Mostrar(TareasRealizadas, canti_tareas);
    BusqPalabra = BuscarPorPalabra(TareasPendientes, TareasRealizadas, canti_tareas);
    Mostrar(BusqPalabra, canti_tareas);
    getchar();
    return 0;
}

void CargaTarea(Tarea **TareasPendientes, int cantidad){
    for(int i = 0; i < cantidad; i++)
    {
        TareasPendientes[i] = (Tarea*) malloc(sizeof(Tarea));
        char strauxiliar[1000];
        TareasPendientes[i]->TareaID = 1 + i;
        printf("Ingrese la descripcion de la tarea %d: ", TareasPendientes[i]->TareaID);
        gets(strauxiliar);
        fflush(stdin);
        int len = strlen(strauxiliar);
        TareasPendientes[i]->Descripcion = (char *)malloc(sizeof(char) * len);
        strcpy(TareasPendientes[i]->Descripcion, strauxiliar);
        TareasPendientes[i]->Duracion = rand()%100 + 10;
        len = 0;
    }
}

void CambioTareas(Tarea **TareasPendientes, Tarea **TareasRealizadas, int cant)
{
    char resultado;
    Tarea **TPendiente;
    Tarea **TRealizado;
    for(int j = 0; j < cant; j++)
    {
        printf("La primera tarea es: %d, ya la realizo? [y/n] ", TareasPendientes[j]->TareaID);
        scanf("%c", &resultado);
        fflush(stdin);
        if (resultado == 'y'){
            TareasRealizadas[j] = (Tarea*) malloc(sizeof(Tarea));
            TareasRealizadas[j] = TareasPendientes[j];
            TPendiente = &TareasPendientes[j];
            *TPendiente = NULL;
        }
        else{
            TRealizado = &TareasRealizadas[j];
            *TRealizado = NULL;
        }
    }
}
void Mostrar(Tarea **TareaAMostrar, int cant)
{
    for(int i=0;i<cant;i++)
    {
        if(TareaAMostrar[i] != NULL)
        {
            printf("ID: %d\n",TareaAMostrar[i]->TareaID);
            printf("Duracion: %d\n",TareaAMostrar[i]->Duracion);
            printf("Descripcion: %s\n",TareaAMostrar[i]->Descripcion);
        }
    }
}

Tarea **BuscarPorPalabra(Tarea **TareaPend, Tarea **TareaReal, int cant_t){
    int boolean;
    Tarea **Aux = (Tarea**) malloc(sizeof(Tarea));
    char Cade[100];
    printf("Ingrese la palabra clave: ");
    scanf("%s", &Cade);
    fflush(stdin);
    for (int i = 0; i < cant_t; i++)
    {
        if(TareaPend[i] != NULL){
            boolean = strcmp(TareaPend[i]->Descripcion, Cade);
            if(boolean == 0){
                Aux[i] = &(*TareaPend[i]);
                break;
            }
            else
            {
                Aux[i] = NULL;
            }
        }
    }
    for (int j = 0; j < cant_t; j++)
    {
        if(TareaReal[j] != NULL){
            boolean = strcmp(TareaReal[j]->Descripcion, Cade);
            if(boolean == 0){
                Aux[j] = &(*TareaReal[j]);
                break;
            }
            else
            {
                Aux[j] = NULL;
            }
        }
    }
    return Aux;
}