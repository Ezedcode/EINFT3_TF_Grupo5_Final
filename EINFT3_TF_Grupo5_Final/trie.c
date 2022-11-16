#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"

void inserir_emLetras(char *chave);
int busca_emLetras(char *chave);
trie *novaTrie();
int tem_Filhos(trie *temp);
int deletar_Palavra(trie **temp, char *chave);
int count_Dis(char *palavra_1, char *palavra_2);
void ligar_Palavra(trie **node, char *palavra_1);
void inserir_ligacao(trie **node, char *palavra_1, char *palavra_2);
void imprimir_Ligacao(trie *tree,ligacao *node, int numero);
char *irParaNo_ImrimirLigacoes(trie *node, char *chave, int numero);
int menor_Palavra(char *palavra_1,char *palavra_2, char *palavra_3);
char *busca_PalavraQuebrada(char *palavra_1, char *palavra_2);


void carrega_Palavras(trie *node){
	FILE * arqLetra = fopen("letras.txt","r");
	FILE * arqlig = fopen("letras.txt","r");
	char chave[n];
	
	if(arqLetra != NULL) {
		while(fscanf(arqLetra,"%s", chave) != EOF) {
			inserir(node, strlwr(chave), 0);
		}
	}
	
	fclose(arqLetra);
	
	if(arqlig != NULL) {
		while(fscanf(arqlig,"%s", chave) != EOF) {
			ligar_Palavra(&node, strlwr(chave));
		}
	}
	
	fclose(arqlig);
}

void inserir_emLetras(char *chave){
	if(busca_emLetras(chave) == 1) return;
		
	FILE * arqLetra = fopen("letras.txt","a");
	fprintf(arqLetra, "\n%s", chave);
	fclose(arqLetra);
}

int busca_emLetras(char *chave){
	FILE * arqLetra = fopen("letras.txt","r");
	char palavra[n];
	
	if(arqLetra != NULL) {
		while(fscanf(arqLetra,"%s", palavra) != EOF) {
			if(stricmp(chave, palavra) == 0) return 1;
		}
	}
	
	fclose(arqLetra);
	return 0;
}

trie *novaTrie(){
	int i;
	
	trie *nova = (trie *)malloc(sizeof(trie));
	
	if(nova != NULL){
		nova->chave = 0;
		nova->ligacoes = NULL;
		
		for(i=0; i < t_Alfabeto; i++)
			nova->filho[i] = NULL;
	}
	
	return nova;
}

void inserir(trie * node, char * chave, int id) {
	trie *temp = node;
	char *aux = chave;
	
	if(busca(node, chave) != 0 && id == 1){
		printf("Palavra ja esta na Trie!");
		return;
	}
	
	while(*chave){
		if (temp->filho[*chave - 'a'] == NULL){
			temp->filho[*chave - 'a'] = novaTrie();
		}
			
		temp = temp->filho[*chave - 'a'];
		
		*chave++;
	}
	
	temp->chave = 1;
	
	if(id == 1){
		inserir_emLetras(aux);
		printf("\nPalavra inserida!");
	}
}

int busca(trie *node, char *chave){
	
	if(node == NULL){
		return 0;
	}
	trie *temp = node;
	
	while(*chave){
		
		temp = temp->filho[*chave - 'a'];
		
		if(temp == NULL){
			return 0;
		}
		
		chave++;
	} 
	
	return temp->chave;
}

int tem_Filhos(trie *temp){
	
	int i;
	
	for(i=0; i< t_Alfabeto; i++){
		if(temp->filho[i]) {
			return 1;
		}
	}
	
	return 0;
}

int deletar_Palavra(trie **temp, char *chave){
	char *aux = chave;
	
	if(*temp == NULL){
		return 0;
	}
			
	if(*chave){
		if(*temp != NULL && (*temp)->filho[*chave - 'a'] != NULL && 
		deletar_Palavra(&((*temp)->filho[*chave - 'a']), chave + 1) && 
		(*temp)->chave == 0){
			
			if (!tem_Filhos(*temp)){
				free(*temp);
				(*temp) = NULL;
				if(temp == '\0')
				return 1;	
			} else {
				return 0;
			}
		}
	}
	
	if (*chave == '\0' && (*temp)->chave){
		
		if(!tem_Filhos(*temp)) {
			free(*temp);
			(*temp) = NULL;
			return 1;
		} else {
			(*temp)->chave = 0;
			return 0;
		}
	}
			
	return 0;
}

