#include<stdio.h>
#include<stdlib.h>

typedef struct arvore{
    int info;
    struct arvore *esq;
    struct arvore *dir;
} arvore;

arvore *lerArvore(FILE *arq) {
    arvore *a = NULL;
    char c;
    int num;

    fscanf(arq,"%c",&c);
    fscanf(arq,"%d",&num);
    
    if (num==-1) {
        fscanf(arq,"%c",&c);
        return NULL;
    }
    else {
        a = (arvore*)malloc(sizeof(arvore));
        a->info = num;
        a->esq = lerArvore(arq);
        a->dir = lerArvore(arq);
        fscanf(arq,"%c",&c);
        return a;
    }
}

void imprimirPreOrdem(arvore *a){
    if(a != NULL){
      printf("%d ", a->info);
      imprimirPreOrdem(a->esq);
      imprimirPreOrdem(a->dir);  
    }
}

void imprimirPosOrdem(arvore *a){
    if(a != NULL){
      imprimirPosOrdem(a->esq);
      imprimirPosOrdem(a->dir);
      printf("%d ", a->info);
    }
}

void imprimirEmOrdem(arvore *a){
    if(a != NULL){
      imprimirEmOrdem(a->esq);
      printf("%d ", a->info);
      imprimirEmOrdem(a->dir);
    }
}

int procurarElemento(arvore *a, int x){
    if(a == NULL){
        return 0;
    }
    else if(a->info == x){
        return 1;
    }
    else{
        return procurarElemento(a->esq, x) || procurarElemento(a->dir, x);
    }
}

int contarElementos(arvore *a){
  if(a == NULL){
    return 0;
  }
  else
    return 1 + contarElementos(a->esq) + contarElementos(a->dir);
}

  int main(){

    arvore *a = NULL;
    FILE *arq;
    int option, optionCase2;

  do{
    printf("[1] Ler uma arvore\n[2] Imprimir Arvore\n[3] Verificar Elemento\n[4] Contar numero de elementos da arvore\n[5] Imprimir nos da arvore\n[6] Verificar se uma arvore esta balanceada\n[7] Verificar se uma arvore esta cheia\n[8] Imprimir o nivel de um no X\n[9] Sair\n");  
    scanf("%d", &option);
    switch(option){
      case 1:{
        char nomeArq[50]; 
        printf("Digite o nome do arquivo que deseja ler: ");
        scanf("%s", nomeArq);
        arq = fopen(nomeArq, "r");
        if(arq == NULL) {
          printf("Erro ao abrir arquivo!\n");
          break;
        }
        a = lerArvore(arq);
        
        break;
      }
      case 2:
        printf("[1] Imprimir Pre-Ordem\n[2] Imprimir Em Ordem\n[3] Imprimir Pos Ordem\n[4] Imprimir em Largura\n");
        scanf("%d", &optionCase2);
        switch(optionCase2){
          case 1:
            imprimirPreOrdem(a);
            printf("\n");
            break;
          case 2:
            imprimirEmOrdem(a);
            printf("\n");
            break;
          case 3:
            imprimirPosOrdem(a);
            printf("\n");
            break;
        }
        break;
      case 3:
      {
        int x;
        printf("Digite o elemento que deseja buscar na arvore: ");
        scanf("%d", &x);
        if(procurarElemento(a, x)){
          printf("Elemento %d encontrado!!\n", x);
          break;
        }
        else
          printf("Elemento %d nao encontrado na arvore!!\n", x);
        break;
      }
      case 4:
          {
            int count = contarElementos(a);
            printf("Numero de elementos da arvore: %d\n", count);
          }
        break;
      case 5:

        break;
      case 6:
        break;
      case 7:
        break;
      case 8:
        break;
      case 9:
        printf("Encerrando Programa...\n");
        fclose(arq);
        break;
      default:
        printf("Opcao Invalida!\n");
        break;
    }
    }while(option != 9);


return 0;
}