#include "structs.h"

//creeaza un nou graf, aloca memorie si il returneaza
StateGraph* AllocateGraph(int number)
{
	StateGraph* List = (StateGraph*)malloc(sizeof(StateGraph));
	if(!List)
		return NULL;
	List->list = (TCel*)malloc(number * sizeof(TCel));
	if(!List->list){
		free(List);
		return NULL;
	}
	List->StateNumber = number;
	return List;
}
/*seteaza starea curenta dintr-o celula, iar restul
campurilor sunt initializate cu null; corespunzator primelor
celule din liste*/
void InitiateGraph(StateGraph *graph, char *state, int i)
{
	graph->list[i].CurrentState = strdup(state);
	graph->list[i].finalState = 0;
	graph->list[i].nextState = NULL;
	graph->list[i].next = NULL;
	graph->list[i].InitialCode = '\0';
	graph->list[i].NextCode = '\0';
	graph->list[i].direction = '\0';
}

/*creeaza o noua celula, initializeaza campurile cu datele
corespunzatoare si o returneaza*/
TCel* NewCel(char *s1, char *s2, char c1, char c2, char dir)
{
	TCel *new = (TCel*)malloc(sizeof(TCel));
	new->finalState = 0;
	new->CurrentState = strdup(s1);
	new->nextState = strdup(s2);
	new->InitialCode = c1;
	new->NextCode = c2;
	new->direction = dir;
	new->next = NULL;
	return new;
}

//pune pe banda  cuvantul citit ca input, iar in rest #
char* InitiateTape(char * word)
{	int i;
	char *tape = (char*)malloc(1001);

	for(i = 0; i < strlen(word); i++)
		tape[i] = word[i];

	for(i = strlen(word); i < 1001; i++)
		tape[i] = '#';

	return tape;
}

//elibereaza campurile structurii alocate dinamic
void myFree(TCel *aux)
{
	free(aux->CurrentState);
	free(aux->nextState);
}


//dezaloca memoria pentru graf
void DestroyGraph(StateGraph** graph)
{ int i;
  TCel *p, *aux;

  for(i = 0; i < (*graph)->StateNumber; i++)
  { 
  	p = &((*graph)->list[i]);
    while(p != NULL)
    { 
    	aux = p; p = p->next;
     	myFree(aux);
    }
  }

  free((*graph)->list);
  free(*graph);
  *graph = NULL;
}

//simuleaza masina: returneaza 1 daca se termina executia, 0 daca se agata
int RunTape(char* tape, char* head, char* state, StateGraph* graph)
{
	int i, ok = -1;
	TCel *aux;

	/*repeta pana ajungi in star finala sau se agata*/
	while(1)
	{
		for(i = 0; i < graph->StateNumber; i++)
		{	
			//cauta intrarea corespunzatoare starii curente in vectorul de liste
			if(strcmp(graph->list[i].CurrentState, state) == 0)
			{
				aux = &(graph->list[i]);
				break;
			}
		}
		printf("%s %c\n", state, *head);
		//daca este stare finala, returneaza 1
		if(aux->finalState == 1)
		{	
			return 1;
		}

		ok = 0;

		/*altfel, parcurge lista pana ajungi la caracterul indicat de 
		capul de citire, sau la final*/
		while(aux != NULL)
		{
			if(aux->InitialCode == *head)
			{	
				ok =1;  //s-a gasit tranzitia corespunzatoare
				break;
			}

			aux = aux->next;
		}

		//daca s-a gasit tranzitia si nu s-a ajuns la finalul listei
		if(ok == 1 && aux != NULL )
		{	
			//actualizeaza caracterul pe banda, starea si muta capul
			*head = aux->NextCode;
			state = strdup(aux->nextState);
			if(aux->direction == 'R')
				head++;
			else if(aux->direction == 'L')
				head--;
		}
		else
			return 0;	//nu s-a gasit o tranzitie corespunzatoare => se agata
	}
}