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
    Tarea **TareasPendientes = (Tarea **)malloc(sizeof(Tarea*)*canti_tareas);//ésto es para asignar memoria para los punteros! Éste TIENE PUNTERO DOBLE (**) PORQUE SERÁN PUNTEROS!
    Tarea **TareasRealizadas = (Tarea **)malloc(sizeof(Tarea*)*canti_tareas);//"" "" " " " " "  "" " " " " " " " " " "" " " " "
    CargaTarea(TareasPendientes, canti_tareas);
    CambioTareas(TareasPendientes, TareasRealizadas, canti_tareas);
    Mostrar(TareasPendientes, TareasRealizadas, canti_tareas);//Mostrar Los arreglos luego de cargado de tareas y cambio de tareas
    getchar();
    return 0;
}

void CargaTarea(Tarea **TareasPendientes, int cantidad){
    for(int i = 0; i < cantidad; i++)
    {
        TareasPendientes[i] = (Tarea*) malloc(sizeof(Tarea));//ésto es porque le vas a asignar memoria particular a cada tarea ESTE TIENE PUNTERO SIMPLE (*) PORQUE no será puntero! Será un elemento de un arreglo.
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
    Tarea **TPendiente;//Puntero Doble que aputará al arreglo de pendientes
    Tarea **TRealizado;//Puntero Doble que aputará al arreglo de realizados
    for(int j = 0; j < cant; j++)
    {
        printf("La primera tarea es: %d, ya la realizo? [y/n] ", TareasPendientes[j]->TareaID);
        scanf("%c", &resultado);
        fflush(stdin);
        if (resultado == 'y'){
            TareasRealizadas[j] = (Tarea*) malloc(sizeof(Tarea)); //Asignarás la memoria particular para la tarea
            TareasRealizadas[j] = TareasPendientes[j];//Igualarás los elementos del arreglo pendientes y realizados
            TPendiente = &TareasPendientes[j]; //copiarás la dirección de memoria de LA tarea, NO la del arreglo.
            *TPendiente = NULL; // E igualarás el contenido de la dirección de memoria a NULL por eso el puntero (*)
        }
        else{
            TRealizado = &TareasRealizadas[j];//Ésto se hace porque si no le asignas nada a una variable TENDRÁ BASURA Y NO NULL
            *TRealizado = NULL;//Por lo que le asignaremos NULL cuando el usuario ingrese que no se realizó la tarea
        }
    }
}
void Mostrar(Tarea **TareasPendientes, Tarea **TareasRealizadas, int cant)
{
    printf("============Tareas Pendientes============\n");
    for(int i=0;i<cant;i++)
    {
        if(*(&TareasPendientes[i]) != NULL) //*(&TP[i]) es igual a *TPendiente que hicimos antes SI NO ES NULL SE MOSTRARÁ EL CONTENIDO DEL ELEMENTO
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
