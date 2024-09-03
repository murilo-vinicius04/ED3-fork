#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

// o presente struct representa o registro de animais marinhos do arquivo
struct {
    int especie;
    char nome[41];
    char nome_cientifico[61];
    int populacao;
    char status[9];
    float localizacao[2];
    int impacto_humano;
} Registro;

#endif
