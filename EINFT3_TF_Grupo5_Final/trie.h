#define t_Alfabeto 26
#define n 100
typedef struct no {
	int d_edicao;
	char palavra[n];
	struct no *prox;
}ligacao;

typedef struct Trie {
	int chave;
	ligacao *ligacoes;
	struct Trie *filho[t_Alfabeto];
}trie;

trie *novaTrie();
void inserir(trie * node, char * chave, int id);
int busca(trie *node, char *chave);
void deletar(trie **temp);
void imprimir_Trie(trie *node);

void carrega_Palavras(trie *node);
int distancia_Edicao(char *palavra_1, char *palavra_2);
void palavras_Ligadas(trie *node);
void maior_PrefixoComum(trie *node);
void palavra_Quebrada(trie *node);
void limpar(trie **tree);
