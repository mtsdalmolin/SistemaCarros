#include <stdio.h>
#include <stdbool.h>
#include "carro.h"
#include "arvoreplaca.h"
#include "arvoremarca.h"
#include "arvoreanos.h"
#include "menu.h"

int main()
{
	bool sair_menu = false;
	Carro* listaCarros = criaListaCarros();
	ArvPlaca* arvorePlacas = criaArvPlacaVazia();
	ArvMarca* arvoreMarcas = criaArvMarcaVazia();
	ArvAno* arvoreAnos = criaArvAnoVazia();

	do
	{
		menu(&listaCarros, &arvorePlacas, &arvoreMarcas, &arvoreAnos, &sair_menu);
	} while (!sair_menu);

	return 0;
}