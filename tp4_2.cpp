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
Tarea **BuscarPorID(Tarea **TareaPendiente, Tarea **TareaRealizada, int cant,  int id);

int main (void){
    srand(time(NULL));
    int canti_tareas = 0;
    int id;
    while(canti_tareas == 0 || canti_tareas > 10)
    {
        printf("Ingrese la cantidad de tareas a realizar: ");
        scanf("%d", &canti_tareas);
        fflush(stdin);
    }
    Tarea **TareasPendientes = (Tarea **)malloc(sizeof(Tarea*)*canti_tareas);
    Tarea **TareasRealizadas = (Tarea **)malloc(sizeof(Tarea*)*canti_tareas);
    Tarea **TareaEncontrada = (Tarea **)malloc(sizeof(Tarea*)*canti_tareas);
    CargaTarea(TareasPendientes, canti_tareas);
    CambioTareas(TareasPendientes, TareasRealizadas, canti_tareas);
    printf("=====Tareas Pendientes===== \n");
    Mostrar(TareasPendientes, canti_tareas);
    printf("\n=====Tareas Realizadas=====\n");
    Mostrar(TareasRealizadas, canti_tareas);
    fflush(stdin);
    printf("\nIngrese el id de la tarea que quiere buscar: ");
    scanf("%d", &id);
    TareaEncontrada = BuscarPorID(TareasPendientes, TareasRealizadas, canti_tareas, id);
    Mostrar(TareaEncontrada, canti_tareas);
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
            TareasRealizadas[j] = (Tarea *) malloc(sizeof(Tarea));
            TareasRealizadas[j]->TareaID = TareasPendientes[j]->TareaID;
            TareasRealizadas[j]->Duracion = TareasPendientes[j]->Duracion;
            TareasRealizadas[j]->Descripcion = (char *) malloc(sizeof(char) * strlen(TareasPendientes[j]->Descripcion));
            strcpy(TareasRealizadas[j]->Descripcion, TareasPendientes[j]->Descripcion);
            TareasPendientes[j] = NULL;
        }
        else{
            TareasRealizadas[j] = NULL;
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

Tarea **BuscarPorID(Tarea **TareaPendiente, Tarea **TareaRealizada, int cant, int id)
{
    Tarea **Aux;
    for(int i = 0; i < cant;i++)
    {
        if(TareaPendiente[i] != NULL)
        {
            if(TareaPendiente[i]->TareaID == id)
            {
                Aux[i]=&(*TareaPendiente[i]);
            }else{
                Aux[i] = NULL;
            }
        }
        for(int j = 0; j<cant;j++)
        {
            if (TareaRealizada[j] != NULL)
            {
                if(TareaRealizada[j]->TareaID == id)
                {
                    Aux[j]=&(*TareaRealizada[j]);
                }else{
                    Aux[j] = NULL;
                }
            }
        }
    }
    return Aux;
}