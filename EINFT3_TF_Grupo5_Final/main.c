#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int menu();

int main(int argc, char *argv[]) {
	trie *root = novaTrie();
	char palavra[n], palavra2[n];
	
	carrega_Palavras(root);

	for(;;){
		switch(menu()){
			case 1:
				printf("Digite a palavra: ");
				scanf(" %s", palavra);
				inserir(root, strlwr(palavra), 1);
				ligar_Palavra(&root, strlwr(palavra));
				limpar(&root);
				carrega_Palavras(root);
				break;
			case 2:
				printf("Digite a palavra: ");
				scanf(" %s", palavra);
				if(busca(root, strlwr(palavra)) != 0){
					printf("\nPalavra esta na Trie!\n");
				} else {
					printf("\nPalavra nao esta na Trie!\n");
				}
				break;
			case 3:
				deletar(&root);
				break;
			case 4:
				printf("Digite a primeira palavra: ");
				scanf(" %s", palavra);
				printf("Digite a segunda palavra: ");
				scanf(" %s", palavra2);
				
				printf("\nDistancia de edicao: %d", distancia_Edicao(strlwr(palavra), strlwr(palavra2)));
				break;
			case 5:
				palavras_Ligadas(root);
				break;
			case 6:
				maior_PrefixoComum(root);
				break;
			case 7:
				palavra_Quebrada(root);
				break;
			case 8:
				imprimir_Trie(root);
				break;
			case 9:
				exit(0);
				break;
			default:
				printf("\n\nOpcão incorreta\n\n");
		}
		printf("\nClick em qualquer tecla pra voltar ao menu principal\n");
		getch();
		system("cls");
	}
	
	return 0;
}

int menu(){
	int opt;
	printf("--------------------------\n");
	printf("           MENU\n");
	printf("--------------------------\n");
	printf(" 1.Inserir palavra na TRIE\n");
	printf(" 2.Procurar palavra\n");
	printf(" 3.Eliminar palavra\n");
	printf(" 4.Verificar distancia de edicao\n");
	printf(" 5.Palavras ligadas\n");
	printf(" 6.Maior prefixo comum\n");
	printf(" 7.Palavra quebrada\n");
	printf(" 8.Imprimir palavras na TRIE\n");
	printf(" 9.Sair\n");
	printf("\nOpcão: ");
	scanf("%d", &opt);
	system("cls");
	return opt;
}

