#include <stdio.h>
#include "estruturas.c"
#include "auxiliares.c"

// a presente funcao recebe o nome do arquivo e imprime relatorio na formatacao pedida
void relatorio(char *nome)
{
    // Primeiro abrimos o arquivo e lemos primeiro registro
    Registro *registro_temporario = (Registro*)malloc(sizeof(Registro));
    
    // primeiro abrimos o arquivo e contamos o numero de registros
    FILE *arquivo = fopen(nome, "r");
    int tamanho = tamanho_bytes(arquivo);

    // por fim, pegamos as informacoes e printamos
    for (int offset=0; offset<tamanho; offset+=131)
    {
        le_registro(registro_temporario, arquivo, offset);
        printa_formatado(registro_temporario);
    }

    // por fim, fecha arquivo e libera o registro temporario
    free(registro_temporario);
    fclose(arquivo);
}

int main()
{
    // primeiro recebemos as informacoes que precisamos
    int n;
    char nome[20];
    scanf("%s", nome);
    scanf("%d", &n);
    switch (n)
    {
        case 2:
            relatorio(nome);
    }

    return 0;
}
