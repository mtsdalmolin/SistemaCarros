typedef struct listaA
{
	struct carro* carro;
	struct listaA* prox;
} ListaA;

typedef struct arvano
{
	int ano;
	ListaA* listaCarrosAno;
	struct arvano* esq;
	struct arvano* dir;
} ArvAno;

ArvAno* criaArvAnoVazia();

bool ArvAnoVazia(ArvAno* arvoreAnos);

void imprimeArvAno(ArvAno* arvoreAnos);

ArvAno* insereArvAno(ArvAno* arvoreAnos, Carro* carroAlvo, int ano);

ArvAno* removeAno(ArvAno* arvoreAnos, int ano, char* placa);

ArvAno* buscaAno(ArvAno* arvoreAnos, int ano);

ArvAno* imprimeCarrosAno(ArvAno* arvoreAnos, ArvAno* anoAlvo);

ListaA* insereCarroAno(ListaA* listaCarrosAno, Carro* carroAlvo);

ListaA* excluiCarroAno(ListaA* listaCarrosAno, char* placa);