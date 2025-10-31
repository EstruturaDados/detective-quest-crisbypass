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

// **** Definições de constantes. ****

/// @brief Define o tamanho máximo do número de itens a integrarem a tabela hash.
#define TAMANHO_TABELA_HASH 10
/// @brief Define o tamanho máximo do número de itens a integrarem a tabela hash.
#define TAMANHO_MAX_NOME 50
/// @brief Define o tamanho máximo para o texto descritivo da pista.
#define TAMANHO_MAX_PISTA 80
/// @brief Define o número mínimo requerido de pistas para acusar um suspeito.
#define NUMERO_PISTAS_REQUERIDAS 2

// **** Definições de estruturas. ****

/// @brief Define a struct para representar a pista. Contém um campo com um texto descritivo.
struct Pista
{
	char pista[TAMANHO_MAX_PISTA];
	struct Pista* esquerda;
	struct Pista* direita;
};

/// @brief Define uma struct com um alias Pista, para uso em uma estratégia BST.
typedef struct Pista Pista;

/// @brief Define um tipo personalizado(Sala) com campos para nome e ponteiros(esquerda e direita).
struct Sala
{
	char pista[TAMANHO_MAX_PISTA];
	char nome[TAMANHO_MAX_NOME];
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

/// @brief Define uma enumeração(alias SeguirNaDirecao), usada na navegação de salas.
struct NoHash
{
	char pista[TAMANHO_MAX_PISTA];
	char suspeito[TAMANHO_MAX_NOME];
	struct NoHash* proximo;
};

/// @brief Define a struct com alias NoHash, usado na tabela hash.
typedef struct NoHash NoHash;

/// @brief Define uma tabela hash, usada na associação de pistas e suspeitos.
typedef struct
{
	NoHash* dados[TAMANHO_TABELA_HASH];
} TabelaHash;

// **** Declarações das funções. ****

// **** Funções de Interface de Usuário ****

/// @brief Exibe o menu principal.
/// @param Inteiro. Ponteiro via referência, para conter o valor da opção escolhida.
void exibirMenuPrincipal(int* opcao);
/// @brief Exibe e monitora o estado atual resultante da investigação,
/// em função nó atualmente visitado(Sala).
/// @param Sala. Ponteiro para recuperação de informações. Somente leitura.
/// @param Pista. Ponteiro via referência, para leitura e atribuição das pistas.
/// @param TabelaHash. Ponteiro usado para recuperar as associações de pistas e suspeitos. Somente leitura.
/// @param Texto. Valor fornecido de forma randômica, representando o verdadeiro culpado. Somente leitura.
void exibirEstadoInvestigacao(
	const Sala* noLocal,
	Pista** arvorePistas,
	const TabelaHash* tabela,
	const char* verdadeiroCulpado,
	int* opcao);

// **** Funções de Lógica Principal e Gerenciamento de Memória ****

/// @brief Cria um ponteiro para referência ao nó(Sala) raiz principal.
/// @returns Sala. Ponteiro do tipo conforme especificado.
Sala* criarMansao();
/// @brief Cria os nós de forma manual para as salas, além de adicionar as pistas
/// já relacionadas aos suspeitos em cada uma delas.
/// @param Sala. Ponteiro via referência, para atribuição e leitura de valores.
void criarSalas(Sala* mansao);
/// @brief Prepara as principais referências para iniciar uma nova partida.
/// @param Sala. Ponteiro via referência da árvore principal, para leitura e atribuição de valores.
/// @param TabelaHash. Ponteiro usado para atribuir e recuperar as associações de pistas e suspeitos.
/// @param Sala. Ponteiro via referência da sala atual, para leitura e atribuição de valores.
/// @param Pista. Ponteiro via referência da árvore principal, para leitura e atribuição de valores.
/// @param Texto. Ponteiro via referência, para conter o valor a ser atribuido de forma randômica, 
/// representando o verdadeiro culpado.
void iniciarNovoJogo(Sala** mansao, TabelaHash** tabela, Sala** atual, Pista** arvorePistas, char** verdadeiroCulpado);
/// @brief Prepara as principais referências para reiniciar em uma nova partida.
/// @param Sala. Ponteiro via referência da árvore principal, para leitura e atribuição de valores.
/// @param TabelaHash. Ponteiro usado para atribuir e recuperar as associações de pistas e suspeitos.
/// @param Sala. Ponteiro via referência da sala atual, para leitura e atribuição de valores.
/// @param Pista. Ponteiro via referência da árvore principal, para leitura e atribuição de valores.
/// @param Texto. Ponteiro via referência, para conter o valor a ser atribuido de forma randômica, 
/// representando o verdadeiro culpado.
void reiniciarJogo(Sala** mansao, TabelaHash** tabela, Sala** atual, Pista** arvorePistas, char** verdadeiroCulpado);
/// @brief Explora os nós de forma hierárquica, simulando uma navegação.
/// @param Enumeração. Valor descrevendo a direção a seguir na navegação.
/// @param Sala. Ponteiro via referência, usado para exploração das salas.
/// @param Sala. Ponteiro via referência, usado como valor padrão, em caso de recuo na navegação.
/// @param Pista. Ponteiro via referência da árvore de pistas, usado para leitura e atribuição no processo de navegação.
/// @param TabelaHash. Ponteiro usado para recuperar as associações de pistas e suspeitos. Somente leitura.
/// @param Texto. Valor fornecido de forma randômica, representando o verdadeiro culpado. Somente leitura.
/// @param Inteiro. Ponteiro via referência, para conter o valor da opção escolhida no menu principal.
/// @returns Sala. Ponteiro do tipo conforme especificado.
Sala* explorarSalasComPistas(SeguirNaDirecao direcao, Sala* atual, Sala* mansao, Pista** arvorePistas,
	const TabelaHash* tabela, const char* verdadeiroCulpado, int* opcao);
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
/// @param Pista. Ponteiro via referência, usado na inserção.
/// @param Texto. Valor descrevendo a pista.
/// @returns Pista. Ponteiro do tipo conforme especificado.
Pista* inserirPista(Pista* raiz, const char* pista);
/// @brief Efetua a exibição de informações sobre as pistas.
/// @param Pista. Ponteiro via referência, usado na recuperação de informações. Somente leitura.
/// @returns Pista. Ponteiro do tipo conforme especificado.
void exibirPistas(const Pista* pista);
/// @brief Efetua a criação de uma tabela hash, para conter as informações sobre as pistas e suspeitos.
/// @param Vetor. Ponteiro para um vetor contendo uma relação com os valores de texto das pistas.
/// @returns TabelaHash. Ponteiro do tipo conforme especificado.
TabelaHash* CriarTabelaHash(const char** listaSuspeitos);
/// @brief Efetua a criação um valor hash, para uso com as associações sobre as pistas e suspeitos.
/// Baseado no conteúdo da plataforma.
/// @param Texto. Ponteiro para um valor de texto, para efetuar o hash.
/// @returns Inteiro. Valor de um índice válido para uso seguro com a tabela.
int funcao_hash(const char* chave);
/// @brief Efetua a inserção de valores de pista e suspeito associados na tabela hash.
/// Baseado no conteúdo da plataforma.
/// @param Texto. Ponteiro para o valor de texto da pista a inserir.
/// @param Texto. Ponteiro para o valor de texto do suspeito a inserir.
/// @param TabelaHash. Ponteiro via referência, usado para atribuir e recuperar pistas e suspeitos.
void inserirNoHash(const char* pista, const char* suspeito, TabelaHash* tabela);
/// @brief Efetua a remoção de valores de pista e suspeito associados na tabela hash.
/// Baseado no conteúdo da plataforma.
/// @param Texto. Ponteiro para o valor de texto da pista a remover.
/// @param TabelaHash. Ponteiro via referência, usado para atribuir e recuperar pistas e suspeitos.
void removerNoHash(const char* suspeito, TabelaHash* tabela);
/// @brief Efetua a busca de nós, relativos a pistas e suspeitos associados na tabela hash.
/// Baseado no conteúdo da plataforma.
/// @param Texto. Ponteiro para o valor de texto da pista a procurar.
/// @param TabelaHash. Ponteiro via referência, usado para recuperar pistas e suspeitos. Somente leitura.
/// @returns NoHash. Ponteiro do tipo conforme especificado.
NoHash* buscarNoHash(const char* pista, const TabelaHash* tabela);
/// @brief Efetua a busca de nós, relativos a pistas, em uma estratégia BST.
/// Baseado no conteúdo da plataforma.
/// @param Pista. Ponteiro via referência da árvore, usada na busca.
/// @param Texto. Ponteiro para o valor de texto da pista a procurar.
/// @returns Pista. Ponteiro do tipo conforme especificado.
Pista* buscarPista(Pista* raiz, const char* pista);
/// @brief Efetua a busca do suspeito, além da lógica do controle de exploração e monitoramento de pistas.
/// @param Pista. Ponteiro via referência da árvore, usada na recuperação e atribuição de pistas.
/// @param Texto. Ponteiro para o valor de texto da pista encontrada.
/// @param TabelaHash. Ponteiro via referência, usado para recuperar pistas e suspeitos. Somente leitura.
/// @param Texto. Ponteiro para o valor de texto criado randomicamente para o culpado. Somente leitura.
/// @param Inteiro. Ponteiro via referência, para conter o valor da opção escolhida no menu principal.
void encontrarSuspeito(Pista** pista, const char* descricaoPista, const TabelaHash* tabela,
	const char* verdadeiroCulpado, int* opcao);
/// @brief Efetua a lógica do veredito do acusado.
/// @param Texto. Ponteiro para o valor de texto do acusado.
/// @param Texto. Ponteiro para o valor de texto do verdadeiro culpado.
/// @param Inteiro. Ponteiro via referência, para conter o valor da opção escolhida no menu principal.
/// @returns Bool. Verdadeiro(true) em caso de sucesso. Caso contrário, falso(false).
bool verificarSuspeitoFinal(const char* acusado, const char* verdadeiroCulpado, int* opcao);
/// @brief Exibe um resumo da busca das pistas relativas aos suspeitos.
/// @param TabelaHash. Ponteiro via referência, usado para recuperar pistas e suspeitos. Somente leitura.
void exibirHash(const TabelaHash* tabela);
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
/// @brief Libera a memória alocada para a tabela hash e seus itens, com navegação sequencial.
/// Baseado no conteúdo da plataforma.
/// @param TabelaHash. Ponteiro raiz, via referência, usado na operação de liberação.
void liberarTabelaHash(TabelaHash* table);
/// @brief Libera a memória alocada para um nó e seus descendentes.
/// @param Sala. Ponteiro raiz, via referência, usado na operação de liberação.
/// @param Pista. Ponteiro raiz, via referência, usado na operação de liberação.
void liberarMemoria(Sala* raiz, Pista* pista, TabelaHash* table);

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

