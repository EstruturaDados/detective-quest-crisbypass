#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
// Se estivermos no windows, vamos incluir usar uma saída de console com padrão adequado para utf-8.
#ifdef _WIN32
#include <Windows.h>
#endif

// Desafio Detective Quest
// Tema 4 - Árvores e Tabela Hash
// Este código inicial serve como base para o desenvolvimento das estruturas de navegação, pistas e suspeitos.
// Use as instruções de cada região para desenvolver o sistema completo com árvore binária, árvore de busca e tabela hash.
	
// **** Definições de estruturas. ****

/// @brief Define a struct para representar a pista. Contém um campo com um texto descritivo.
struct Pista
{
	char pista[50];
	struct Pista* esquerda;
	struct Pista* direita;
};

/// @brief Define uma struct com um alias Pista, para uso em uma estratégia BST.
typedef struct Pista Pista;

/// @brief Define um tipo personalizado(Sala) com campos para nome e ponteiros(esquerda e direita).
struct Sala
{
	char pista[50];
	char nome[50];
	struct Sala* esquerda;
	struct Sala* direita;
};

/// @brief Define a struct com um alias Sala, para uso em uma estratégia BST.
typedef struct Sala Sala;

/// @brief Define uma enumeração(alias SeguirNaDirecao), usada na navegação de salas.
typedef enum
{
	SeguirNaDirecao_NENHUM = 0,
	SeguirNaDirecao_ESQUERDA = 1,
	SeguirNaDirecao_DIREITA = 2,
} SeguirNaDirecao;


// **** Declarações das funções. ****

// **** Funções de Interface de Usuário ****

/// @brief Exibe o menu principal.
/// @param Inteiro. Ponteiro via referência, para conter o valor da opção escolhida.
void exibirMenuPrincipal(int* opcao);
/// @brief Exibe e monitora o estado atual resultante da investigação,
/// em função nó atualmente visitado(Sala).
/// @param Sala. Ponteiro para recuperação de informações. Somente leitura.
void exibirEstadoInvestigacao(const Sala* noLocal);

// **** Funções de Lógica Principal e Gerenciamento de Memória ****

