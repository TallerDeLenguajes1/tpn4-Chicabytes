#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef struct Tarea{
	int TareaID;
	char *Descripcion;
	int Duracion;
}Tareas;

//------------PROTOTIPOS------------

Tareas *Interfaz();
void mostrar(Tareas *p_tarea);
//--------MAIN-----------
int main(){
	Tareas *tarea;//tarea es una variable que contiene la direccion de memoria de una estructura de tipo Tareas.
	
	tarea = Interfaz();//tarea es un puntero, Interfaz me tiene que devolver un puntero tambien
	mostrar(tarea);
	
	
	return 0;
}

//---------FUNCIONES------------

Tareas *Interfaz(){
	Tareas **p_tarea;//p_tarea es una variable que contiene la direccion de un puntero
	int cant_tareas,tamanio,i;
	char descripcion[100];
	

	printf("Igrese el numero de tareas:\n");
	scanf("%d",&cant_tareas);
	p_tarea = (Tareas **)malloc(sizeof(Tareas*)*cant_tareas);//reservo la memoria para p_tarea 
	if(p_tarea==NULL){//¿p_tarea contiene una direccion de memoria,está bien hacer p_tarea==NULL(acá estaría verificando si el doble puntero)? ¿o debe ser *p_tarea==NULL(acá estaría verificando si mi puntero está vacio)?
		printf("error al reservar memoria");
	}else{
		printf("se reservo la memoria para p_tarea\n");
	}
	
	// usando notacion de asterisco
	/*for(i=1; i<=cant_tareas;i++)
	{
		(*p_tarea)[i].TareaID = i ;//al hacer (*p_tarea)[i] no estaría accediendo a la memoria de mi puntero? no deberia hacer (**p_tarea)[i] para colocar en la cariable misma el valor i?
		(*p_tarea)[i].Duracion = rand() % 91 + 10;
		printf("Ingrese una descripcion de la tarea:\n");
		fflush(stdin);
		fgets(descripcion,100,stdin);
		tamanio= strlen(descripcion);
		(*p_tarea)[i].Descripcion = (char*)malloc(sizeof(char)*tamanio);
		
		if((*p_tarea)[i].Descripcion==NULL)
		{
			printf("error al reservar memoria para la descripcion");
		}else{
			strcpy((*p_tarea)[i].Descripcion,descripcion);
		}	
	
	}*/
	
	//usando notacion de flecha
	for(i=1; i<=cant_tareas;i++)
	{
		p_tarea[i]->TareaID = i ;//al hacer (*p_tarea)[i] no estaría accediendo a la memoria de mi puntero? no deberia hacer (**p_tarea)[i] para colocar en la cariable misma el valor i?
		p_tarea[i]->Duracion = rand() % 91 + 10;
		printf("Ingrese una descripcion de la tarea:\n");
		fflush(stdin);
		fgets(descripcion,100,stdin);
		tamanio= strlen(descripcion);
		p_tarea[i]->Descripcion = (char*)malloc(sizeof(char)*tamanio);
		
		if(p_tarea[i]->Descripcion==NULL)
		{
			printf("error al reservar memoria para la descripcion");
		}else{
			strcpy(p_tarea[i]->Descripcion,descripcion);
		}	
	
	}
	
	
	
	return *p_tarea;
}

void mostrar(Tareas *p_tarea){
	int i,cant;
	
	printf("\nIngrese nuevamente la cantidad de tareas:\n");
	scanf("%d",&cant);
	for(i=1;i<=cant;i++)
	{
		printf("tarea #%d\n",i);
		printf("ID: %d\n", (p_tarea)[i].TareaID);//¿porqué me muestra el contenido y no la direccion? no deberia ser (*p_tarea)[i].TareaID?
		printf("Duracion: %d\n",(p_tarea)[i].Duracion);
		puts((p_tarea)[i].Descripcion);
		printf("\n\n");
	}
	
}
