#ifndef ESTRUTURAS
#define ESTRUTURAS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// o presente struct representa o registro de animais marinhos do arquivo
typedef struct
{
    int especie;
    char nome[41];
    char nome_cientifico[61];
    int populacao;
    char status[9];
    float localizacao[2];
    int impacto_humano;
} Registro;

// essa funcao recebe o ponteiro de um arquivo, o byte offset do registro,
// e o ponteiro do registro que salvara os dados
// a seguinte funcao le o registro com byteoffset do arquivo
void le_registro(Registro *registro, FILE *arquivo, int offset)
{
    // arruma o ponteiro para o inicio do registro e le os valores
    fseek(arquivo, offset, SEEK_SET);
    fread(&registro->especie, 4, 1, arquivo);
    fread(registro->nome, 1, 41, arquivo);
    fread(registro->nome_cientifico, 1, 61, arquivo);
    fread(&registro->populacao, 4, 1, arquivo);
    fread(registro->status, 1, 9, arquivo);
    fread(registro->localizacao, 4, 2, arquivo);
    fread(&registro->impacto_humano, 4, 1, arquivo);
}

// a seguinte funcao recebe um registro e printa suas informacoes de forma formatada
void printa_formatado(Registro *registro)
{
    printf("ID: %d\n", registro->especie);
    printf("Nome: %s\n", registro->nome);
    printf("Nome Científico: %s\n", registro->nome_cientifico);
    printf("População: %d\n", registro->populacao);
    printf("Status: %s\n", registro->status);
    printf("Localização: (%.2f, %.2f)\n", registro->localizacao[0], registro->localizacao[1]);
    printf("Impacto Humano: %d\n", registro->impacto_humano);
}
int busca_por_id(int id, FILE *arquivo)
{
    int id_cmp = 0, tamanho = tamanho_bytes(arquivo);

    for (int i = 0; i < tamanho; i += 131)
    {
        fseek(arquivo, i, SEEK_SET);
        fread(&id_cmp, sizeof(int), 1, arquivo);

        if (id_cmp == id)
        {
            return i;
        }
    }

    return -1;
}

void preenche_string(char *string, size_t tamanho)
{
    size_t len = strlen(string);

    if (len < tamanho - 1)
    {
        string[len] = '\0';
    }

    for (size_t i = len + 1; i < tamanho; i++)
    {
        string[i] = '$';
    }
}

void limpa_campo(char *campo, size_t tamanho)
{
    for (size_t i = 0; i < tamanho; i++)
    {
        if (campo[i] == '$')
        {
            campo[i] = '\0';
            break;
        }
    }
}

#endif