void deletar(trie **temp){
	char palavra[n];
	
	printf("Digite a palavra: ");
	scanf(" %s", palavra);
	
	if(busca(*temp, strlwr(palavra)) == 0){
		printf("\nPalavra nao existe na Trie!");
		return;
	}
	
	deletar_Palavra(temp, strlwr(palavra));
				
	if(busca(*temp, strlwr(palavra)) == 0)
		printf("\nPalavra eliminada!");
	
	return;
}

void imprimir_Trie(trie *node){
	FILE * arqLetra = fopen("letras.txt","r");
	char palavra[n];
	int count=1;
	
	printf("Lista de palavra na TRIE!\n");
	
	if(arqLetra != NULL) {
		while(fscanf(arqLetra,"%s", palavra) != EOF) {
			if(busca(node, strlwr(palavra)) != 0)printf("\n%d.%s",count++,palavra);
		}
	}
	
	printf("\n");
	
	fclose(arqLetra);
}

//1

int count_Dis(char *palavra_1, char *palavra_2){
	int count = 0;
	int i;
	
	for(i=0; i < strlen(palavra_1); i++){
		if(palavra_1[i] != palavra_2[i]){
			count++;
		}
	}

	return count;
}

int distancia_Edicao(char *palavra_1, char *palavra_2){
	
	if(strlen(palavra_1) < strlen(palavra_2)){
		
		return (count_Dis(palavra_1,palavra_2)+(strlen(palavra_2)-strlen(palavra_1)));
		
	} else if(strlen(palavra_1) == strlen(palavra_2)) {
	
		return count_Dis(palavra_1,palavra_2);

	} else {
		
		return (count_Dis(palavra_2,palavra_1)+(strlen(palavra_1)-strlen(palavra_2)));
	}
}

void ligar_Palavra(trie **node, char *palavra_1){
	FILE * arqLetra = fopen("letras.txt","r");
	char *palavra_2;
	
	if(arqLetra != NULL) {
		
		while(fscanf(arqLetra,"%s ", palavra_2) != EOF) {
			if(busca(*node, palavra_1) != 0 && busca(*node, palavra_2) != 0){
				inserir_ligacao(node, palavra_1, palavra_2);
			}
		}
		
	}
	
	fclose(arqLetra);

}

void inserir_ligacao(trie **node, char *palavra_1, char *palavra_2){
	
	if(distancia_Edicao(palavra_1, palavra_2)>=1 && distancia_Edicao(palavra_1, palavra_2)<=3){
		trie *temp = (*node);
		char *aux = palavra_1;
		
		while(*aux){
			temp = temp->filho[*aux - 'a'];
			*aux++;	
		}
	
		ligacao *novaLigacao = (ligacao *)malloc(sizeof(ligacao));
		
		novaLigacao->d_edicao = distancia_Edicao(palavra_1, palavra_2);
		
		strcpy(novaLigacao->palavra, palavra_2);
		
		novaLigacao->prox = temp->ligacoes;
	
		temp->ligacoes = novaLigacao;
	}
}

void imprimir_Ligacao(trie *tree,ligacao *node, int numero){
	ligacao *q;
	ligacao *p;
	int count = 0, aux = 0;
	
	for(p=node; p!=NULL; p=p->prox){
		if(p->d_edicao == numero && busca(tree, p->palavra) != 0)
			count++;
	}
	
	if(count == 0){
		printf(" Sem ligacoes.");
		return;
	}
	
	for(q=node; q!=NULL; q=q->prox){
		if(q->d_edicao == numero){
			aux++;
			if(busca(tree, q->palavra)){			
				if(aux == count && busca(tree, q->palavra) != 0){
					printf("%s.", q->palavra);
					return;
				}
				printf("%s, ", q->palavra);
			}
		}
	}
}

char *irParaNo_ImrimirLigacoes(trie *node, char *chave, int numero){
	
	trie *temp = node;
	
	while(*chave){
		temp = temp->filho[*chave - 'a'];
		chave++;
	} 
	
	if(temp->ligacoes == NULL)
		printf("Sem ligacoes.");
		
	imprimir_Ligacao(node, temp->ligacoes, numero);
		
}

