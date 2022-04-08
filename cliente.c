//aluno: Renzo Prats Silva Souza   matricula: 11921ECP004
//arquivo com a funcao main
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash.h"

//funcao que transforma uma letra em um numero binario
void binario(int n, char **valores_binarios, int indice, int *aux);

//funcao auxiliar que ira chamar a funcao binario para transformar cada letra do nome num numero binario
void transformar_binario(char *nome, char **valores_binarios);

//funcao que faz o XOR bit-a-bit com as letras do nome que esta em binario e no fim transforma para decimal 
int xor_bit(char **valores_binarios, int tam_nome);

//funcao que eleva um numero, similiar a funcao pow
int elevar(int base, int expoente);

int main(){
    //declarando os vetores ordem e nome, e outras variaveis que serao utilizadas
    char *ordem = (char *) malloc(9 * sizeof(char));
    char *nome = (char *) malloc(200 * sizeof(char));
    int RA;
    int qt = 0;
    int *quantidade_alunos = &qt;

    //criando Hash de tamanho 13 conforme especificado
    Hash *p = criar_hash(13);

    //enquanto a ordem for diferente de sair    
    while (scanf("%s", ordem) && strcmp(ordem, "sair") != 0) {
        
        //se a ordem for igual insere
        if (strcmp(ordem, "insere") == 0) {
            //recebemos o RA e o nome do alino
            scanf("%d", &RA);
            scanf(" %[^\n]", nome);
            printf("Insere: %d %s\n", RA, nome);
            
            int tam_nome = strlen(nome);

            //criamos uma matriz chamada valores_binarios que tera o valor binario de cada letra do nome
            char **valores_binarios = (char **) malloc(sizeof(char*) * tam_nome);
            int v;

            //inicializando cada letra do nome o valor binario 00000000
            for(int i = 0; i < tam_nome; i++){
                valores_binarios[i] = (char*) malloc(9 * sizeof(char));
                strcpy(valores_binarios[i], "00000000");
            }
            //transformando o nome em valores binario
            transformar_binario(nome, valores_binarios);
            
            //realizando o xor e transformando para decimal
            v = xor_bit(valores_binarios, tam_nome);

            //verifica se o aluno ja esta no hash
            int achou_hash = buscar_hash(p, nome, v, 0);
            
            //caso estiver printa nome repetido
            if(achou_hash != -1){
                printf("Nome repetido: %s\n", nome);
            }else{
                //caso nao estiver, adiciona e aumenta a quantidade de alunos
                inserir_hash(p, nome, RA, v);
                (*quantidade_alunos)++;
            }

            //desaloca a matriz valores_binarios
            for(int i = 0; i < tam_nome; i++){
                free(valores_binarios[i]);
            }
            free(valores_binarios);
                        
        
        //caso a ordem seja remove
        }else if(strcmp(ordem, "remove") == 0){
            //recebe o nome do aluno
            scanf(" %[^\n]", nome);
            printf("Remove: %s\n", nome);
            
            int tam_nome = strlen(nome);

            //criamos uma matriz chamada valores_binarios que tera o valor binario de cada letra do nome
            char **valores_binarios = (char **) malloc(sizeof(char*) * tam_nome);
            int v;

            //inicializando cada letra do nome o valor binario 00000000
            for(int i = 0; i < tam_nome; i++){
                valores_binarios[i] = (char*) malloc(9 * sizeof(char));
                strcpy(valores_binarios[i], "00000000");
            }
            //transformando o nome em valores binario
            transformar_binario(nome, valores_binarios);
            
            //realizando o xor e transformando para decimal
            v = xor_bit(valores_binarios, tam_nome);

            //chama a funcao remove_hash que removera o aluno caso tenha, caso nao tenha retornara -1
            int remove = remover_hash(p, nome, v);
            if(remove != -1){
                (*quantidade_alunos)--;
            }else{
                printf("Nome inexistente: %s\n", nome);
            }

            //desalocando a matriz valores_binarios
            for(int i = 0; i < tam_nome; i++){
                free(valores_binarios[i]);
            }
            free(valores_binarios);        
        
        //caso a ordem seja consulta
        }else if(strcmp(ordem, "consulta") == 0){
            //recebe o nome do aluno
            scanf(" %[^\n]", nome);
            printf("Consulta: %s\n", nome);
            
            int tam_nome = strlen(nome);

            //criamos uma matriz chamada valores_binarios que tera o valor binario de cada letra do nome
            char **valores_binarios = (char **) malloc(sizeof(char*) * tam_nome);
            int v;

            //inicializando cada letra do nome o valor binario 00000000
            for(int i = 0; i < tam_nome; i++){
                valores_binarios[i] = (char*) malloc(9 * sizeof(char));
                strcpy(valores_binarios[i], "00000000");
            }
            //transformando o nome em valores binario
            transformar_binario(nome, valores_binarios);
            
            //realizando o xor e transformando para decimal
            v = xor_bit(valores_binarios, tam_nome);

            //busca o elemento na hash, caso exista retornara o dado do elemento, caso contrario -1
            int busca = buscar_hash(p, nome, v, 1);
            if(busca == -1){
                printf("Nome inexistente: %s\n", nome);
            }

            //desalocando a matriz valores_binarios
            for(int i = 0; i < tam_nome; i++){
                free(valores_binarios[i]);
            }
            free(valores_binarios);        
        
        //caso a ordem seja imprime
        }else if(strcmp(ordem, "imprime") == 0){
            printf("\n");
            //imprime a quantidade de alunos
            printf("Imprime Tabela: %d aluno(s):\n", *quantidade_alunos);
            //imprime o hash
            imprimir_hash(p);
            printf("\n");
        }
    }
    //desalocando o hash, e os vetores ordem e nome
    destruir_hash(&p);
    free(ordem);
    free(nome);
    return 0;
}


