#include<stdio.h>
#include<stdlib.h>

typedef struct arvore{
    int info;
    struct arvore *esq;
    struct arvore *dir;
}arvore;
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
void imprimirNivel(arvore *a, int cont, int n){
  if(a != NULL){
    if(cont == n) 
      printf("%d ", a->info);
    else{
      imprimirNivel(a->esq, cont + 1, n);
      imprimirNivel(a->dir, cont + 1, n);
    }
  }
}
int altura(arvore *a){
  if (a == NULL) return 0;
  else{
    int he = altura(a->esq);
    int hd = altura(a->dir);
    if(he > hd) return he + 1;
    else return hd + 1;
  }
}
void imprimirEmLargura(arvore *a){
  int h = altura(a);
  for(int i = 1; i <= h; i++){
    imprimirNivel(a, 1, i);
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
void imprimirFolhas(arvore *a){
  if(a != NULL){
    if(a->dir == NULL && a->esq == NULL)
      printf("%d ", a->info);
  
  imprimirFolhas(a->esq);
  imprimirFolhas(a->dir);
}
}
int verificarArvoreBalanceada(arvore *a){
    if(a == NULL)
        return 1;

    int he = altura(a->esq);
    int hd = altura(a->dir);

    if(abs(he - hd) <= 1 && verificarArvoreBalanceada(a->esq) && verificarArvoreBalanceada(a->dir) == 1){ //verifica se cada subarvore da direita e da esquerda sao balanceadas && abs é uma função que retorna o valor absoluto 
        return 1;
    }

    return 0;
}
int verificarArvoreCheia(arvore *a){
  if(a == NULL) return 1;

  if(a->esq == NULL && a->dir == NULL) return 1;

  if(a->esq != NULL && a->dir != NULL) return verificarArvoreCheia(a->esq) && verificarArvoreCheia(a->dir); //chega se todas as subarvores tem 2 elementos filhos

  return 0;
}
int nivelDoNo(arvore *a, int x, int nivel){
  if(a == NULL) return -1; //menos 1, porque nesse caso o nivel pode ser 0

  if(a->info == x) return nivel;

  int nivel1 = nivelDoNo(a->esq, x, nivel+1);
  if(nivel1 == -1){ //se nao estiver na esquerda procura na direita
    nivel1 = nivelDoNo(a->dir, x, nivel+1);
  }

  return nivel1;
}
void freeArvore(arvore *a) {
    if (a != NULL) {
        freeArvore(a->esq);
        freeArvore(a->dir);
        free(a);
    }
}
int main(){

    arvore *a = NULL;
    FILE *arq;
    int option, optionCase2;

  do{
    printf("[1] Ler uma arvore\n[2] Imprimir Arvore\n[3] Verificar Elemento\n[4] Contar numero de elementos da arvore\n[5] Imprimir nos folhas da arvore\n[6] Verificar se uma arvore esta balanceada\n[7] Verificar se uma arvore esta cheia\n[8] Imprimir o nivel de um no X\n[9] Sair\n");  
    scanf("%d", &option);
    switch(option){
      case 1:{
        char nomeArq[50]; 
        printf("Digite o nome do arquivo que deseja ler: ");
        scanf("%s", nomeArq);
        arq = fopen(nomeArq, "r");
        if(arq == NULL) {
          printf("Erro ao abrir arquivo!\n\n");
          break;
        }
        a = lerArvore(arq);
        printf("Arvore lida com sucesso!\n");
        fclose(arq);
        break;
      }
      case 2:
        printf("\n[1] Imprimir Pre-Ordem\n[2] Imprimir Em Ordem\n[3] Imprimir Pos Ordem\n[4] Imprimir em Largura\n");
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
          case 4:
            imprimirEmLargura(a);
            printf("\n");
            break;
          default:
            printf("Opção Invalida!\n");
            break;
        }
        break;
      case 3:{
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
      case 4:{
            int count = contarElementos(a);
            printf("Numero de elementos da arvore: %d\n", count);
          }
        break;
      case 5:
        imprimirFolhas(a);
        printf("\n");
        break;
      case 6:
        if(verificarArvoreBalanceada(a) == 1)
          printf("Arvore balanceada!\n");
        else 
          printf("A Arvore nao esta balanceada!\n");
        break;
      case 7:
        if(verificarArvoreCheia(a) == 1)
          printf("Arvore cheia!\n");
        else
          printf("A Arvore nao esta cheia!\n");
        break;
      case 8:
        {int x;
        printf("Digite o no que esta buscando: ");
        scanf("%d", &x);
        printf("Nivel do no %d: %d\n", x, nivelDoNo(a, x, 0));
        break;
        }
      case 9:
        printf("Encerrando Programa...\n");
        break;
      default:
        printf("Opcao Invalida!\n");
        break;
    }
    }while(option != 9);

    freeArvore(a);

    return 0;
  }