/// @brief Cria um ponteiro para referência ao nó(Sala) raiz principal.
/// @returns Sala. Ponteiro do tipo conforme especificado.
Sala* criarMansao();
/// @brief Cria os nós de forma manual, usando um ponteiro via
/// referência ao nó(Sala) raiz principal.
void criarSalas(Sala* mansao);
/// @brief Explora os nós de forma hierárquica, simulando uma navegação.
/// @param Enumeração. Valor descrevendo a direção a seguir na navegação.
/// @param Sala. Ponteiro via referência, usado para exploração das salas.
/// @param Sala. Ponteiro via referência, usado para valor padrão, em caso de recuo na navegação.
/// @param Pista. Ponteiro via referência, usado para leitura e atribuição no processo de navegação.
/// @returns Sala. Ponteiro do tipo conforme especificado.
Sala* explorarSalasComPistas(SeguirNaDirecao direcao, Sala* atual, Sala* mansao, Pista** pista);
/// @brief Cria um ponteiro para um nó, tipo Sala.
/// Baseado no conteúdo da plataforma.
/// @param Texto. Valor descrevendo o nome da Sala.
/// @returns Sala. Ponteiro do tipo conforme especificado.
Sala* criarSala(const char* nome, const char* pista);
/// @brief Efetua uma inserção na árvore para BST, tipo Sala.
/// Baseado no conteúdo da plataforma.
/// @param Sala. Ponteiro via referência, usado na inserção.
/// @param Texto. Valor descrevendo o nome da Sala.
/// @returns Sala. Ponteiro do tipo conforme especificado.
Sala* inserirSala(Sala* raiz, const char* nome);
/// @brief Cria um ponteiro para um nó, tipo Pista.
/// Baseado no conteúdo da plataforma.
/// @param Texto. Valor descrevendo a pista.
/// @returns Sala. Ponteiro do tipo conforme especificado.
Pista* criarPista(const char* pista);
/// @brief Efetua uma inserção na árvore para BST, tipo Pista.
/// Baseado no conteúdo da plataforma.
/// @param Sala. Ponteiro via referência, usado na inserção.
/// @param Texto. Valor descrevendo a pista.
/// @returns Pista. Ponteiro do tipo conforme especificado.
Pista* inserirPista(Pista* raiz, const char* pista);
/// @brief Efetua a exibição de informações sobre as pistas.
/// @param Pista. Ponteiro via referência, usado na recuperação de informações. Somente leitura.
/// @returns Pista. Ponteiro do tipo conforme especificado.
void exibirPistas(const Pista* pista);
/// @brief Recupera informações sobre a altura de uma árvore(composição hierárquica).
/// Baseado no conteúdo da plataforma.
/// @param Sala. Ponteiro usado na recuperação de informações. Somente leitura.
/// @returns Inteiro. Valor informando a altura, conforme especificado.
int altura(const Sala* raiz);
/// @brief Recupera informações sobre a profundidade(a nível recursivo) 
/// de uma árvore(composição hierárquica). Baseado no conteúdo da plataforma.
/// @param Sala. Ponteiro raiz usado na recuperação de informações. Somente leitura.
/// @param Sala. Ponteiro alvo a ser usado como para consulta de profundidade. Somente leitura.
/// @param Inteiro. Valor representando o nível máximo de chamadas recursivas permitidas.
/// @returns Inteiro. Valor informando a profundidade, conforme especificado.
int profundidade(const Sala* raiz, const Sala* alvo, int nivel);
/// @brief Efetua a pré-ordenação de um nó e seus descendentes. Baseado no conteúdo da plataforma.
/// @param Sala. Ponteiro raiz, via referência, usado na operação de pré-ordenação.
void preOrdem(const Sala* raiz);
/// @brief Efetua a ordenação de um nó e seus descendentes. Baseado no conteúdo da plataforma.
/// @param Sala. Ponteiro raiz, via referência, usado na operação de ordenação.
void emOrdem(const Sala* raiz);
/// @brief Efetua a ordenação de um nó e seus descendentes. Baseado no conteúdo da plataforma.
/// @param Sala. Ponteiro raiz, via referência, usado na operação de ordenação. Somente leitura.
void exibirPistasEmOrdem(const Pista* raiz);
/// @brief Efetua a pós-ordenação de um nó e seus descendentes.
/// Baseado no conteúdo da plataforma.
/// @param Sala. Ponteiro raiz, via referência, usado na operação de pós-ordenação.
void posOrdem(const Sala* raiz);
/// @brief Libera a memória alocada para um nó e seus descendentes, usando chamadas recursivas.
/// Baseado no conteúdo da plataforma.
/// @param Sala. Ponteiro raiz, via referência, usado na operação de liberação.
void liberarSala(Sala* raiz);
/// @brief Libera a memória alocada para um nó e seus descendentes, usando chamadas recursivas.
/// Baseado no conteúdo da plataforma.
/// @param Pista. Ponteiro raiz, via referência, usado na operação de liberação.
void liberarPista(Pista* raiz);
/// @brief Libera a memória alocada para um nó e seus descendentes.
/// @param Sala. Ponteiro raiz, via referência, usado na operação de liberação.
/// @param Pista. Ponteiro raiz, via referência, usado na operação de liberação.
void liberarMemoria(Sala* raiz, Pista* pista);

// **** Funções utilitárias ****

/// @brief Limpa o buffer de entrada do teclado (stdin), evitando problemas 
/// com leituras consecutivas de scanf e getchar.
void limparBufferEntrada();
/// @brief Função para limpar '\n' deixado pelo fgets.
/// @param str Conteúdo do texto a ser analisado e limpo.
void limparEnter(char* str);

