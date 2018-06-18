#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "carro.h"

Carro* criaListaCarros()
{
	return NULL;
}

Carro* insereCarroLista(Carro* listaCarros, int ano, char* placa, char* marca)
{
	int retornoStrcmp;
	Carro* aux;
	Carro* ant = NULL;
	Carro* novoCarro = (Carro*) malloc(sizeof(Carro));
	novoCarro->ano = ano;
	strcpy(novoCarro->placa, placa);
	strcpy(novoCarro->marca, marca);
	if (listaCarros == NULL)
		novoCarro->prox = listaCarros;
	else
	{
		for (aux = listaCarros; aux != NULL; aux = aux->prox)
		{
			retornoStrcmp = strcmp(novoCarro->placa, aux->placa);
			if (retornoStrcmp < 0)
				break;
			ant = aux;
		}
		if (ant == NULL)
		{
			listaCarros = novoCarro;
			novoCarro->prox = aux;
		} else {
			ant->prox = novoCarro;
			novoCarro->prox = aux;
			return listaCarros;
		}
	}
	return novoCarro;
}

Carro* excluiCarroLista(Carro* listaCarros, char* placa)
{
	int retornoStrcmp;
	Carro* aux;
	Carro* ant = NULL;
	for (aux = listaCarros; aux != NULL; aux = aux->prox)
	{
		retornoStrcmp = strcmp(aux->placa, placa);
		if (!retornoStrcmp)
		{
			if (ant == NULL)
			{
				listaCarros = listaCarros->prox;
				break;
			} else {
				ant->prox = aux->prox;
				break;
			}
		}
		ant = aux;
	}
	printf("Carro da placa %s removido da lista!\n", aux->placa);
	free(aux);
	return listaCarros;
}

bool placaIgual(Carro* listaCarros, char* placa)
{
	Carro* aux;
	for (aux = listaCarros; aux != NULL; aux = aux->prox)
		if (!strcmp(aux->placa, placa))
			return true;
	return false;
}

void imprimeListaCarros(Carro* listaCarros)
{
	Carro* aux;
	for (aux = listaCarros; aux != NULL; aux = aux->prox)
		printf("----------CARRO----------\nAno: %d\nPlaca: %s\nMarca: %s\n", aux->ano, aux->placa, aux->marca);
}

Carro* buscaCarro(Carro* listaCarros, char* placa)
{
	int retornoStrcmp;
	Carro* aux;
	for (aux = listaCarros; aux != NULL; aux = aux->prox)
	{
		retornoStrcmp = strcmp(aux->placa, placa);
		if (!retornoStrcmp)
			return aux;
	}
	return NULL;
}