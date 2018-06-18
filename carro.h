typedef struct carro
{
	int ano;
	char placa[15];
	char marca[20];
	struct carro* prox;
} Carro;

Carro* criaListaCarros();

Carro* insereCarroLista(Carro* listaCarros, int ano, char* placa, char* marca);

Carro* excluiCarroLista(Carro* listaCarros, char* placa);

bool placaIgual(Carro* listaCarros, char* placa);

void imprimeListaCarros(Carro* listaCarros);

Carro* buscaCarro(Carro* listaCarros, char* placa);