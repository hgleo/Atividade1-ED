#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

int main() {
    arvore *a = NULL;
    FILE *arq = NULL;
    int option, optionCase2, x;
    char nomeArq[50]; 

    do {
        printf("[1] Ler uma arvore\n[2] Imprimir Arvore\n[3] Verificar Elemento\n[4] Contar numero de elementos da arvore\n[5] Imprimir nos da arvore\n[6] Verificar se uma arvore esta balanceada\n[7] Verificar se uma arvore esta cheia\n[8] Imprimir o nivel de um no X\n[9] Sair\n");  
        scanf("%d", &option);
        switch(option) {
            case 1:
                
                printf("Digite o nome do arquivo que deseja ler: ");
                scanf("%s", nomeArq);
                arq = fopen(nomeArq, "r");
                if(arq == NULL) {
                    printf("Erro ao abrir arquivo!\n");
                    break;
                }
                a = lerArvore(arq);
                fclose(arq);
                break;
            case 2:
                if (a == NULL) {
                    printf("Arvore nao carregada!\n");
                    break;
                }
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
                    default:
                        printf("Opcao Invalida!\n");
                        break;
                }
                break;
            case 3:
                if (a == NULL) {
                    printf("Arvore nao carregada!\n");
                    break;
                }
                printf("Digite o elemento que deseja buscar na arvore: ");
                scanf("%d", &x);
                if(procurarElemento(a, x)){
                    printf("Elemento %d encontrado!!\n", x);
                } else {
                    printf("Elemento %d nao encontrado na arvore!!\n", x);
                }
                break;
            case 4:
                if (a == NULL) {
                    printf("Arvore nao carregada!\n");
                    break;
                }
                printf("Numero de elementos da arvore: %d\n", contarElementos(a));
                break;
            case 5:
                // implementar
                break;
            case 6:
                // implementar
                break;
            case 7:
                // implementar
                break;
            case 8:
                // implementar
                break;
            case 9:
                printf("Encerrando Programa...\n");
                if (a != NULL) {
                    free(a);
                }
                break;
            default:
                printf("Opcao Invalida!\n");
                break;
        }
    } while(option != 9);

    return 0;
}
