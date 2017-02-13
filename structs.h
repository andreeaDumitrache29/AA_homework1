#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*structura pentru a avea toate datele necesare unei tranzitii*/
typedef struct cel{
	int finalState;   // 1 daca starea este finala, 0 altfel
	char *CurrentState, *nextState;
	char InitialCode, NextCode;
	char direction;
	struct cel * next;
}TCel;

/*am stocat tranzitiile intr-un graf cu liste de adiacenta:
un vector de stari in care fiecare membru reprezinta starea curenta
apoi toate tranzitiile care pleaca din acea stare in lista corespunzatoare*/
typedef struct graph{
	int StateNumber;  //numar de stari
	TCel *list;	//vectorul cu liste de adiacenta
}StateGraph;

//functii folosite
StateGraph* AllocateGraph(int number);
void InitiateGraph(StateGraph *graph, char *state, int i);
char* InitiateTape(char * word);
void myFree(TCel *aux);
void DestroyGraph(StateGraph **graph);
int RunTape(char* tape, char* head, char* state, StateGraph* graph);
TCel* NewCel(char *s1, char *s2, char c1, char c2, char dir);
