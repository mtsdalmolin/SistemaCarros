typedef struct arvplaca
{
	char placa[15];
	struct carro* carro;
	struct arvplaca* esq;
	struct arvplaca* dir;
} ArvPlaca;

ArvPlaca* criaArvPlacaVazia();

bool ArvPlacaVazia(ArvPlaca* arvorePlacas);

void imprimeArvPlaca(ArvPlaca* arvorePlacas);

ArvPlaca* insereArvPlaca(ArvPlaca* arvorePlacas, Carro* carroAlvo, char* placa);

ArvPlaca* removePlaca(ArvPlaca* arvorePlacas, char* placa);

ArvPlaca* buscaPlaca(ArvPlaca* arvorePlacas, char* placa);