void palavras_Ligadas(trie *node){
	char palavra[n];
	int numero;
	
	printf("Digite a palavra: ");
	scanf(" %s", palavra);
	
	printf("Digite um numero: ");
	scanf("%d", &numero);
	
	if(numero < 1 || numero > 3){
		printf("\nDigite um numero no intervalo de 1 a 3!\n\n");
		palavras_Ligadas(node);
	}else if(busca(node, strlwr(palavra)) != 0){
		printf("\nPalavra ligadas: ");
		irParaNo_ImrimirLigacoes(node, strlwr(palavra), numero);
	} else {
		printf("\nA palavra %s nao faz parte da TRIE! Insira uma palavra que esteja na TRIE!\n\n", strlwr(palavra));
		palavras_Ligadas(node);
	}
}

//2

int menor_Palavra(char *palavra_1,char *palavra_2, char *palavra_3){
	if((strlen(palavra_1) <= strlen(palavra_2)) && (strlen(palavra_1) <= strlen(palavra_3))){
		return strlen(palavra_1);
	}
	else if((strlen(palavra_2) <= strlen(palavra_1)) && (strlen(palavra_2) <= strlen(palavra_3))){
		return strlen(palavra_2);
	}
	else if((strlen(palavra_3) <= strlen(palavra_1)) && (strlen(palavra_3) <= strlen(palavra_2))){
		return strlen(palavra_3);
	}
}

void maior_PrefixoComum(trie *node) {
	char palavra_1[n], palavra_2[n], palavra_3[n];
	int i, j=0;
	
	printf("Digite a primeira palavra: ");
	scanf(" %s", palavra_1);
	
	printf("Digite a segunda palavra: ");
	scanf(" %s", palavra_2);
	
	printf("Digite a terceira palavra: ");
	scanf(" %s", palavra_3);
	
	char prefixo[menor_Palavra(strlwr(palavra_1),strlwr(palavra_2), strlwr(palavra_3))]; 
	
	if(busca(node, strlwr(palavra_1)) != 0 && busca(node, strlwr(palavra_2)) != 0 && busca(node, strlwr(palavra_3)) != 0){
	
		for(i=0; i < menor_Palavra(strlwr(palavra_1),strlwr(palavra_2), strlwr(palavra_3)); i++){
			if((palavra_1[i] == palavra_2[i]) && (palavra_1[i] == palavra_3[i])){
				prefixo[j] = palavra_1[i];
				j++;
			}
			else {
				break;
			}
		}
		
		if(prefixo[0] == '\0'){
			printf("\n%s, %s, %s: sem prefixo em comum!", strlwr(palavra_1), strlwr(palavra_2), strlwr(palavra_3));
		}else{
			printf("\n%s, %s, %s: %s.", strlwr(palavra_1), strlwr(palavra_2), strlwr(palavra_3), strlwr(prefixo));
		}
	}
	else {
		printf("\nInsira palavras presentes na TRIE!\n\n");
		maior_PrefixoComum(node);
	}
	
}

//3

void palavra_Quebrada(trie *node){
	
	FILE * arqLetra = fopen("letras.txt","r");
	FILE * arqLetraPrint = fopen("letras.txt","r");
	
	char palavra_1[n];
	char palavra_2[n];
	int count=0, aux = 0;
	
	printf("\nDigite a palavra quebrada: ");
	scanf(" %s", palavra_1);
	
	if(arqLetra != NULL) {
		
		while(fscanf(arqLetra,"%s ", palavra_2) != EOF) {
			if(busca(node, strlwr(palavra_2)) != 0){
				if(busca_PalavraQuebrada(strlwr(palavra_1), strlwr(palavra_2)) != NULL)
					count++;
			}		
		}
	}
		
	fclose(arqLetra);
	
	if(arqLetraPrint != NULL && count != 0) {
		printf("\nSim. ");
		while(fscanf(arqLetraPrint,"%s ", palavra_2) != EOF) {
			if(busca(node, palavra_2) != 0){
				
				if(busca_PalavraQuebrada(strlwr(palavra_1), strlwr(palavra_2)) != NULL){
					
					printf("%s",busca_PalavraQuebrada(strlwr(palavra_1), strlwr(palavra_2)));
					
					if(aux < count-1){
						printf(", ");
					}
						
					aux++;
				}
			}		
		}
		printf(".\n");
	} else {
		printf("\nNao.\n");
	}
	
	fclose(arqLetraPrint);
}

char *busca_PalavraQuebrada(char *palavra_1, char *palavra_2){
	
	if(strstr(palavra_1, palavra_2) != NULL)
		return palavra_2;
			
	return NULL;	
}

void limpar(trie **tree){
	free(*tree);
	*tree = novaTrie();
}