	// 🧠 Nível Mestre: Relacionamento de Pistas com Suspeitos via Hash
	//
	// - Crie uma struct Suspeito contendo nome e lista de pistas associadas.
	// - Crie uma tabela hash (ex: array de ponteiros para listas encadeadas).
	// - A chave pode ser o nome do suspeito ou derivada das pistas.
	// - Implemente uma função inserirHash(pista, suspeito) para registrar relações.
	// - Crie uma função para mostrar todos os suspeitos e suas respectivas pistas.
	// - Adicione um contador para saber qual suspeito foi mais citado.
	// - Exiba ao final o “suspeito mais provável” baseado nas pistas coletadas.
	// - Para hashing simples, pode usar soma dos valores ASCII do nome ou primeira letra.
	// - Em caso de colisão, use lista encadeada para tratar.
	// - Modularize com funções como inicializarHash(), buscarSuspeito(), listarAssociacoes().

	// Configurações de caracteres para ajuste de ortografia para saída do console(UTF-8).

#ifdef _WIN32
	// Plataforma Windows.
	SetConsoleOutputCP(CP_UTF8);
#endif
	// Inicializa o gerador de números aleatórios.
	srand((unsigned int)time(NULL));

	printf("======================================================\n");
	printf("====== 🔎  DETECTIVE QUEST - Nível Mestre  🔍 =======\n");
	printf("======================================================\n");

