//aluno: Renzo Prats Silva Souza   matricula: 11921ECP004
//arquivo que define as funcoes do hash
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"


//cria hash
Hash* criar_hash(int M){
    Hash *p = (Hash*) malloc(sizeof(Hash));
    p->vetor = (No**) malloc(M * sizeof(No**));
    int i;
    for(i=0; i<M; i++){
        p->vetor[i] = criar_lista();
    }
    p->M = M;
    return p;
}

//destroi hash
void destruir_hash(Hash **p){
    for(int i=0;i<(*p)->M;i++){
        destruir_lista((*p)->vetor[i]);
    } 
    free((*p)->vetor);
    free(*p);
    *p = NULL;
}

//faz o hashing
int hashing(int decimal, int M) {
    int n = 0;
    n = decimal % M;
    return n;
}

//insere hash
void inserir_hash(Hash *p, char *chave, int dado, int decimal) {
    int n = hashing(decimal, p->M);
    p->vetor[n] = inserir_lista(p->vetor[n], chave, dado);
}

//remove hash
int remover_hash(Hash *p, char *chave, int decimal) {
    int n = hashing(decimal, p->M);

    //faz uma busca antes para ver se o elemento a ser removido existe
    int tem_valor = buscar_valor(p->vetor[n], chave, 0);
    if(tem_valor != -1){
        //caso exista ai sim remove o elemento
        p->vetor[n] = remover_lista(p->vetor[n], chave);
    }
    //retorna -1 caso nao exista o elemento, caso exista retornara o seu valor
    return tem_valor;
}

//busca hash
int buscar_hash(Hash *p, char *chave, int decimal, int imprimir){//retorna -1 se nao encontrou  
    int n = hashing(decimal, p->M);
    return buscar_valor(p->vetor[n], chave, imprimir);//retorna valor (chave, valor)
}

//imprime hash
void imprimir_hash(Hash *p){    
    int i;
    for(i=0; i<p->M; i++){
        imprimir_lista(p->vetor[i], i);
    }
}