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
Nodo *BorrarNodo(Nodo *Lista);//Desvincula el nodo de una lista y lo devuelve como nodo independiente.
Tarea CrearTarea(int cantidad, int _contador);
void CambioTareas(Nodo **Lista, Nodo **TareasPendientes, Nodo **TareasRealizadas, int cant); 
void MostrarLista(Nodo *Lista);
void BuscarPorPalabra(Nodo **BusqClave, Nodo **TareasPendientes, Nodo **TareasRealizadas);
void BuscarPorID(Nodo **BusqID, Nodo **TareasPendientes, Nodo **TareasRealizadas);


int main (void){
    srand(time(NULL));
    int canti_tareas = 0;
    while(canti_tareas == 0 || canti_tareas > 10)
    {
        printf("Ingrese la cantidad de tareas a realizar: ");
        scanf("%d", &canti_tareas);
        fflush(stdin);
    }
    Nodo *Lista = CrearListaVacia();
    Nodo *ListaTReal = CrearListaVacia();
    Nodo *ListaTPend = CrearListaVacia();
    Nodo *BusqClave = CrearListaVacia();
    Nodo *BusqID = CrearListaVacia();
    Nodo *Auxi;
    
    for (int cont = 0; cont < canti_tareas; cont++)
    {
        Auxi = CrearNodo(canti_tareas, cont);
        InsertarNodo(&Lista, Auxi);
    }

    CambioTareas(&Lista, &ListaTPend, &ListaTReal, canti_tareas);

    printf("=====Tareas Pendientes===== \n");
    MostrarLista(ListaTPend);

    printf("\n=====Tareas Realizadas=====\n");
    MostrarLista(ListaTReal);
    fflush(stdin);

    printf("\n=====Busqueda por Clave=====\n");
    BuscarPorPalabra(&BusqClave, &ListaTPend, &ListaTReal);
    MostrarLista(Auxi); //Por alguna extraña razon que todavia no logro entender, por mas que a la funcion le pase BusqClave, la lista aparece en Auxi... Será cosa del diablo, pero es la unica forma q me anda :(
    
    printf("\n=====Busqueda por ID=====\n");
    BuscarPorID(&BusqID, &ListaTPend, &ListaTReal);
    MostrarLista(BusqID);
    
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
    NuevaTarea.Descripcion = (char*)malloc(sizeof(char)*strlen(strauxiliar));
    strcpy(NuevaTarea.Descripcion, strauxiliar);
    NuevaTarea.Duracion = rand() % 91 + 10;
    return NuevaTarea;
}

Nodo *BorrarNodo(Nodo **Lista){
	Nodo *Aux1 = *Lista;
    *Lista = (*Lista)->Siguiente;
    Aux1->Siguiente = NULL;
    return Aux1;
}

void CambioTareas(Nodo **Lista, Nodo **TareasPendientes, Nodo **TareasRealizadas, int cant)
{
    char resultado;
    Nodo* Auxi;
    for(int j = 0; j < cant; j++)
    {
        printf("La tarea es: %d, ya la realizo? [y/n] ", (*Lista)->T.TareaID);
        scanf("%c", &resultado);
        fflush(stdin);
        Auxi = BorrarNodo(Lista);
        switch (resultado)
        {
        case 'y':
            InsertarNodo(TareasRealizadas, Auxi);
            break;
        case 'n':
            InsertarNodo(TareasPendientes, Auxi);
            break;
        default:
            break;
        }
    }
}
void MostrarLista(Nodo *Lista1){
	while(Lista1 != NULL){
		printf("\nID: %d", Lista1->T.TareaID);
		printf("\nDESCRIPCION: %s", Lista1->T.Descripcion);
		printf("\nDURACION: %d", Lista1->T.Duracion);
		Lista1 = Lista1->Siguiente;
	}
}
 
void BuscarPorPalabra(Nodo **BusqClave, Nodo **TareasPendientes, Nodo **TareasRealizadas)
{
    Nodo *Aux2;
    char Cade[20];
    printf("\nIngrese la palabra clave: ");
    gets(Cade);
    fflush(stdin);
    while((*TareasPendientes)->Siguiente != NULL)
    {
        if(strcmp((*TareasPendientes)->T.Descripcion, Cade) == 0)
        {
            Aux2 = BorrarNodo(TareasPendientes);
            InsertarNodo(BusqClave, Aux2);
            InsertarNodo(TareasPendientes, Aux2);
        }
        *TareasPendientes = (*TareasPendientes)->Siguiente;
    }
    while((*TareasRealizadas)->Siguiente != NULL)
    {
        if(strcmp((*TareasRealizadas)->T.Descripcion, Cade) == 0)
        {
            Aux2 = BorrarNodo(TareasRealizadas);
            InsertarNodo(BusqClave, Aux2);
            InsertarNodo(TareasRealizadas, Aux2);
        }
        *TareasPendientes = (*TareasPendientes)->Siguiente;
    }
}

void BuscarPorID(Nodo **BusqClave, Nodo **TareasPendientes, Nodo **TareasRealizadas)
{
    int id;
    Nodo *Nnodo;
    printf("\nIngrese el id de la tarea que quiere buscar: ");
    scanf("%d", &id);
    while((*TareasPendientes)->Siguiente != NULL)
    {
        if((*TareasPendientes)->T.TareaID == id)
        {
            Nnodo = BorrarNodo(TareasPendientes);
            InsertarNodo(BusqClave, Nnodo);
            InsertarNodo(TareasPendientes, Nnodo);
        }
        *TareasPendientes = (*TareasPendientes)->Siguiente;
    }
    while((*TareasRealizadas)->Siguiente != NULL)
    {
        if((*TareasRealizadas)->T.TareaID == id)
        {
            Nnodo = BorrarNodo(TareasRealizadas);
            InsertarNodo(BusqClave, Nnodo);
            InsertarNodo(TareasRealizadas, Nnodo);
        }
        *TareasPendientes = (*TareasPendientes)->Siguiente;
    }
}