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
    for (int i = 0; i < tamanho; i++)
    {
        if (str[i] != '$')
            tamanho_real++;
        else
            break;
    }

    // por fim, copia string real
    char *str_real = (char *)malloc(tamanho_real * sizeof(char));
    for (int i = 0; i < tamanho_real; i++)
        str_real[i] = str[i];

    return str_real;
}

// recebe o ponteiro de um arquivo e le quantos bytes ele possui
int tamanho_bytes(FILE *arquivo)
{
    fseek(arquivo, 0, SEEK_END);
    return ftell(arquivo);
}

void readline(char *string)
{
    char c = 0;

    do
    {
        c = (char)getchar();
    } while (c == '\n' || c == '\r');

    int i = 0;

    do
    {
        string[i] = c;
        i++;
        c = getchar();
    } while (c != '\n' && c != '\r');

    string[i] = '\0';
}

void binarioNaTela(char *nomeArquivoBinario)
{ /* Você não precisa entender o código dessa função. */
    unsigned long i, cs;
    unsigned char *mb;
    size_t fl;
    FILE *fs;
    if (nomeArquivoBinario == NULL || !(fs = fopen(nomeArquivoBinario, "rb")))
    {
        fprintf(stderr, "ERRO AO ESCREVER O BINARIO NA TELA (função binarioNaTela): não foi possível abrir o arquivo que me passou para leitura. Ele existe e você tá passando o nome certo? Você lembrou de fechar ele com fclose depois de usar?\n");
        return;
    }
    fseek(fs, 0, SEEK_END);
    fl = ftell(fs);
    fseek(fs, 0, SEEK_SET);
    mb = (unsigned char *)malloc(fl);
    fread(mb, 1, fl, fs);

    cs = 0;
    for (i = 0; i < fl; i++)
    {
        cs += (unsigned long)mb[i];
    }
    printf("%lf\n", (cs / (double)100));
    free(mb);
    fclose(fs);
}

#endif