	int opcao = -1;

	Sala* arvoreMansao, * atual; // Definindo o valor padrão inicial para a navegação.

	TabelaHash* tabela;

	Pista* arvorePistas; // Ponteiro para conter uma referência para os nós das pistas.

	char* verdadeiroCulpado;

	iniciarNovoJogo(&arvoreMansao, &tabela, &atual, &arvorePistas, &verdadeiroCulpado);

	do
	{
		exibirEstadoInvestigacao(atual, &arvorePistas, tabela, verdadeiroCulpado, &opcao);

		exibirMenuPrincipal(&opcao);

		switch (opcao)
		{
		case 1:
			// Ir para a esquerda.
			atual = explorarSalasComPistas(SeguirNaDirecao_ESQUERDA, atual, arvoreMansao,
				&arvorePistas, tabela, verdadeiroCulpado, &opcao);
			break;
		case 2:
			// Ir para a direita.
			atual = explorarSalasComPistas(SeguirNaDirecao_DIREITA, atual, arvoreMansao,
				&arvorePistas, tabela, verdadeiroCulpado, &opcao);
			break;
		case 3:
			exibirHash(tabela); // Reiniciando a partida e exibindo resumo das pistas da partida anterior.
			reiniciarJogo(&arvoreMansao, &tabela, &atual, &arvorePistas, &verdadeiroCulpado);
			opcao = -1; // Vamos continuar o jogo.
			break;
		case 0:
			//  0  Sair.
			exibirHash(tabela); // Exibindo resumo das pistas.
			printf("\n==== Saindo do sistema... ====\n");
			break;
		default:
			// Continua.
			printf("\n==== ⚠️  Opção inválida. ====\n");
			break;
		}

	} while (opcao != 0);


