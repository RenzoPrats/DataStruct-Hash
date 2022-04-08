//aluno: Renzo Prats Silva Souza   matricula: 11921ECP004
//arquivo que define o prototipo das funcoes da lista
#ifndef LISTA_H
#define LISTA_H

//Dados
typedef struct No {
  char *chave;
  int dado;
  struct No *prox;
} No;

//funcoes
No* criar_lista();
void destruir_lista(No* p);

No* inserir_lista(No *p, char *chave, int dado);
No* remover_lista(No* p, char *chave);

int buscar_valor(No *p, char *chave, int imprimir);
int imprimir_lista(No *p, int i);
  

#endif