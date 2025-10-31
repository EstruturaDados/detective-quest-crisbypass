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

/// @brief Define um tipo personalizado(Sala) com campos para nome e ponteiros(esquerda e direita).
struct Sala
{
	char nome[50];
	struct Sala* esquerda;
	struct Sala* direita;
};

/// @brief Define uma struct com um alias Sala.
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
/// @brief Cria os nós de forma manual, usando um ponteiro via referência ao nó(Sala) raiz principal.
void criarSalas(Sala* mansao);
/// @brief Explora os nós de forma hierárquica, simulando uma navegação.
/// @param Enumeração. Valor descrevendo a direção a seguir na navegação.
/// @param Sala. Ponteiro, usado para exploração das salas.
/// @returns Sala. Ponteiro do tipo conforme especificado.
Sala* explorarSalas(SeguirNaDirecao direcao, Sala* atual);
/// @brief Cria um ponteiro para um nó, tipo Sala. Baseado no conteúdo da plataforma.
/// @param Texto. Valor descrevendo o nome da Sala.
/// @returns Sala. Ponteiro do tipo conforme especificado.
Sala* criarSala(const char* nome);
/// @brief Cria um ponteiro para um nó, tipo Sala. Baseado no conteúdo da plataforma.
/// @param Texto. Valor descrevendo o nome da Sala.
/// @returns Sala. Ponteiro do tipo conforme especificado.
Sala* inserirSala(Sala* raiz, const char* nome);
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
/// @brief Efetua a ordenação de um nó e seus descendentes.
/// Baseado no conteúdo da plataforma.
/// @param Sala. Ponteiro raiz, via referência, usado na operação de ordenação.
void emOrdem(const Sala* raiz);
/// @brief Efetua a pós-ordenação de um nó e seus descendentes.
/// Baseado no conteúdo da plataforma.
/// @param Sala. Ponteiro raiz, via referência, usado na operação de pós-ordenação.
void posOrdem(const Sala* raiz);
/// @brief Libera a memória alocada para um nó e seus descendentes, usando chamadas recursivas.
/// Baseado no conteúdo da plataforma.
/// @param Sala. Ponteiro raiz, via referência, usado na operação de liberação.
void liberarSala(Sala* raiz);
/// @brief Libera a memória alocada para um nó e seus descendentes.
/// @param Sala. Ponteiro raiz, via referência, usado na operação de liberação.
void liberarMemoria(Sala* raiz);

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

	// 🌱 Nível Novato: Mapa da Mansão com Árvore Binária
	//
	// - Crie uma struct Sala com nome, e dois ponteiros: esquerda e direita.
	// - Use funções como criarSala(), conectarSalas() e explorarSalas().
	// - A árvore pode ser fixa: Hall de Entrada, Biblioteca, Cozinha, Sótão etc.
	// - O jogador deve poder explorar indo à esquerda (e) ou à direita (d).
	// - Finalize a exploração com uma opção de saída (s).
	// - Exiba o nome da sala a cada movimento.
	// - Use recursão ou laços para caminhar pela árvore.
	// - Nenhuma inserção dinâmica é necessária neste nível.	

	// Configurações de caracteres para ajuste de ortografia para saída do console(UTF-8).
#ifdef _WIN32
	// Plataforma Windows.
	SetConsoleOutputCP(CP_UTF8);
#endif

	printf("======================================================\n");
	printf("====== 🔎  DETECTIVE QUEST - Nível Novato  🔍 =======\n");
	printf("======================================================\n");

	int opcao = 0;

	Sala* mansao = criarMansao();

	criarSalas(mansao);

	Sala* atual = mansao;

	do
	{
		exibirEstadoInvestigacao(atual);

		if (atual == NULL)
		{
			break; // Neste nível de desafio, podemos parar por aqui, caso alcancemos o nó folha.
		}

		exibirMenuPrincipal(&opcao);

		switch (opcao)
		{
		case 1:
			// Ir para a esquerda.
			atual = explorarSalas(SeguirNaDirecao_ESQUERDA, atual);
			break;
		case 2:
			// Ir para a direita.
			atual = explorarSalas(SeguirNaDirecao_DIREITA, atual);
			break;
		case 0:
			//  0  Sair.
			printf("\n==== Saindo do sistema... ====\n");
			break;
		default:
			// Continua.
			printf("\n==== ⚠️  Opção inválida. ====\n");
			break;
		}

	} while (opcao != 0);


	liberarMemoria(mansao);

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
		printf("\n  ℹ️  A exploração terminou.\n");
		return;
	}

	printf("\n ====  ℹ️  No momento, você se encontra neste local: %s  🚩 ==== \n", noLocal->nome);
}

