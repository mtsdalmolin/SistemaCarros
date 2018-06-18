#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "carro.h"
#include "arvoreplaca.h"

ArvPlaca* criaArvPlacaVazia()
{
	return NULL;
}

bool ArvPlacaVazia(ArvPlaca* arvorePlacas)
{
	return arvorePlacas == NULL;
}

void imprimeArvPlaca(ArvPlaca* arvorePlacas)
{
	if (!ArvPlacaVazia(arvorePlacas))
	{
		imprimeArvPlaca(arvorePlacas->esq);
		printf("------CARRO------\nPlaca: %s\n",arvorePlacas->placa);
		imprimeArvPlaca(arvorePlacas->dir);
	}
}

ArvPlaca* insereArvPlaca(ArvPlaca* arvorePlacas, Carro* carroAlvo, char* placa)
{
	int retornoStrcmp;
	if (ArvPlacaVazia(arvorePlacas))
	{
		arvorePlacas = (ArvPlaca*) malloc(sizeof(ArvPlaca));
		strcpy(arvorePlacas->placa, placa);
		arvorePlacas->carro = carroAlvo;
		arvorePlacas->esq = arvorePlacas->dir = NULL;
	} else {
	    retornoStrcmp = strcmp(placa, arvorePlacas->placa);
		if (retornoStrcmp < 0)
			arvorePlacas->esq = insereArvPlaca(arvorePlacas->esq, carroAlvo, placa);
		else
			arvorePlacas->dir = insereArvPlaca(arvorePlacas->dir, carroAlvo, placa);
	}
	return arvorePlacas;
}

ArvPlaca* removePlaca(ArvPlaca* arvorePlacas, char* placa)
{
	int retornoStrcmp;
	if(ArvPlacaVazia(arvorePlacas))
		return NULL; 
	else
	{
		retornoStrcmp = strcmp(arvorePlacas->placa, placa);
		if(retornoStrcmp > 0)
			arvorePlacas->esq= removePlaca(arvorePlacas->esq, placa);
		else if(retornoStrcmp < 0)
			arvorePlacas->dir= removePlaca(arvorePlacas->dir, placa);
		else
		{
			if (arvorePlacas->esq == NULL && arvorePlacas->dir == NULL)
			{
				free(arvorePlacas);
				arvorePlacas = NULL;
			} else if (arvorePlacas->esq == NULL) {
				ArvPlaca* aux = arvorePlacas;
				arvorePlacas = arvorePlacas->dir;
				free(aux);
			} else if (arvorePlacas->dir == NULL) {
				ArvPlaca* aux = arvorePlacas;
				arvorePlacas = arvorePlacas->esq;
				free(aux);
			} else {
				ArvPlaca* aux = arvorePlacas->esq;
				while (aux->dir != NULL)
					aux = aux->dir;
				strcpy(arvorePlacas->placa, aux->placa);
				strcpy(aux->placa, placa);
				arvorePlacas->esq = removePlaca(arvorePlacas->esq, placa);
			}
		}
	}
	return arvorePlacas;
}

ArvPlaca* buscaPlaca(ArvPlaca* arvorePlacas, char* placa)
{
	int retornoStrcmp;
	if (arvorePlacas == NULL)
		return NULL;
	retornoStrcmp = strcmp(arvorePlacas->placa, placa);
	if (retornoStrcmp < 0)
		arvorePlacas = buscaPlaca(arvorePlacas->dir, placa);
	else if (retornoStrcmp > 0)
		arvorePlacas = buscaPlaca(arvorePlacas->esq, placa);
	return arvorePlacas;
}