/// @brief Ponto de entrada do programa.
/// @returns Inteiro. Zero, em caso de sucesso. Ex: EXIT_SUCCESS. 
/// Ou diferente de Zero, em caso de falha. Ex: EXIT_FAILURE.
int main() {

	// 🔍 Nível Aventureiro: Armazenamento de Pistas com Árvore de Busca
	//
	// - Crie uma struct Pista com campo texto (string).
	// - Crie uma árvore binária de busca (BST) para inserir as pistas coletadas.
	// - Ao visitar salas específicas, adicione pistas automaticamente com inserirBST().
	// - Implemente uma função para exibir as pistas em ordem alfabética (emOrdem()).
	// - Utilize alocação dinâmica e comparação de strings (strcmp) para organizar.
	// - Não precisa remover ou balancear a árvore.
	// - Use funções para modularizar: inserirPista(), listarPistas().
	// - A árvore de pistas deve ser exibida quando o jogador quiser revisar evidências.	

	// Configurações de caracteres para ajuste de ortografia para saída do console(UTF-8).
#ifdef _WIN32
	// Plataforma Windows.
	SetConsoleOutputCP(CP_UTF8);
#endif

	printf("======================================================\n");
	printf("==== 🔎  DETECTIVE QUEST - Nível Aventureiro  🔍 ====\n");
	printf("======================================================\n");

	int opcao = 0;

	Sala* mansao = criarMansao();

	criarSalas(mansao);

	Sala* atual = mansao; // Definindo o valor padrão inicial para a navegação.

	Pista* pista = NULL; // Preparando um ponteiro para conter uma referência para os nós das pistas.

	do
	{
		exibirEstadoInvestigacao(atual);

		exibirMenuPrincipal(&opcao);

		switch (opcao)
		{
		case 1:
			// Ir para a esquerda.
			atual = explorarSalasComPistas(SeguirNaDirecao_ESQUERDA, atual, mansao, &pista);
			break;
		case 2:
			// Ir para a direita.
			atual = explorarSalasComPistas(SeguirNaDirecao_DIREITA, atual, mansao, &pista);
			break;
		case 0:
			exibirPistas(pista);
			//  0  Sair.
			printf("\n==== Saindo do sistema... ====\n");
			break;
		default:
			// Continua.
			printf("\n==== ⚠️  Opção inválida. ====\n");
			break;
		}

	} while (opcao != 0);


	liberarMemoria(mansao, pista);

	printf("\n==== Operação encerrada. ====\n");


	return EXIT_SUCCESS;
}

// **** Implementação das funções. ****

// **** Funções de Interface de Usuário ****

void exibirMenuPrincipal(int* opcao)
{
	printf("\nE(ou e) - Ir para a Esquerda ↩️ \n");
	printf("D(ou d) - Ir para a Direita ↪️ \n");
	printf("S(ou s) - Sair.\n");

	bool invalido;

	char escolhido;

	do
	{
		printf("Escolha uma opção: ");
		escolhido = getchar();
		limparBufferEntrada();
		invalido = escolhido != 'e' && escolhido != 'E' &&
			escolhido != 'd' && escolhido != 'D' &&
			escolhido != 's' && escolhido != 'S';

		if (invalido)
		{
			printf("\n==== ⚠️  Entrada inválida. Esperado: E(ou e), D(ou d) ou S(ou s). ====\n");
		}
	} while (invalido);


	switch (escolhido)
	{
	case 'e':
	case 'E':
		*opcao = 1;
		break;
	case 'd':
	case 'D':
		*opcao = 2;
		break;
	case 's':
	case 'S':
		*opcao = 0;
		break;
	default:
		*opcao = -1;
		break;
	}
}

void exibirEstadoInvestigacao(const Sala* noLocal)
{
	if (noLocal == NULL)
	{
		printf("\n ====  🚫  Nada existe além do local atual.  🚩 ==== \n");
		printf("\n  ℹ️  Vamos voltar ao ponto de partida.\n");
		return;
	}

	printf("\n ====  ℹ️  No momento, você se encontra neste local: %s  🚩 ==== \n", noLocal->nome);
}

// **** Funções de Lógica Principal e Gerenciamento de Memória ****

