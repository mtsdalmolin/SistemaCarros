#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "carro.h"
#include "arvoreplaca.h"
#include "arvoremarca.h"
#include "arvoreanos.h"

void menu(Carro** listaCarros, ArvPlaca** arvorePlacas, ArvMarca** arvoreMarcas, ArvAno** arvoreAnos, bool* sair_menu)
{
	int selecao;
	int ano;
	char placa[15];
	char marca[20];
	bool verificaPlaca;
	Carro* carroAlvo;
	ArvPlaca* placaAlvo = NULL;
	ArvMarca* marcaAlvo = NULL;
	ArvAno* anoAlvo = NULL;
	printf("------MENU PRINCIPAL------\n");
	printf("[1] INSERIR CARRO\n[2] EXCLUIR CARRO\n[3] BUSCAR CARRO POR PLACA\n[4] BUSCAR CARRO POR MARCA\n[5] BUSCAR CARRO POR ANO\n[6] IMPRIMIR LISTA DE CARROS\n[7] IMPRIMIR ARVORE DE MARCAS\n[8] IMPRIMIR ARVORE DE ANOS\n[9] SAIR\n");
	scanf("%d", &selecao);
	switch (selecao)
	{
		case 1:
			printf("Inserindo um carro na lista.\nAno do carro:");
			scanf("%d", &ano);
			do
			{
				printf("Informe a placa do carro:\n");
				scanf("%s", placa);
				if (*listaCarros == NULL)
					verificaPlaca = false;
				else
				{
					verificaPlaca = placaIgual(*listaCarros, placa);
					if (verificaPlaca)
						printf("PLACA JA INSERIDA NA LISTA! INSIRA OUTRA PLACA PARA O CARRO!\n");
				}
			} while (verificaPlaca);
			printf("Informe a marca do carro:\n");
			scanf("%s", marca);
			*listaCarros = insereCarroLista(*listaCarros, ano, placa, marca);
			carroAlvo = buscaCarro(*listaCarros, placa);
			*arvorePlacas = insereArvPlaca(*arvorePlacas, carroAlvo, placa);
			*arvoreMarcas = insereArvMarca(*arvoreMarcas, carroAlvo, marca);
			*arvoreAnos = insereArvAno(*arvoreAnos, carroAlvo, ano);
			break;
		case 2:
			printf("Informe a placa do carro que deseja excluir da lista.\n");
			scanf("%s", placa);
			placaAlvo = buscaPlaca(*arvorePlacas, placa);
			if (placaAlvo == NULL)
				printf("PLACA NAO ENCONTRADA!!!\n");
			else
			{
				strcpy(marca, placaAlvo->carro->marca);
				*arvoreMarcas = removeMarca(*arvoreMarcas, marca, placa);
				ano = placaAlvo->carro->ano;
				*arvoreAnos = removeAno(*arvoreAnos, ano, placa);
				*arvorePlacas = removePlaca(*arvorePlacas, placa);
				*listaCarros = excluiCarroLista(*listaCarros, placa);
			}
			break;
		case 3:
			printf("Informe a placa que deseja buscar.\n");
			scanf("%s", placa);
			placaAlvo = buscaPlaca(*arvorePlacas, placa);
			if (placaAlvo == NULL)
				printf("PLACA NAO ENCONTRADA!!!\n");
			else
				printf("-----CARRO-----\nAno: %d\nPlaca: %s\nMarca: %s\n", placaAlvo->carro->ano, placaAlvo->carro->placa, placaAlvo->carro->marca);
			break;
		case 4:
			printf("Informe a marca do carro para listar os carros da marca.\n");
			scanf("%s", marca);
			marcaAlvo = buscaMarca(*arvoreMarcas, marca);
			if (marcaAlvo == NULL)
				printf("MARCA NAO ENCONTRADA!!!\n");
			else
				*arvoreMarcas = imprimeCarrosMarca(*arvoreMarcas, marcaAlvo);
			break;
		case 5:
			printf("Informe o ano do carro para listar os carros do ano.\n");
			scanf("%d", &ano);
			anoAlvo = buscaAno(*arvoreAnos, ano);
			if (anoAlvo == NULL)
				printf("ANO NAO ENCONTRADO!!!\n");
			else
				*arvoreAnos = imprimeCarrosAno(*arvoreAnos, anoAlvo);
			break;
		case 6:
			printf("------LISTA DE CARROS------\n");
			if (*listaCarros == NULL)
				printf("LISTA DE CARROS VAZIA!!!\n");
			else
				imprimeListaCarros(*listaCarros);
			break;
		case 7:
			printf("------ARVORE DE MARCAS------\n");
			if (*arvoreMarcas == NULL)
				printf("ARVORE DE MARCAS VAZIA!!!\n");
			else
				imprimeArvMarca(*arvoreMarcas);
			break;
		case 8:
			printf("------ARVORE DE ANOS------\n");
			if (*arvoreAnos == NULL)
				printf("ARVORE DE ANOS VAZIA!!!\n");
			else
				imprimeArvAno(*arvoreAnos);
			break;
		case 9:
			*sair_menu = true;
			break;
		default: printf("ENTRADA INVALIDA!!!\n");
	}
}