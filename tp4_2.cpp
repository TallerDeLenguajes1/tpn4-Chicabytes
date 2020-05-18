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
void Mostrar(Tarea **TareasPendientes, Tarea **TareasRealizadas, int cant);

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
    CargaTarea(TareasPendientes, canti_tareas);
    CambioTareas(TareasPendientes, TareasRealizadas, canti_tareas);
    Mostrar(TareasPendientes, TareasRealizadas, canti_tareas);
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
void Mostrar(Tarea **TareasPendientes, Tarea **TareasRealizadas, int cant)
{
    printf("============Tareas Pendientes============\n");
    for(int i=0;i<cant;i++)
    {
        if(*(&TareasPendientes[i]) != NULL) 
        {
            printf("ID: %d\n",TareasPendientes[i]->TareaID);
            printf("Duracion: %d\n",TareasPendientes[i]->Duracion);
            printf("Descripcion: %s\n",TareasPendientes[i]->Descripcion);
        }
        
    }
    printf("============Tareas Realizadas============\n");
    for(int i=0;i<cant;i++)
    {
        if(*(&TareasRealizadas[i]) != NULL)
        {
            printf("ID: %d\n",TareasRealizadas[i]->TareaID);
            printf("Duracion: %d\n",TareasRealizadas[i]->Duracion);
            printf("Descripcion: %s\n",TareasRealizadas[i]->Descripcion);
        }
    }
}