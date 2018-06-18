#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "carro.h"
#include "arvoremarca.h"

ArvMarca* criaArvMarcaVazia()
{
	return NULL;
}

bool ArvMarcaVazia(ArvMarca* arvoreMarcas)
{
	return arvoreMarcas == NULL;
}

void imprimeArvMarca(ArvMarca* arvoreMarcas)
{
	if (!ArvMarcaVazia(arvoreMarcas))
	{
		imprimeArvMarca(arvoreMarcas->esq);
		printf("-----MARCA: %s-----\n",arvoreMarcas->marca);
		imprimeArvMarca(arvoreMarcas->dir);
	}
}

ArvMarca* insereArvMarca(ArvMarca* arvoreMarcas, Carro* carroAlvo, char* marca)
{
	int retornoStrcmp;
	if (ArvMarcaVazia(arvoreMarcas))
	{
		arvoreMarcas = (ArvMarca*) malloc(sizeof(ArvMarca));
		strcpy(arvoreMarcas->marca, marca);
		arvoreMarcas->esq = arvoreMarcas->dir = criaArvMarcaVazia();
		arvoreMarcas->listaCarrosMarca = insereCarroMarca(NULL, carroAlvo);
	} else {
		retornoStrcmp = strcmp(marca, arvoreMarcas->marca);
		if (retornoStrcmp < 0)
			arvoreMarcas->esq = insereArvMarca(arvoreMarcas->esq, carroAlvo, marca);
		else if (retornoStrcmp > 0)
			arvoreMarcas->dir = insereArvMarca(arvoreMarcas->dir, carroAlvo, marca);
		else
			arvoreMarcas->listaCarrosMarca = insereCarroMarca(arvoreMarcas->listaCarrosMarca, carroAlvo);
	}
	return arvoreMarcas;
}

ArvMarca* removeMarca(ArvMarca* arvoreMarcas, char* marca, char* placa)
{
	int marcaIgual;
	if(ArvMarcaVazia(arvoreMarcas))
		return NULL;
	marcaIgual = strcmp(arvoreMarcas->marca, marca);
	if (marcaIgual > 0)
		arvoreMarcas->esq = removeMarca(arvoreMarcas->esq, marca, placa);
	else if (marcaIgual < 0)
		arvoreMarcas->dir = removeMarca(arvoreMarcas->dir, marca, placa);
	else
	{
		arvoreMarcas->listaCarrosMarca = excluiCarroMarca(arvoreMarcas->listaCarrosMarca, placa);
		if (arvoreMarcas->listaCarrosMarca == NULL)
		{
			if (arvoreMarcas->esq == NULL && arvoreMarcas->dir == NULL)
			{
				free(arvoreMarcas);
				arvoreMarcas = NULL;
			} else if (arvoreMarcas->esq == NULL) {
				ArvMarca* aux = arvoreMarcas;
				arvoreMarcas = arvoreMarcas->dir;
				free(aux);
			} else if (arvoreMarcas->dir == NULL) {
				ArvMarca* aux = arvoreMarcas;
				arvoreMarcas = arvoreMarcas->esq;
				free(aux);
			} else {
				ArvMarca* aux = arvoreMarcas->esq;
				while (aux->dir != NULL)
					aux = aux->dir;
				strcpy(arvoreMarcas->marca, aux->marca);
				strcpy(aux->marca, marca);
				arvoreMarcas->esq = removeMarca(arvoreMarcas->esq, marca, placa);
			}
		}
	}
	return arvoreMarcas;
}

ArvMarca* buscaMarca(ArvMarca* arvoreMarcas, char* marca)
{
	int retornoStrcmp;
	if (ArvMarcaVazia(arvoreMarcas))
		return NULL;
	retornoStrcmp = strcmp(arvoreMarcas->marca, marca);
	if (retornoStrcmp < 0)
		arvoreMarcas = buscaMarca(arvoreMarcas->dir, marca);
	else if (retornoStrcmp > 0)
		arvoreMarcas = buscaMarca(arvoreMarcas->esq, marca);
	return arvoreMarcas;
}

ArvMarca* imprimeCarrosMarca(ArvMarca* arvoreMarcas, ArvMarca* marcaAlvo)
{
	int retornoStrcmp;
	Lista* aux;
	if (ArvMarcaVazia(arvoreMarcas))
		return NULL;
	else
	{
		imprimeCarrosMarca(arvoreMarcas->esq, marcaAlvo);
		for (aux = arvoreMarcas->listaCarrosMarca; aux != NULL; aux = aux->prox)
		{
			retornoStrcmp = strcmp(marcaAlvo->marca, aux->carro->marca);
			if (!retornoStrcmp)
			printf("------CARRO------\nAno: %d\nPlaca: %s\nMarca: %s\n", aux->carro->ano, aux->carro->placa, aux->carro->marca);
		}
		imprimeCarrosMarca(arvoreMarcas->dir, marcaAlvo);
	}
	return arvoreMarcas;
}

Lista* insereCarroMarca(Lista* listaCarrosMarca, Carro* carroAlvo)
{
	Lista* novoCarro = (Lista*) malloc(sizeof(Lista));
	novoCarro->carro = carroAlvo;
	novoCarro->prox = listaCarrosMarca;
	return novoCarro;
}

Lista* excluiCarroMarca(Lista* listaCarrosMarca, char* placa)
{
	int placaDiferente;
	Lista* aux;
	Lista* ant = NULL;
	for (aux = listaCarrosMarca; aux != NULL; aux = aux->prox)
	{
		placaDiferente = strcmp(aux->carro->placa, placa);
		if (!placaDiferente) //placa é igual
		{
			if (ant == NULL)
			{ // remover primeiro elemento
				listaCarrosMarca = listaCarrosMarca->prox;
				break;
			} else { // meio da lista... ou fim
				ant->prox = aux->prox;
				break;
			}
		}
		ant = aux;
	}
	free(aux);
	return listaCarrosMarca;
}