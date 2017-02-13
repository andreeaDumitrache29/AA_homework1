#include "structs.h"

int main(int argc, char const *argv[])
{
	int N,M,P, i = 0, j;
	
	//deschiderea fisierelor
	FILE *tm = fopen("tm.in", "r");
	FILE* input = fopen("tape.in", "r");
	FILE *output = fopen("tape.out", "w");

	char *word= (char*)malloc(1000 * sizeof(char));
	char*state = (char*)malloc(10 * sizeof(char));
	//citeste cuvantul dat ca input din fisierul tape.in
	fscanf(input, "%s", word);
	
	fscanf(tm, "%d", &N);
	//Alocarea grafului care va stoca tranzitiile
	StateGraph *StateGraph = AllocateGraph(N);

	for(i = 0; i < N; i++){
		/*intializez vectorul in care stochez listele de adiacenta
		aferente tuturor starilor pe masura ce le citesc*/
		fscanf(tm, "%s", state);
		InitiateGraph(StateGraph,state, i);
	}

	fscanf(tm, "%d", &M);

	/*citeste lista starilor finale si marcheaza starile corespunzatoare
	din vectorul de liste*/
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

	//citeste starea initiala
	char* InitialState = malloc(10 * sizeof(char));
	fscanf(tm, "%s", InitialState);

	fscanf(tm, "%d", &P);
	char* s1, *s2;
	s1 = malloc(10 * sizeof(char));
	s2 = malloc(10 * sizeof(char));
	char c1, c2, dir;

	/*pentru fiecare tranzitie citeste datele corespunzatoare
	construieste o noua celula cu acestea si insereaz-o in lista
	de adiacenta corespunzatoare*/
	for(i = 0; i < P; i++){
		fscanf(tm, "%s", s1);
		fgetc(tm);
		fscanf(tm, "%c", &c1);
		fscanf(tm, "%s", s2);
		fgetc(tm);
		fscanf(tm, "%c", &c2);
		fgetc(tm);
		fscanf(tm, "%c", &dir);
		
		for(j = 0; j < N; j++)
		{
			if(strcmp(StateGraph->list[j].CurrentState, s1) == 0)
			{
				TCel *aux = &(StateGraph->list[j]);
				while(aux->next != NULL)
					aux = aux->next;

				TCel *new = NewCel(s1, s2, c1, c2, dir);
				aux->next  = new;
				break;
			}
		}
	}

	//banda masinii Turing
	char *tape = InitiateTape(word);

	char *head = &(tape[1]);

	//ruleaza masina si verifica rezultatul
	int rez = RunTape(tape, head, InitialState, StateGraph);

	if(rez == 1)
		fprintf(output, "%s", tape);
	else
		fprintf(output, "Se agata!");

	free(word); 
	free(state);
	free(InitialState);
	free(s1);
	free(tape);
	free(s2);
	fclose(input);
	fclose(output);
	fclose(tm);
	DestroyGraph(&StateGraph);

	return 0;
}