	liberarMemoria(arvoreMansao, arvorePistas, tabela);

	printf("\n==== Operação encerrada. ====\n");


	return EXIT_SUCCESS;
}

// **** Implementação das funções. ****

// **** Funções de Interface de Usuário ****

void exibirMenuPrincipal(int* opcao)
{
	if (*opcao == 3 || *opcao == 0)
	{
		return; //Optando por jogar novamente, ou saindo.
	}

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

void exibirEstadoInvestigacao(const Sala* noLocal, Pista** arvorePistas,
	const TabelaHash* tabela, const char* verdadeiroCulpado, int* opcao)
{
	if (noLocal == NULL)
	{
		printf("\n ====  🚫  Nada existe além do local atual.  🚩 ==== \n");
		printf("\n  ℹ️  Vamos voltar ao ponto de partida.\n");
		return;
	}

	if (noLocal->pista != NULL)
	{
		printf("\n ====  ℹ️  Foi encontrada uma pista nesse local: %s ❕ ==== \n", noLocal->pista);

		encontrarSuspeito(arvorePistas, noLocal->pista, tabela, verdadeiroCulpado, opcao);
	}

	printf("\n ====  ℹ️  No momento, você se encontra neste local: %s  🚩 ==== \n", noLocal->nome);
}

// **** Funções de Lógica Principal e Gerenciamento de Memória ****

void iniciarNovoJogo(Sala** mansao, TabelaHash** tabela, Sala** atual, Pista** arvorePistas, char** verdadeiroCulpado)
{
	*mansao = criarMansao();
	criarSalas(*mansao);

	// Vamos sortear alguém para ser o culpado, desde que atenda os requisitos obrigatórios do jogo.
	char* listaCulpados[] = { "Mr. X", "Butcher", "El Divo", "Dr. Stein", "Krauser", "Julius", "Freud" };

	int sorteio = rand() % 7; // De 0 a 6, dentro do intervalo da lista de culpados.

	*verdadeiroCulpado = listaCulpados[sorteio];

	*tabela = CriarTabelaHash(listaCulpados);
	*atual = *mansao; // Definindo o valor padrão inicial para a navegação.

	*arvorePistas = criarPista("O sistema de alarme não foi acionado."); // Ponteiro para conter uma referência para os nós das pistas.
}

void reiniciarJogo(Sala** mansao, TabelaHash** tabela, Sala** atual, Pista** arvorePistas, char** verdadeiroCulpado)
{
	liberarMemoria(*mansao, *arvorePistas, *tabela);
	iniciarNovoJogo(mansao, tabela, atual, arvorePistas, verdadeiroCulpado);
}

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
	mansao->direita = criarSala("Sala de Estar", "Têm um vaso quebrado com um punhal dentro.");

	mansao->esquerda->esquerda = criarSala("Escadaria", "Há um colar despedaçado.");
	mansao->esquerda->direita = criarSala("O Corredor", "Têm uma mancha de sangue.");

	mansao->esquerda->esquerda->esquerda = criarSala("A Suíte", "Há uma maçaneta quebrada.");
	mansao->esquerda->esquerda->direita = criarSala("Hidro", "Têm problemas elétricos.");

	mansao->esquerda->direita->esquerda = criarSala("Biblioteca", "Há livros jogados pelo chão.");
	mansao->esquerda->direita->direita = criarSala("Escritório", "A janela está quebrada.");

	mansao->direita->esquerda = criarSala("A Sala de Jantar", "O café ainda está quente no copo.");
	mansao->direita->direita = criarSala("O Gazebo", "Os assentos estão bagunçados.");

	mansao->direita->esquerda->esquerda = criarSala("A Cozinha", "Alguém deixou algo os aparelhos ligados.");
	mansao->direita->esquerda->direita = criarSala("Despensa", "Os produtos estão jogados pelo chão.");

	mansao->direita->direita->esquerda = criarSala("A Piscina", "Está parcialmente coberta.");
	mansao->direita->direita->direita = criarSala("Quadra", "A iluminação está parcial.");
}

