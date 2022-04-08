//aluno: Renzo Prats Silva Souza   matricula: 11921ECP004
//arquivo que define o prototipo das funcoes do hash
#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include "lista.h"

//Dados
typedef struct {
    No **vetor;
    int M; //tamanho do vetor
} Hash;

//Funcoes
Hash* criar_hash(int M);
void destruir_hash(Hash **p);

void inserir_hash(Hash *p, char *chave, int dado, int decimal);
int remover_hash(Hash *p, char *chave, int decimal); //retorna -1 se nao encontrou o elemento que deveria ser removido

int buscar_hash(Hash *p, char *chave, int decimal, int imprimir);//retorna -1 se nao encontrou
void imprimir_hash(Hash *p);

#endif