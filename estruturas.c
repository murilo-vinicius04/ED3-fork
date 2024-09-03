#ifndef ESTRUTURAS_C
#define ESTRUTURAS_C

#include <stdio.h>
#include "estruturas.h"

struct Registro *le_registro(FILE *arquivo, int offset)
{
    struct Registro *registro;
    fseek(arquivo, offset, SEEK_SET);
    fread(registro->especie, 4, 1, arquivo);
    fread(registro->nome, 41, 1, arquivo);
    fread(registro->nome_cientifico, 61, 1, arquivo);
    fread(registro->populacao, 4, 1, arquivo);
    fread(registro->status, 9, 1, arquivo);
    fread(registro->localizacao, 8, 1, arquivo);
    fread(registro->localizacao, 8, 1, arquivo);

    return registro;
}

#endif