//transforma um numero decimal em um numero binario
void binario(int n, char **valores_binarios, int indice, int *aux){
    if(n == 0){
        valores_binarios[indice][*aux] = '0';
    }else{
        binario(n/2, valores_binarios, indice, aux);
        (*aux)++;
        char charValue = (n % 2) +'0';
        valores_binarios[indice][*aux] = charValue;
        
    }
}

//funcao auxiliar que ira chamar a funcao binario para transformar cada letra do nome num numero binario
//recebe o nome, e a matriz valores_binarios onde cada linha representa o numero binario de uma letra do nome
void transformar_binario(char *nome, char **valores_binarios){
    int v1 = 0;
    int *aux = &v1;
    int tamanho_nome = strlen(nome);
    for(int j = 0; j < tamanho_nome; j++){
        int num = nome[j];
        //caso o caractere transformado para int seja menor que 64, isso significa que ele tera 6 bits
        //entao devemos definir o aux em 1 para que o numero binario fique ajustado corretamente no vetor
        if(num < 64){
            *aux = 1;
        }else{
            *aux = 0;
        }
        //chama a funcao binaria passando cada letra do nome
        binario(nome[j], valores_binarios, j, aux);
    }
}

//funcao que faz o xor bit-a-bit e depois transforma para decimal
//recebe a matriz valores_binarios e o tam nome
int xor_bit(char **valores_binarios, int tam_nome){
    int k = 0;
    char resultado = '0';
    char *bit_final = (char*) malloc(9 * sizeof(char));

    int z = 0;
    int val = 0; 
    
    //para cada numero binario
    for(int i = 0; i < 8; i++){
        //para cada "letra" no nome
        for(int j = 0; j < tam_nome; j++){
            
            //se for a primeira "letra" de cada nome
            if(j == 0){
                //resultado vai ser o proprio inicio
                resultado = valores_binarios[j][i];
            }else{
                //faz o XOR, caso valores_binarios[j][i] seja igual ao resultado, o resultado sera 0
                //caso seja diferente o resultado sera 1
                if(valores_binarios[j][i] == resultado){
                    resultado = '0';

                }else{
                    resultado = '1';
                }
            }
        }
        //o bit final sera o resultado final do XOR de cada "letra" do nome
        bit_final[k] = resultado;
        k++;
    }
    //transforma o numero binario em um numero decimal
    for(int u = 7; u >= 0; u--){
        int number = bit_final[u] - '0';
        val = val + (elevar(2, z) * number);
        z++;
    }
    free(bit_final);
    return val;
}

//funcao que eleva um numero
int elevar(int base, int expoente){
    if(expoente == 0)
        return 1;
    else
        return (base * elevar(base, expoente-1));
}