Sala* criarMansao()
{
	return criarSala("Hall de Entrada", "O sistema de alarme não foi acionado.");
}

void criarSalas(Sala* mansao)
{
	// Criação de nós de forma explícita(manual), procurando seguir uma ordem para a 
	// otimização por busca alfabética do algoritmo. Por exemplo, o BST(Binary Search Tree),
	// usando o conteúdo do texto. Mas ainda assim, ao menos conseguimos simular uma hierarquia
	// baseada no posicionamento para a navegação de nós do nosso desafio atual.

	mansao->esquerda = criarSala("Area Reservada", "Há uma cápsula de projétil no chão.");
	mansao->direita = criarSala("Sala de Estar", "Têm um vaso quebrado com algo dentro.");

	mansao->esquerda->esquerda = criarSala("Escadaria", "Há um colar despedaçado.");
	mansao->esquerda->direita = criarSala("O Corredor", "Têm uma mancha de sangue.");

	mansao->esquerda->esquerda->esquerda = criarSala("A Suíte", "Há uma maçaneta quebrada.");
	mansao->esquerda->esquerda->direita = criarSala("Hidro", "Têm problemas elétricos.");

	mansao->esquerda->direita->esquerda = criarSala("Biblioteca", "Há livros jogados pelo chão.");
	mansao->esquerda->direita->direita = criarSala("Escritório", "A janela está quebrada.");

	mansao->direita->esquerda = criarSala("A Sala de Jantar", "O café ainda está quente no copo.");
	mansao->direita->direita = criarSala("O Gazebo", "Os assentos estão bagunçados.");

	mansao->direita->esquerda->esquerda = criarSala("A Cozinha", "Alguém deixou algo os aparelhos ligados.");
	mansao->direita->esquerda->direita = criarSala("Despensa", "Está aberta e desorganizada.");

	mansao->direita->direita->esquerda = criarSala("A Piscina", "Está parcialmente coberta.");
	mansao->direita->direita->direita = criarSala("Quadra", "A iluminação está parcial.");
}

Sala* explorarSalasComPistas(SeguirNaDirecao direcao, Sala* atual, Sala* mansao, Pista** pista)
{
	if (atual == NULL)
	{
		return NULL;
	}

	if (atual != NULL && atual->pista != NULL)
	{
		*pista = inserirPista(*pista, atual->pista);		
	}

	// Caso o ponto de navegação atual resulte em um nó folha, vamos voltar
	// automaticamente à referência mais alta. Neste nível de desafio, é indefinido
	// em que momento a investigação deveria terminar, até o jogador decidir sair.
	switch (direcao)
	{
	case SeguirNaDirecao_ESQUERDA:		

		if (atual->esquerda == NULL)
		{
			exibirEstadoInvestigacao(atual->esquerda);
			return mansao;
		}

		return atual->esquerda;

	case SeguirNaDirecao_DIREITA:

		if (atual->direita == NULL)
		{
			exibirEstadoInvestigacao(atual->direita);
			return mansao;
		}		

		return atual->direita;

	default:
		return NULL;
	}
}

Sala* criarSala(const char* nome, const char* pista)
{
	Sala* novo = (Sala*)malloc(sizeof(Sala));
	if (novo == NULL)
	{
		printf("\n  ❌  Erro ao tentar alocar a memória para o novo nó.\n");
		return NULL;
	}

	strcpy(novo->nome, nome);
	strcpy(novo->pista, pista);
	novo->esquerda = NULL;
	novo->direita = NULL;

	return novo;
}

Pista* criarPista(const char* pista)
{
	Pista* novo = (Pista*)malloc(sizeof(Pista));
	if (novo == NULL)
	{
		printf("\n  ❌  Erro ao tentar alocar a memória para o novo nó.\n");
		return NULL;
	}

	strcpy(novo->pista, pista);
	novo->esquerda = NULL;
	novo->direita = NULL;

	return novo;
}

