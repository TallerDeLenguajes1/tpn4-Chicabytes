#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Tar{
    int TareaID; //Numerado en ciclo iterativo
    char *Descripcion; //
    int Duracion; // entre 10 – 100
}Tarea;

typedef struct Nodo{
    Tarea T;
    Nodo *Siguiente;
}Nodo;

Nodo *CrearListaVacia();
Nodo *CrearNodo(int cantidad, int contador);
void InsertarNodo(Nodo **Lista, Nodo *Nnodo);
Nodo *BorrarNodo(Nodo *Lista);
Tarea CrearTarea(int cantidad, int _contador);
void CambioTareas(Nodo **TareasPendientes, Nodo **TareasRealizadas, int cant); 
void MostrarLista(Nodo *Lista);
//Tarea **BuscarPorID(Tarea **TareaPendiente, Tarea **TareaRealizada, int cant,  int id);
//Tarea **BuscarPorPalabra(Tarea **TareaPend, Tarea **TareaReal, int cant_t);

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
    Nodo *ListaTReal = CrearListaVacia();
    Nodo *ListaTPend = CrearListaVacia();
    Nodo *Aux;
    //Tarea **TareaEncontrada = (Tarea **)malloc(sizeof(Tarea*)*canti_tareas);
    //Tarea **BusqPalabra;
    for (int cont = 0; cont < canti_tareas; cont++)
    {
        Aux = CrearNodo(canti_tareas, cont);
        InsertarNodo(&ListaTPend, Aux);
    }
    CambioTareas(&ListaTPend, &ListaTReal, canti_tareas);
    printf("=====Tareas Pendientes===== \n");
    MostrarLista(ListaTPend);
    printf("\n=====Tareas Realizadas=====\n");
    MostrarLista(ListaTReal);
    fflush(stdin);
    /*printf("\nIngrese el id de la tarea que quiere buscar: ");
    scanf("%d", &id);
    TareaEncontrada = BuscarPorID(TareasPendientes, TareasRealizadas, canti_tareas, id);
    Mostrar(TareaEncontrada, canti_tareas); 
    BusqPalabra = BuscarPorPalabra(TareasPendientes, TareasRealizadas, canti_tareas);
    Mostrar(BusqPalabra, canti_tareas);*/
    return 0;
}

Nodo *CrearListaVacia(){
    return NULL;
}
Nodo *CrearNodo(int cantidad, int contador){
    Nodo *NNodo = (Nodo*)malloc(sizeof(Nodo));
    NNodo->T = CrearTarea(cantidad, contador);
    NNodo->Siguiente = NULL;
    return NNodo;
}
void InsertarNodo(Nodo **Lista, Nodo *NNodo){
	NNodo->Siguiente = *Lista;
	*Lista = NNodo;
}

Tarea CrearTarea(int cantidad, int _contador){
    char strauxiliar[1000];
    printf("Ingrese la descripcion de la tarea %d: ", _contador+1);
    gets(strauxiliar);
    fflush(stdin);
    Tarea NuevaTarea;
    NuevaTarea.TareaID = 1 + _contador;
    printf("%d", _contador);
    NuevaTarea.Descripcion = (char*)malloc(sizeof(char)*strlen(strauxiliar));
    strcpy(NuevaTarea.Descripcion, strauxiliar);
    NuevaTarea.Duracion = rand() % 91 + 10;
    return NuevaTarea;
}

Nodo *BorrarNodo(Nodo **Lista){
	Nodo *Aux = *Lista;
	*Lista = (*Lista)->Siguiente;
    return Aux;
}

void CambioTareas(Nodo **TareasPendientes, Nodo **TareasRealizadas, int cant)
{
    char resultado;
    Nodo* Aux;
    Nodo **Tareas = TareasPendientes;
    for(int j = 0; j < cant; j++)
    {
        printf("La tarea es: %d, ya la realizo? [y/n] ", (*Tareas)->T.TareaID);
        scanf("%c", &resultado);
        fflush(stdin);
        switch (resultado)
        {
        case 'y':
            (*Tareas)->Siguiente;
            Aux = BorrarNodo(Tareas);
            InsertarNodo(TareasRealizadas, Aux);
            break;
        case 'n':
            (*Tareas)->Siguiente;
            break;
        default:
            break;
        }
    }
}
void MostrarLista(Nodo *Lista){
	while(Lista != NULL){
		printf("\nID: %d", Lista->T.TareaID);
		printf("\nDESCRIPCION: %s", Lista->T.Descripcion);
		printf("\nDURACION: %d", Lista->T.Duracion);
		Lista = Lista->Siguiente;
	}
}
 /*
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
}*/