TabelaHash* CriarTabelaHash(const char** listaSuspeitos)
{
	TabelaHash* table = (TabelaHash*)malloc(sizeof(TabelaHash));
	if (table == NULL)
	{
		printf(" ❌  Erro ao alocar memória para a tabela hash.\n");
		return NULL;
	}

	// Inicializa todos os ponteiros da tabela como NULL
	for (int i = 0; i < TAMANHO_TABELA_HASH; i++) {
		table->dados[i] = NULL;
	}

	int indices[7] = { 0, 1, 2, 3, 4, 5, 6 };
	// Vamos usar um embaralhamento dos suspeitos em estilo de algoritmo (Fisher-Yates),
	// apenas para deixar o jogo um pouquinho mais dinâmico.
	for (int i = 7 - 1; i > 0; i--)
	{
		int j = rand() % (i + 1);
		int temp = indices[i];
		indices[i] = indices[j];
		indices[j] = temp;
	}

	//inserirNoHash("O sistema de alarme não foi acionado.", "Eu", table); // Apenas para descontrair o jogador.
	inserirNoHash("Há uma cápsula de projétil no chão.", listaSuspeitos[indices[0]], table);
	inserirNoHash("Têm um vaso quebrado com um punhal dentro.", listaSuspeitos[indices[1]], table);
	inserirNoHash("Há um colar despedaçado.", listaSuspeitos[indices[2]], table);
	inserirNoHash("Têm uma mancha de sangue.", listaSuspeitos[indices[3]], table);
	inserirNoHash("Há uma maçaneta quebrada.", listaSuspeitos[indices[4]], table);
	inserirNoHash("Têm problemas elétricos.", listaSuspeitos[indices[5]], table);
	inserirNoHash("Há livros jogados pelo chão.", listaSuspeitos[indices[6]], table);
	inserirNoHash("A janela está quebrada.", listaSuspeitos[indices[0]], table);
	inserirNoHash("O café ainda está quente no copo.", listaSuspeitos[indices[1]], table);
	inserirNoHash("Os assentos estão bagunçados.", listaSuspeitos[indices[2]], table);
	inserirNoHash("Alguém deixou algo os aparelhos ligados.", listaSuspeitos[indices[3]], table);
	inserirNoHash("Os produtos estão jogados pelo chão.", listaSuspeitos[indices[4]], table);
	inserirNoHash("Está parcialmente coberta.", listaSuspeitos[indices[5]], table);
	inserirNoHash("A iluminação está parcial.", listaSuspeitos[indices[6]], table);

	return table;
}

