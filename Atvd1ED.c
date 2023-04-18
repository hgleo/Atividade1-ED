/*
Enunciado:

## Implemente um programa que apresente na tela o seguinte menu de opções

1- Ler uma árvore de um arquivo fornecido pelo usuário
2- Imprimir a árvore (opões: pré-ordem,em-ordem,pós-ordem)
3- Verificar se um elemento x existe na árvor
4- Contar o número de elementos na árvore
5- Imprimir os nós folhas da árvore
6- Verificar se uma árvore está balanceada
7- Verificar se uma árvore é chei
8- Imprimir o nível de um nó x
9- Sair
*/
#include "stdio.h"
#include "stdlib.h"

typedef struct arvore{
  
  int info;
  struct arvore *esq;
  struct arvore *dir;

}arvore;

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

int altura(arvore *a){
  if(a == NULL)
    return 0;

  else{

    int he,hd;
    he = altura(a->esq);
    hd = altura(a->dir);

    if(he>hd)
      return he+1
    else
      return hd+1    
  
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


int main (){

  FILE *arq;
  arvore *a = NULL;

  arq = fopen("Entrada.txt", "r");
  a = lerArvore(arq);
  imprimeNivel(a,0,n);
  fclose(arq);

  return 0;
}