// **** Funções de Lógica Principal e Gerenciamento de Memória ****

Sala* criarMansao()
{
	return criarSala("Hall de Entrada");
}

void criarSalas(Sala* mansao)
{	
	// Criação de nós de forma explícita(manual), procurando seguir uma ordem para a 
	// otimização por busca alfabética do algoritmo. Por exemplo, o BST(Binary Search Tree),
	// usando o conteúdo do texto. Mas ainda assim, ao menos conseguimos simular uma hierarquia
	// baseada no posicionamento para a navegação de nós do nosso desafio atual.

	mansao->esquerda = criarSala("Area Reservada");
	mansao->direita = criarSala("Sala de Estar");

	mansao->esquerda->esquerda = criarSala("Escadaria");
	mansao->esquerda->direita = criarSala("O Corredor");

	mansao->esquerda->esquerda->esquerda = criarSala("A Suíte");
	mansao->esquerda->esquerda->direita = criarSala("Hidro");

	mansao->esquerda->direita->esquerda = criarSala("Biblioteca");
	mansao->esquerda->direita->direita = criarSala("Escritório");

	mansao->direita->esquerda = criarSala("A Sala de Jantar");
	mansao->direita->direita = criarSala("O Gazebo");

	mansao->direita->esquerda->esquerda = criarSala("A Cozinha");
	mansao->direita->esquerda->direita = criarSala("Despensa");

	mansao->direita->direita->esquerda = criarSala("A Piscina");
	mansao->direita->direita->direita = criarSala("Quadra");
}

Sala* explorarSalas(SeguirNaDirecao direcao, Sala* atual)
{
	if (atual == NULL)
	{		
		return NULL;
	}
	switch (direcao)
	{
	case SeguirNaDirecao_ESQUERDA:
		return atual->esquerda;		
	case SeguirNaDirecao_DIREITA:		
		return atual->direita;		
	default:
		return NULL;		
	}
}

Sala* criarSala(const char* nome)
{
	Sala* novo = (Sala*)malloc(sizeof(Sala));
	if (novo == NULL)
	{
		printf("\n  ❌  Erro ao tentar alocar a memória para o novo nó.\n");
		return NULL;
	}

	strcpy(novo->nome, nome);
	novo->esquerda = NULL;
	novo->direita = NULL;

	return novo;
}

Sala* inserirSala(Sala* raiz, const char* nome)
{
	// Se o nó atual ainda não existe(portanto, não possui nós filhos), então será criado.
	if (raiz == NULL)
	{
		return criarSala(nome);
	}
	// Verificamos se o nome correspondente é diferente do atual. Feito isso, atribui o nó.
	if (strcmp(nome, raiz->nome) < 0)
	{
		raiz->esquerda = inserirSala(raiz->esquerda, nome);		
	}
	else if(strcmp(nome, raiz->nome) > 0)
	{
		// Caso contrário, atribui o nó à direita.
		raiz->direita = inserirSala(raiz->direita, nome);
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
		printf(" %s |", raiz->nome);
		preOrdem(raiz->esquerda);
		preOrdem(raiz->direita);
	}
}

void emOrdem(const Sala* raiz)
{
	if (raiz != NULL)
	{
		emOrdem(raiz->esquerda);
		printf(" %s |", raiz->nome);
		emOrdem(raiz->direita);
	}
}

void posOrdem(const Sala* raiz)
{
	if (raiz != NULL)
	{
		posOrdem(raiz->esquerda);
		posOrdem(raiz->direita);
		printf(" %s |", raiz->nome);
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

void liberarMemoria(Sala* raiz)
{
	liberarSala(raiz);

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