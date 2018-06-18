typedef struct lista
{
	struct carro* carro;
	struct lista* prox;
} Lista;

typedef struct arvmarca
{
	char marca[20];
	Lista* listaCarrosMarca;
	struct arvmarca* esq;
	struct arvmarca* dir;
} ArvMarca;

ArvMarca* criaArvMarcaVazia();

bool ArvMarcaVazia(ArvMarca* arvoreMarcas);

void imprimeArvMarca(ArvMarca* arvoreMarcas);

ArvMarca* insereArvMarca(ArvMarca* arvoreMarcas, Carro* carroAlvo, char* marca);

ArvMarca* removeMarca(ArvMarca* arvoreMarcas, char* marca, char* placa);

ArvMarca* buscaMarca(ArvMarca* arvoreMarcas, char* marca);

ArvMarca* imprimeCarrosMarca(ArvMarca* arvoreMarcas, ArvMarca* marcaAlvo);

Lista* insereCarroMarca(Lista* listaCarrosMarca, Carro* carroAlvo);

Lista* excluiCarroMarca(Lista* listaCarrosMarca, char* placa);