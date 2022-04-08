//aluno: Renzo Prats Silva Souza   matricula: 11921ECP004 
//arquivo com as funcoes da lista
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

//cria lista
No* criar_lista(){
  return NULL;
}

//destroi lista
void destruir_lista(No* p) {
    if (p != NULL) {
        destruir_lista(p->prox);
        free(p->chave);
        free(p);
    }
}

//insere na lista
No* inserir_lista(No *p, char *chave, int dado) {
    //cria um No novo, seta chave e dado
    No *novo = malloc(1 * sizeof(No));

    novo->chave = (char*) malloc( (strlen(chave) + 1) * sizeof(char) );
    
    strcpy(novo->chave, chave);
    novo->dado = dado;
    
    //declarando os nos aux, aux2 e o int maior_algum que identificara se o novo no vai estar no comeco da lista
    No *aux = p;
    No *aux2;
    int maior_algum = 0;

    //enquanto o no aux for diferente de null
    while(aux != NULL){
        //faz a comparacao lexicografica para ver se o novo->chave eh menor ou maior que o no atual
        if(strcmp(novo->chave, aux->chave) >= 0){
            //caso for maior o aux2 sera o aux, visto que o aux2 sempre aponta para o anterior do atual que estamos comparando
            aux2 = aux;
            //o no aux passa a ser o proximo
            aux = aux->prox;
            //maior_algum passa a ser 1 o que identifica que o novo no nao estara no comeco da lista
            maior_algum = 1;
        }else{
            //caso o novo->chave seja menor que o no atual, isso significa que ele deve ficar antes do no atual, entao podemos dar break
            break;
        }
    }
    //caso maior_algum seja igual a zero eh porque devemos inserir o novo noh no comeco
    if (maior_algum == 0){
        //o proximo do novo no eh o aux
        novo->prox = aux;
        //retorna o comeco da lista que no caso sera representado por novo, ja que o novo no foi adicionado no comeco
        return novo;
    //caso contrario poderemos adicionar o novo no em alguma posicao depois do comeco
    }else{
        //o proximo do anterior do no atual eh o novo no
        aux2->prox = novo;
        //o proximo do novo no eh o no atual
        novo->prox = aux;
    }
    //retorna o comeco da lista que no caso sera representado por p
    return p;
}

//remove da lista
No* remover_lista(No* p, char *chave){
    No *proximo;
    if (p == NULL)
        return NULL;
    else if (strcmp(p->chave,chave)==0) {
        proximo = p->prox;
        free(p->chave);
        free(p);
        return proximo;
    }else {
        p->prox = remover_lista(p->prox, chave);
        return p;
    }
}

//busca valor na lista
int buscar_valor(No *p, char *chave, int imprimir) {
    //enquanto a lista tiver elementos
    while(p != NULL){
        //caso o elemento->chave for igual a chave que buscamos
        if (strcmp(p->chave, chave) == 0){
            //se essa busca necessitar imprimir
            if(imprimir == 1){
                printf("%d %s\n", p->dado, p->chave);
            }
            //retorna o dado achado
            return p->dado;
        }
        p = p->prox;
    }
    //retorna -1 simbolizando que nao achou o dado
    return -1;
}

//imprime a lista
int imprimir_lista(No *p, int i) {
    while(p != NULL){
        printf("(%d) %d %s\n", i, p->dado, p->chave);
        p = p->prox;
    }
    return 0;
}