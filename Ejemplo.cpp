#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
typedef struct 
{
    int TareaID;    //Numerado en ciclo iterativo
    char *Descripcion;  //
    int Duracion;   // entre 10 - 100
}Tarea;
void CargarTareas(Tarea **TareasPendientes, int cantTareas);
void TareasCompletadas(Tarea **TareasPendientes, Tarea **TareasRealizadas, int cantTareas);
void MostrarTareas(Tarea **TareasPendientes, Tarea **TareasRealizadas, int cantTareas);
int main(){
    srand(time(NULL));
    int cantTareas;
    printf("Ingrese la cantidad de tareas a cargar: ");
    scanf("%d", &cantTareas);
    fflush(stdin);
    Tarea **TareasPendientes;
    TareasPendientes = (Tarea **) malloc(sizeof(Tarea) * cantTareas);
    Tarea **TareasRealizadas;
    TareasRealizadas = (Tarea **) malloc(sizeof(Tarea) * cantTareas);
    CargarTareas(TareasPendientes, cantTareas);
    printf("\n\n");
    TareasCompletadas(TareasPendientes, TareasRealizadas, cantTareas);
    printf("\n\n");
    MostrarTareas(TareasPendientes, TareasRealizadas, cantTareas);
    getchar();
    return 0;
}
void CargarTareas(Tarea **TareasPendientes, int cantTareas){
    char descTarea[150];
    for (int i = 0; i < cantTareas; i++)
    {
        TareasPendientes[i] = (Tarea *) malloc(sizeof(Tarea));
        TareasPendientes[i]->TareaID = i + 1;
        TareasPendientes[i]->Duracion = rand()%91 + 10;
        printf("Ingrese la descripcion de la tarea %d: ", TareasPendientes[i]->TareaID);
        fflush(stdin);
        gets(descTarea);
        fflush(stdin);
        TareasPendientes[i]->Descripcion = (char *) malloc(sizeof(char) * strlen(descTarea));
        strcpy(TareasPendientes[i]->Descripcion, descTarea);
    }
}
void TareasCompletadas(Tarea **TareasPendientes, Tarea **TareasRealizadas, int cantTareas){
    int aux;
    printf("********* Tareas *********\n\n");
    for (int i = 0; i < cantTareas; i++)
    {
        printf("ID de la tarea: %d\n", TareasPendientes[i]->TareaID);
        printf("Descripcion: %s\n", TareasPendientes[i]->Descripcion);
        printf("Duracion: %d\n\n", TareasPendientes[i]->Duracion);
        printf("¿La tarea %d fue realizada? Presione 1 (Si fue realizada), presione 0 (Si no fue realizada): ", TareasPendientes[i]->TareaID);
        scanf("%d", &aux);
        fflush(stdin);
        printf("\n\n");
        if (aux == 1)
        {
            TareasRealizadas[i] = (Tarea *) malloc(sizeof(Tarea));
            TareasRealizadas[i]->TareaID = TareasPendientes[i]->TareaID;
            TareasRealizadas[i]->Duracion = TareasPendientes[i]->Duracion;
            TareasRealizadas[i]->Descripcion = (char *) malloc(sizeof(char) * strlen(TareasPendientes[i]->Descripcion));
            strcpy(TareasRealizadas[i]->Descripcion, TareasPendientes[i]->Descripcion);
            TareasPendientes[i] = NULL; //Apunto a NULL el puntero de la tarea que ya fue completada
        }
        else{
            TareasRealizadas = &TareasRealizadas[i];//Ésto se hace porque si no le asignas nada a una variable TENDRÁ BASURA Y NO NULL
            *TareasRealizadas = NULL;
        }
    }
}
void MostrarTareas(Tarea **TareasPendientes, Tarea **TareasRealizadas, int cantTareas){
    int i;
    printf("********* Tareas Pendientes *********\n\n");
    for ( i = 0; i < cantTareas; i++)
    {
        if (TareasPendientes[i] != NULL)
        {
            printf("ID de la tarea: %d\n", TareasPendientes[i]->TareaID);
            printf("Descripcion: %s\n", TareasPendientes[i]->Descripcion);
            printf("Duracion: %d\n", TareasPendientes[i]->Duracion);
            printf("\n");
        }
    }
    printf("********* Tareas Realizadas *********\n\n");
    for ( i = 0; i < cantTareas; i++)
    {
        printf("ID de la tarea: %d\n", TareasRealizadas[i]->TareaID);
        printf("Descripcion: %s\n", TareasRealizadas[i]->Descripcion);
        printf("Duracion: %d\n", TareasRealizadas[i]->Duracion);
        printf("\n");
    }
}