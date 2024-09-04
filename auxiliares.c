#ifndef AUXILIARES
#define AUXILIARES

#include <stdlib.h>
#include <stdio.h>

// Esse modulo possui as funcoes auxiliares, ou seja
// tanto aquelas que nao sao metodos do registro, tampouco
// as funces que precisam ser implementadas de fato

// a presente funcao recebe o ponteiro de um string e seu tamanho
// retorna o mesmo string sem os lixos que sao o caracter "$"
char *limpa(char *str, int tamanho)
{
    // vamos medir quando o string de fato termina e depois copiar
    // os caracteres ate o tamanho real
    int tamanho_real;

    // agora precisamos descobrir quando comeca o lixo
    for (int i=0; i<tamanho; i++)
    {
        if (str[i] != '$')
            tamanho_real++;
        else
            break;
    }

    // por fim, copia string real
    char *str_real = (char*)malloc(tamanho_real*sizeof(char));
    for (int i=0; i<tamanho_real; i++) str_real[i] = str[i];

    return str_real;
}

// recebe o ponteiro de um arquivo e le quantos bytes ele possui
int tamanho_bytes(FILE *arquivo)
{
    fseek(arquivo, 0, SEEK_END);
    return ftell(arquivo);
}

#endif 
