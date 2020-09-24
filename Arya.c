#include <stdio.h>
#include <stdlib.h>
typedef struct aux{
	int chave;
	struct aux* prox;
}Ele;
typedef Ele* Pont; 
void insere(Pont* l, int p){
	Pont temp = (Pont)malloc(sizeof(Ele));
	temp->prox = NULL;
	temp->chave = p;
	if(*l == NULL)
		*l = temp;	
	else{
		Pont pon = *l;
		while(pon->prox != NULL)
			pon = pon->prox;
		pon->prox = temp;
	}
}
void insereP(Pont l, int p, int e){
	Pont temp = (Pont)malloc(sizeof(Ele));
	temp->prox = NULL;
	temp->chave = p;
	while(l->chave != e){
		l = l->prox;
	}
	temp->prox = l->prox;
	l->prox = temp;
}
void removeP(Pont l, int p){
	Pont temp, ant = NULL;
	while(l->chave != p){
		ant = l;
		l = l->prox;
	}
	if(ant == NULL){
		temp = l;
		l = l->prox;
	}else{
		ant->prox = l->prox;
	}	temp = l;
	free(temp);
}
int numInimigosAB(Pont l, int a, int b){
	int cont = 0;
	while(l->chave != a && l->chave != b){
		l = l->prox;		
	}
	int v = (l->chave == a) ? b : a;
	l = l->prox;
	while(l->chave != v){
		cont++;
		l = l->prox;		
	}
	return cont;
}
void imprimeLista(Pont l){
	while(l != NULL){
		printf("%d ", l->chave);
		l = l->prox;
	}
	
}
int main(){
	int n, i, a;
	char c; 
	scanf("%d", &n);
	Pont l = NULL;
	for(i = 0; i < n; i++){
		scanf("%d", &a);
		insere(&l, a);
	}
	while(scanf("%c", &c) && c != 'F'){
		int x,y;
		if(c == 'I'){
			scanf("%d %d", &x, &y);
			n++;
			insereP(l, x, y);
			printf("inserido %d\n", x);
		}else if(c == 'R'){
			scanf("%d", &x);
			n--;
			removeP(l, x);
			printf("removido %d\n", x);
		}else if(c == 'C'){
			scanf("%d %d", &x, &y);
			printf("quantidade %d\n", numInimigosAB(l, x, y));
		}else if(c == 'M'){
			if(n == 0)
				printf("lista vazia\n");			
			else{
				printf("lista ");
				imprimeLista(l);
				printf("\n");
			}
							
		}
		
	}
		printf("fim\n");
	
	return 0;
}