Sala* inserirSala(Sala* raiz, const char* nome)
{
	// Se o nó atual ainda não existe(portanto, não possui nós filhos), então será criado.
	if (raiz == NULL)
	{
		return criarSala(nome, nome);
	}
	// Verificamos se o nome correspondente é um valor menor que o atual atual.
	// Feito isso, atribui o nó de menor valor à esquerda.
	if (strcmp(nome, raiz->nome) < 0)
	{
		raiz->esquerda = inserirSala(raiz->esquerda, nome);
	}
	else if (strcmp(nome, raiz->nome) > 0)
	{
		// Caso contrário, atribui o nó à direita.
		raiz->direita = inserirSala(raiz->direita, nome);
	}

	return raiz;
}

Pista* inserirPista(Pista* raiz, const char* pista)
{
	// Se o nó atual ainda não existe(portanto, não possui nós filhos), então será criado.
	if (raiz == NULL)
	{
		return criarPista(pista);
	}
	// Verificamos se o nome correspondente é um valor menor que o atual atual.
	// Feito isso, atribui o nó de menor valor à esquerda.
	if (strcmp(pista, raiz->pista) < 0)
	{
		raiz->esquerda = inserirPista(raiz->esquerda, pista);
	}
	else if (strcmp(pista, raiz->pista) > 0)
	{
		// Caso contrário, se o valor é maior, atribui o nó à direita.
		raiz->direita = inserirPista(raiz->direita, pista);
	}

	return raiz;
}

int altura(const Sala* raiz)
{
	if (raiz == NULL)
	{
		return 0;
	}

	int alt_esq = altura(raiz->esquerda);
	int alt_dir = altura(raiz->direita);
	return 1 + (alt_esq > alt_dir ? alt_esq : alt_dir);
}

int profundidade(const Sala* raiz, const Sala* alvo, int nivel)
{
	if (raiz == NULL)
	{
		return -1;
	}

	if (raiz == alvo)
	{
		return nivel;
	}

	int esq = profundidade(raiz->esquerda, alvo, nivel + 1);

	if (esq != -1)
	{
		return esq;
	}

	return profundidade(raiz->direita, alvo, nivel + 1);
}

void preOrdem(const Sala* raiz)
{
	if (raiz != NULL)
	{
		printf(" • %s\n", raiz->nome);
		preOrdem(raiz->esquerda);
		preOrdem(raiz->direita);
	}
}

void emOrdem(const Sala* raiz)
{
	if (raiz != NULL)
	{
		emOrdem(raiz->esquerda);
		printf(" • %s\n", raiz->nome);
		emOrdem(raiz->direita);
	}
}

void exibirPistasEmOrdem(const Pista* raiz)
{
	if (raiz == NULL)
	{
		return;
	}
	exibirPistasEmOrdem(raiz->esquerda);
	printf("\n • %s\n", raiz->pista);
	exibirPistasEmOrdem(raiz->direita);
}

void exibirPistas(const Pista* pista) 
{
	printf("\n  ℹ️  Descrição das pistas encontradas até o momento:\n");

	exibirPistasEmOrdem(pista);
}

void posOrdem(const Sala* raiz)
{
	if (raiz != NULL)
	{
		posOrdem(raiz->esquerda);
		posOrdem(raiz->direita);
		printf(" • %s\n", raiz->nome);
	}
}

void liberarSala(Sala* raiz)
{
	if (raiz != NULL)
	{
		liberarSala(raiz->esquerda);
		liberarSala(raiz->direita);
		free(raiz);
	}
}

void liberarPista(Pista* raiz)
{
	if (raiz != NULL)
	{
		liberarPista(raiz->esquerda);
		liberarPista(raiz->direita);
		free(raiz);
	}
}

void liberarMemoria(Sala* raiz, Pista* pista)
{
	liberarSala(raiz);
	liberarPista(pista);

	printf("\n  ✅  Memória alocada para os nós liberada com sucesso.\n");
}

// **** Funções utilitárias ****

void limparBufferEntrada()
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

void limparEnter(char* str)
{
	str[strcspn(str, "\n")] = '\0';
}