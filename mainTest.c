#include "structs.h"

int main(int argc, char const *argv[])
{
	int N,M,P, i = 0, j;
	
	FILE *tm = fopen("tm.in", "r");
	FILE* input = fopen("tape.in", "r");
	FILE *output = fopen("tape.out", "w");

	char word[1750];
	fscanf(input, "%s", word);
	char state[100];
	
	fscanf(tm, "%d", &N);
	StateGraph *StateGraph = AllocateGraph(N);

	for(i = 0; i < N; i++){
		fscanf(tm, "%s", state);
		InitiateGraph(StateGraph,state, i);
	}

	fscanf(tm, "%d", &M);

	for (i = 0; i < M; i++)
	{
		fscanf(tm, "%s", state);

		for(j = 0; j < N; j++)
		{
			if(strcmp(StateGraph->list[j].CurrentState, state) == 0)
			{	
				StateGraph->list[j].finalState = 1;
				break;
			}
		}
	}

	char InitialState[100];
	fscanf(tm, "%s", InitialState);

	fscanf(tm, "%d", &P);
	char s1[100];
	char s2[100];
	char c1, c2, dir;

	for(i = 0; i < P; i++){
		fscanf(tm, "%s", s1);
		getc(tm);
		fscanf(tm, "%c", &c1);
		getc(tm);
		fscanf(tm, "%s", s2);
		getc(tm);
		fscanf(tm, "%c", &c2);
		getc(tm);
		fscanf(tm, "%c", &dir);
		
		for(j = 0; j < N; j++)
		{
			if(strcmp(StateGraph->list[j].CurrentState, s1) == 0)
			{
				TCel *aux = &(StateGraph->list[j]);
				while(aux->next != NULL)
					aux = aux->next;

				TCel *new = (TCel*)malloc(sizeof(TCel));
				new->finalState = 0;
				new->CurrentState = strdup(s1);
				new->nextState = strdup(s2);
				new->InitialCode = c1;
				new->NextCode = c2;
				new->direction = dir;
				new->next = NULL;
				aux->next  = new;
				break;
			}
		}
	}

	char tape[1751];

	for(i = 0; i < strlen(word); i++)
		tape[i] = word[i];

	for(i = strlen(word); i < 1751; i++)
		tape[i] = '#';

	char *head = &(tape[1]);

	int rez = RunTape(tape, head, InitialState, StateGraph);

	if(rez == 1)
		fprintf(output, "%s", tape);
	else
		fprintf(output, "Se agata!");

	fclose(input);
	fclose(output);
	fclose(tm);
	DestroyGraph(&StateGraph);

	return 0;
}