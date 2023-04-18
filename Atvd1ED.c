/*
Enunciado:

## Implemente um programa que apresente na tela o seguinte menu de opções

1- Ler uma árvore de um arquivo fornecido pelo usuário      ok
2- Imprimir a árvore (opões: pré-ordem ,em-ordem,pós-ordem) ok
3- Verificar se um elemento x existe na árvor               ok
4- Contar o número de elementos na árvore 
5- Imprimir os nós folhas da árvore
6- Verificar se uma árvore está balanceada
7- Verificar se uma árvore é cheio
8- Imprimir o nível de um nó x                               ok
9- Sair
*/
#include "stdio.h" 
#include "stdlib.h"

typedef struct arvore{
  
  int info;
  struct arvore *esq;
  struct arvore *dir;

}arvore;

int existeElemento(arvore *a, int x){

  if(a ==NULL)
    return 0;
  
  else if(a->info == x)
    return 1;
  
  else{
    int ret = existeElemento(a->esq,x);
    if(ret == 1)
      return 1;
    return existeElemento(a->dir,x);
  }
}

arvore *lerArvore(FILE *arq){
    
  arvore *a = NULL;
  char c;
  int num; 

  fscanf(arq,"%c",&c);
  fscanf(arq,"%d",&num);

  if(num == -1){
    fscanf(arq,"%c",&c);
    return NULL;
  }
  else{
    a = (arvore*)malloc(sizeof(arvore));
    a->info = num;
    a->esq = lerArvore(arq);
    a->dir = lerArvore(arq);
    fscanf(arq,"%c",&c);
    return a;
  }
}

void imprimePreOrdem(arvore* a){

  if(a != NULL){
    printf("%d", a->info);
    imprimePreOrdem(a->esq);
    imprimePreOrdem(a->dir);
  }
}

void imprimeEmOrdem(arvore* a){

  if(a != NULL){
    imprimePreOrdem(a->esq);
    printf("%d", a->info);    
    imprimePreOrdem(a->dir);
  }
}

void imprimePosOrdem(arvore* a){

  if(a != NULL){
    imprimePreOrdem(a->esq);
    imprimePreOrdem(a->dir);
    printf("%d", a->info);

  }
}

int altura(arvore *a){

  if(a == NULL)
    return 0;

  else{

    int he,hd;
    he = altura(a->esq);
    hd = altura(a->dir);

    if(he>hd)
      return he+1;
    else
      return hd+1;  
  
  }
}

void imprimeNivel(arvore *a,int cont, int nivel){

 if(a != NULL){
   if(cont == nivel){
     printf("%d",a->info);     
   }
   else{
     imprimeNivel(a->esq,cont+1,nivel); // subesq
     imprimeNivel(a->dir,cont+1,nivel); // subdir
   }
 } 
}

void menu(int option,arvore* a){
  int x;
  printf("Escolha uma das seguintes opcoes:\n[1] Ler uma arvore de um arquivo fornecido pelo usuário\n[2] Imprimir a arvore por pre-ordem/n[3] Imprimir a arvore em ordem\n[4]Imprimir a arvore por pos-ordem/n[5] Verificar se um elemento X existe na arvore\n[6] Contar o numero de elementos de uma arvore\n[7] Imprimir os nos das folhas da arvore\n[8] Verificar se uma arvore esta balanceada\n[9] Verificar se uma arvore e cheia\n[10] Imprimir o nivel de um no X\n [11] Sair");
  do{
  switch(option){
    case 1:
      lerArvore(a);
      break;
    case 2:
      imprimePreOrdem(a);
      break;
    case 3:
      imprimeEmOrdem(a);
      break;
    case 4:
      imprimePosOrdem(a);
      break;
    case 5:
      printf("Qual elemento deseja procurar?");
      scanf("%d", &x);
      existeElemento(a, x);
      break;
    case 6:
      break;
    case 7:
      break;
    case 8:
      break;
    case 9:
      break;
    case 10:
      break;
    case 11:
      printf("Encerrando...");
      break;
  }
  } while(option != 11);
} 

int main (){

  FILE *arq;
  arvore *a = NULL;
  int option,n;
  arq = fopen("Entrada.txt", "r");
  menu(option,a);
  a = lerArvore(arq);
  imprimeNivel(a,0,n);
  fclose(arq);

  return 0;
}