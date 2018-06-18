#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "carro.h"
#include "arvoreanos.h"

ArvAno* criaArvAnoVazia()
{
	return NULL;
}

bool ArvAnoVazia(ArvAno* arvoreAnos)
{
	return arvoreAnos == NULL;
}

void imprimeArvAno(ArvAno* arvoreAnos)
{
	if (!ArvAnoVazia(arvoreAnos))
	{
		imprimeArvAno(arvoreAnos->esq);
		printf("-----ANO: %d-----\n", arvoreAnos->ano);
		imprimeArvAno(arvoreAnos->dir);
	}
}

ArvAno* insereArvAno(ArvAno* arvoreAnos, Carro* carroAlvo, int ano)
{
	if (ArvAnoVazia(arvoreAnos))
	{
		arvoreAnos = (ArvAno*) malloc(sizeof(ArvAno));
		arvoreAnos->ano = ano;
		arvoreAnos->esq = arvoreAnos->dir = criaArvAnoVazia();
		arvoreAnos->listaCarrosAno = insereCarroAno(NULL, carroAlvo);
	} else {
		if (ano < arvoreAnos->ano)
			arvoreAnos->esq = insereArvAno(arvoreAnos->esq, carroAlvo, ano);
		else if (ano > arvoreAnos->ano)
			arvoreAnos->dir = insereArvAno(arvoreAnos->dir, carroAlvo, ano);
		else
			arvoreAnos->listaCarrosAno = insereCarroAno(arvoreAnos->listaCarrosAno, carroAlvo);
	}
	return arvoreAnos;
}

ArvAno* removeAno(ArvAno* arvoreAnos, int ano, char* placa)
{
	if(ArvAnoVazia(arvoreAnos))
		return NULL;
	if (ano < arvoreAnos->ano)
	{
		arvoreAnos->esq = removeAno(arvoreAnos->esq, ano, placa);
	}
	else if (ano > arvoreAnos->ano)
	{
		arvoreAnos->dir = removeAno(arvoreAnos->dir, ano, placa);
	}
	else
	{
		arvoreAnos->listaCarrosAno = excluiCarroAno(arvoreAnos->listaCarrosAno, placa);
		if (arvoreAnos->listaCarrosAno == NULL)
		{
			if (arvoreAnos->esq == NULL && arvoreAnos->dir == NULL)
			{
				free(arvoreAnos);
				arvoreAnos = NULL;
			} else if (arvoreAnos->esq == NULL) {
				ArvAno* aux = arvoreAnos;
				arvoreAnos = arvoreAnos->dir;
				free(aux);
			} else if (arvoreAnos->dir == NULL) {
				ArvAno* aux = arvoreAnos;
				arvoreAnos = arvoreAnos->esq;
				free(aux);
			} else {
				ArvAno* aux = arvoreAnos->esq;
				while (aux->dir != NULL)
					aux = aux->dir;
				arvoreAnos->ano = aux->ano;
				aux->ano = ano;
				arvoreAnos->esq = removeAno(arvoreAnos->esq, ano, placa);
			}
		}
	}
	return arvoreAnos;
}

ArvAno* buscaAno(ArvAno* arvoreAnos, int ano)
{
	if (arvoreAnos == NULL)
		return NULL;
	if (arvoreAnos->ano < ano)
		arvoreAnos = buscaAno(arvoreAnos->dir, ano);
	else if (arvoreAnos->ano > ano)
		arvoreAnos = buscaAno(arvoreAnos->esq, ano);
	return arvoreAnos;
}

ArvAno* imprimeCarrosAno(ArvAno* arvoreAnos, ArvAno* anoAlvo)
{
	ListaA* aux;
	if (ArvAnoVazia(arvoreAnos))
		return NULL;
	imprimeCarrosAno(arvoreAnos->esq, anoAlvo);
	for (aux = arvoreAnos->listaCarrosAno; aux != NULL; aux = aux->prox)
		if (anoAlvo->ano == aux->carro->ano)
			printf("------CARRO------\nAno: %d\nPlaca: %s\nMarca: %s\n", aux->carro->ano, aux->carro->placa, aux->carro->marca);
	imprimeCarrosAno(arvoreAnos->dir, anoAlvo);
	return arvoreAnos;
}

ListaA* insereCarroAno(ListaA* listaCarrosAno, Carro* carroAlvo)
{
	ListaA* novoCarro = (ListaA*) malloc(sizeof(ListaA));
	novoCarro->carro = carroAlvo;
	novoCarro->prox = listaCarrosAno;
	return novoCarro;
}

ListaA* excluiCarroAno(ListaA* listaCarrosAno, char* placa)
{
	int placaIgual;
	ListaA* aux;
	ListaA* ant = NULL;
	for (aux = listaCarrosAno; aux != NULL; aux = aux->prox)
	{
		placaIgual = strcmp(aux->carro->placa, placa);
		if (!placaIgual)
		{
			if (ant == NULL)
			{
				listaCarrosAno = listaCarrosAno->prox;
				break;
			} else {
				ant->prox = aux->prox;
				break;
			}
		}
		ant = aux;
	}
	free(aux);
	return listaCarrosAno;
}