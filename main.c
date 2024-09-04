#include <stdio.h>
#include "estruturas.c"
#include "auxiliares.c"

// a presente funcao recebe o nome do arquivo e imprime relatorio na formatacao pedida
void relatorio(FILE *arquivo)
{
    // Primeiro abrimos o arquivo e lemos primeiro registro
    Registro *registro_temporario = (Registro*)malloc(sizeof(Registro));
    
    // primeiro abrimos o arquivo e contamos o numero de registros
    int tamanho = tamanho_bytes(arquivo);

    // por fim, pegamos as informacoes e printamos
    for (int offset=0; offset<tamanho; offset+=131)
    {
        le_registro(registro_temporario, arquivo, offset);
        printa_formatado(registro_temporario);
    }

    // por fim libera o registro temporario
    free(registro_temporario);
}

// busca registro a partir do RRN que tambem vamos pedir, a base de dados eh dado pelo
// string nome
void busca(FILE *arquivo)
{
    // Primeiro criamos um registro e abrimos o arquivo
    Registro *registro = (Registro*)malloc(sizeof(Registro));

    // entao pedimos o RRN e calculamos o byteoffset
    unsigned offset, rrn;
    unsigned tamanho_registro = 4+41+61+4+9+8+4;
    scanf("%u", &rrn);
    offset = rrn*tamanho_registro;

    // precisamos checar se o rrn existe, caso nao retornar erro
    unsigned ultimo_offset = tamanho_bytes(arquivo) - tamanho_registro;
    if (offset > ultimo_offset)
    {
        printf("Espécie não encontrada\n");
        return;
    }

    // por fim lemos o registro e printamos ele na tela
    le_registro(registro, arquivo, offset);
    printa_formatado(registro);

    // libera o registro
    free(registro);
}

int main()
{
    // primeiro recebemos as informacoes que precisamos
    int n;
    char nome[20];
    scanf("%d %s", &n, nome);

    // busca o arquivo
    FILE *arquivo = fopen(nome, "r+");
    if (arquivo == NULL)
    {
        printf("Falha no processamento do arquivo\n");
        return 1;
    }

    // executa funcionalidade desejada
    switch (n)
    {
        case 2:
            relatorio(arquivo);
            break;
        case 3:
            busca(arquivo);
            break;
    }

    // fecha o arquivo
    fclose(arquivo);

    return 0;
}