Sala* explorarSalasComPistas(SeguirNaDirecao direcao, Sala* atual, Sala* mansao,
	Pista** arvorePistas, const TabelaHash* tabela, const char* verdadeiroCulpado, int* opcao)
{
	if (atual == NULL)
	{
		return NULL;
	}

	// Caso o ponto de navegação atual resulte em um nó folha, vamos voltar
	// automaticamente à referência mais alta. Neste nível de desafio, é indefinido
	// em que momento a investigação deveria terminar, até o jogador decidir sair.
	switch (direcao)
	{
	case SeguirNaDirecao_ESQUERDA:

		if (atual->esquerda == NULL)
		{
			exibirEstadoInvestigacao(atual->esquerda, arvorePistas, tabela, verdadeiroCulpado, opcao);
			return mansao;
		}

		return atual->esquerda;

	case SeguirNaDirecao_DIREITA:

		if (atual->direita == NULL)
		{
			exibirEstadoInvestigacao(atual->direita, arvorePistas, tabela, verdadeiroCulpado, opcao);
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

void encontrarSuspeito(Pista** arvorePistas, const char* descricaoPista,
	const TabelaHash* tabela, const char* verdadeiroCulpado, int* opcao)
{	
	bool acusar = false;
	int contadorPistas = 0;

	if (arvorePistas == NULL || *arvorePistas == NULL)
	{
		return;
	}
	
	Pista* pistaAtual = buscarPista(*arvorePistas, descricaoPista);
	// Verificando se falta inserir a pista.
	if (pistaAtual == NULL)
	{
		*arvorePistas = inserirPista(*arvorePistas, descricaoPista);
		pistaAtual = buscarPista(*arvorePistas, descricaoPista);
	}

	if (pistaAtual == NULL)
	{
		// Se ainda for NULL, algo deu errado.
		return;
	}

	//Calculando o índice hash da pista atual.	
	int indiceAtual = funcao_hash(pistaAtual->pista);

	if (indiceAtual < 0 || indiceAtual >= TAMANHO_TABELA_HASH)
	{
		return; //índice inválido.
	}

	// Precisamos de um valor relativo ao suspeito. Vamos coletar na tabela hash.
	// Antes, assumiremos o item padrão no encadeamento.
	NoHash* correspondente = tabela->dados[indiceAtual];
	// Depois, vamos verificar as colisões.
	while (correspondente != NULL)
	{
		if (strcmp(descricaoPista, correspondente->pista) == 0)
		{
			contadorPistas++; // Recuperaremos o item correto se hover correspondência.			
			break;
		}
		correspondente = correspondente->proximo;
	}

	if (correspondente == NULL)
	{
		// Nenhuma associação para esta pista.
		return;
	}
	// Suspeito recuperado.
	const char* suspeito = correspondente->suspeito;

	for (int i = 0; i < TAMANHO_TABELA_HASH; i++)
	{
		NoHash* atual = tabela->dados[i];
		while (atual != NULL)
		{
			if (strcmp(atual->suspeito, suspeito) == 0 && strcmp(atual->pista, descricaoPista) != 0)
			{
				Pista* pistaAtual = buscarPista(*arvorePistas, atual->pista);

				if (pistaAtual != NULL)
				{
					contadorPistas++;
				}

				if (contadorPistas >= NUMERO_PISTAS_REQUERIDAS)
				{
					acusar = true;
					break;
				}
			}
			
			atual = atual->proximo;
		}

		if (acusar)
		{
			break;
		}
	}	

	printf("\n  🔍  Pista '%s' associada a %s. (Total de pistas: %d)\n", descricaoPista, suspeito, contadorPistas);

	if (acusar)
	{
		exibirPistas(*arvorePistas);

		printf("\n ⚠️  Duas ou mais pistas apontadas a %s durante a investigação.\n", suspeito);

		char resposta;

		bool invalido = false;

		do
		{
			printf("\nDeseja acusar este suspeito? (s/n): ");
			resposta = getchar();
			limparBufferEntrada();
			invalido = resposta != 's' && resposta != 'S' && resposta != 'n' && resposta != 'N';

			if (invalido)
			{
				printf("\n==== ⚠️  Entrada inválida. Esperado: s(ou S) ou n(ou N). ====\n");
			}
		} while (invalido);

		if (!((resposta == 's' || resposta == 'S') &&
			verificarSuspeitoFinal(suspeito, verdadeiroCulpado, opcao)))
		{
			printf("\n De volta à investigação... ⬅️\n");
		}
	}
}

bool verificarSuspeitoFinal(const char* acusado, const char* verdadeiroCulpado, int* opcao)
{
	printf("\n====================== ⚖️ Efetuando Julgamento ======================\n");
	printf("		Você acusou o suspeito: %s \n", acusado);
	printf("===================================================================\n");

	if (!strcmp(acusado, verdadeiroCulpado) == 0)
	{
		printf(" ❌  %s não é o verdadeiro culpado.\n", acusado);
		printf("\nAs pistas levaram a uma conclusão incorreta.\n");
		printf("\n ⚠️  Você precisará continuar a investigação. Revise as pistas antes de tentar novamente.\n");
		return false;
	}

	printf("\n  ✅  A investigação foi conclusiva! %s é realmente o culpado!\n", acusado);
	printf("\n  🕵️  Todas as pistas apontam para este desfecho.\n");
	printf("\n  🏁  Caso encerrado com sucesso!\n");

	printf("\n===============================================================\n");

	char resposta;

	bool invalido = false;

	do
	{
		printf("\n  🔁  Deseja jogar novamente?(s/n): ");
		resposta = getchar();
		limparBufferEntrada();
		invalido = resposta != 's' && resposta != 'S' && resposta != 'n' && resposta != 'N';

		if (invalido)
		{
			printf("\n==== ⚠️  Entrada inválida. Esperado: s(ou S) ou n(ou N). ====\n");
		}
	} while (invalido);

	if (resposta == 's' || resposta == 'S')
	{
		*opcao = 3; // Jogar de novo.
		return true;
	}

	*opcao = 0; // Fim de jogo.

	return true;
}

void exibirHash(const TabelaHash* table)
{
	printf("\n============== Fim de Jogo ==============\n");
	printf("\n===== Resumo das pistas ↔ suspeitos =====\n\n");
	for (int i = 0; i < TAMANHO_TABELA_HASH; i++)
	{
		NoHash* atual = table->dados[i];
		while (atual != NULL)
		{
			printf(" • [%s] ➜ %s\n", atual->suspeito, atual->pista);
			atual = atual->proximo;
		}
	}
}

int funcao_hash(const char* chave)
{
	int soma = 0;
	for (int i = 0; chave[i] != '\0'; i++)
	{
		soma += chave[i];
	}
	return soma % TAMANHO_TABELA_HASH;
}

void inserirNoHash(const char* pista, const char* suspeito, TabelaHash* tabela)
{
	int indice = funcao_hash(pista); // Descobre onde armazenar.
	// Cria um nó.
	NoHash* novo = (NoHash*)malloc(sizeof(NoHash));

	if (novo == NULL)
	{
		printf("\n  ❌  Erro ao tentar alocar a memória para o novo nó da tabela hash.\n");
		return;
	}

	strcpy(novo->pista, pista);
	strcpy(novo->suspeito, suspeito);

	// Insere no início da lista (head).
	novo->proximo = tabela->dados[indice];
	tabela->dados[indice] = novo;
}

void removerNoHash(const char* pista, TabelaHash* tabela)
{
	int indice = funcao_hash(pista);
	NoHash* atual = tabela->dados[indice];
	NoHash* anterior = NULL;

	while (atual != NULL)
	{
		if (strcmp(atual->pista, pista) == 0)
		{
			if (anterior == NULL) {
				tabela->dados[indice] = atual->proximo; // Era o primeiro.
			}
			else {
				anterior->proximo = atual->proximo; // "Pula" o nó atual.
			}
			free(atual);
			printf("\n  ℹ️  '%s' removido.\n", pista);
			return;
		}
		anterior = atual;
		atual = atual->proximo;
	}

	printf(" ℹ️  '%s' não encontrado.\n", pista);
}

NoHash* buscarNoHash(const char* pista, const TabelaHash* tabela)
{
	int indice = funcao_hash(pista);
	NoHash* atual = tabela->dados[indice];

	while (atual != NULL)
	{
		if (strcmp(atual->pista, pista) == 0)
		{
			return atual; // Encontrou.
		}

		atual = atual->proximo;
	}

	return NULL; // Não está na lista.
}

Pista* buscarPista(Pista* raiz, const char* pista)
{
	if (raiz == NULL)
	{
		return NULL;
	}
	if (strcmp(pista, raiz->pista) == 0)
	{
		return raiz;
	}
	else if (strcmp(pista, raiz->pista) < 0)
	{
		return buscarPista(raiz->esquerda, pista);
	}
	else
	{
		return buscarPista(raiz->direita, pista);
	}
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

void liberarTabelaHash(TabelaHash* table)
{
	if (table == NULL)
		return;

	for (int i = 0; i < TAMANHO_TABELA_HASH; i++)
	{
		NoHash* atual = table->dados[i];
		while (atual != NULL)
		{
			NoHash* temp = atual;
			atual = atual->proximo;
			free(temp);
		}
	}

	free(table);
}

void liberarMemoria(Sala* raiz, Pista* pista, TabelaHash* table)
{
	liberarSala(raiz);
	liberarPista(pista);
	liberarTabelaHash(table);

	printf("\n  ✅  Memória alocada liberada completamente.\n");
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