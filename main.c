#include <stdio.h>
#include "estruturas.c"
#include "auxiliares.c"

// a presente funcao recebe o nome do arquivo e imprime relatorio na formatacao pedida
void relatorio(FILE *arquivo)
{
    // Primeiro abrimos o arquivo e lemos primeiro registro
    Registro *registro_temporario = (Registro *)malloc(sizeof(Registro));

    // primeiro abrimos o arquivo e contamos o numero de registros
    int tamanho = tamanho_bytes(arquivo);

    // por fim, pegamos as informacoes e printamos
    for (int offset = 0; offset < tamanho; offset += 131)
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
    Registro *registro = (Registro *)malloc(sizeof(Registro));

    // entao pedimos o RRN e calculamos o byteoffset
    unsigned offset, rrn;
    unsigned tamanho_registro = 4 + 41 + 61 + 4 + 9 + 8 + 4;
    scanf("%u", &rrn);
    offset = rrn * tamanho_registro;

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
void registra_especie(FILE *arquivo)
{
    int qtd_registros;
    scanf("%d", &qtd_registros);

    for (int i = 0; i < qtd_registros; i++)
    {
        Registro *registro = calloc(1, sizeof(Registro));
        registro->impacto_humano = 0;
        registro->populacao = 0;
        int id_cmp = 0;
        int id_existente = 0;

        scanf("%d", &registro->especie);

        for (int j = 0; j < tamanho_bytes(arquivo); j += 131)
        {
            fseek(arquivo, j, SEEK_SET);
            fread(&id_cmp, sizeof(int), 1, arquivo);
            if (registro->especie == id_cmp)
            {
                id_existente = 1;
                break;
            }
        }

        getchar();

        readline(registro->nome);
        preenche_string(registro->nome, sizeof(registro->nome));

        readline(registro->nome_cientifico);
        preenche_string(registro->nome_cientifico, sizeof(registro->nome_cientifico));

        scanf("%d", &registro->populacao);
        getchar(); // Limpa o '\n'

        readline(registro->status);
        preenche_string(registro->status, sizeof(registro->status));

        scanf("%f", &registro->localizacao[0]);
        scanf("%f", &registro->localizacao[1]);

        registro->localizacao[0] = ((int)(registro->localizacao[0] * 100 + 0.5)) / 100.0;
        registro->localizacao[1] = ((int)(registro->localizacao[1] * 100 + 0.5)) / 100.0;

        scanf("%d", &registro->impacto_humano);

        if (id_existente)
        {
            free(registro);
            continue;
        }

        fseek(arquivo, 0, SEEK_END);
        fwrite(&registro->especie, sizeof(int), 1, arquivo);
        fwrite(registro->nome, sizeof(registro->nome), 1, arquivo);
        fwrite(registro->nome_cientifico, sizeof(registro->nome_cientifico), 1, arquivo);
        fwrite(&registro->populacao, sizeof(int), 1, arquivo);
        fwrite(registro->status, sizeof(registro->status), 1, arquivo);
        fwrite(&registro->localizacao, sizeof(float), 2, arquivo);
        fwrite(&registro->impacto_humano, sizeof(int), 1, arquivo);

        free(registro);
    }
}

void registra_informacao(FILE *arquivo)
{
    Registro *registro = calloc(1, sizeof(Registro));

    int id, qtd_informacoes;
    char dado_adicionado[20];

    scanf("%d", &id);

    int offset = busca_por_id(id, arquivo);

    if (offset == -1)
    {
        printf("Espécie não encontrada\n");
        free(registro);
        return;
    }

    le_registro(registro, arquivo, offset);

    limpa_campo(registro->status, sizeof(registro->status));

    scanf("%d", &qtd_informacoes);
    getchar();

    for (int i = 0; i < qtd_informacoes; i++)
    {

        readline(dado_adicionado);

        if (strcmp(dado_adicionado, "HUMAN IMPACT") == 0)
        {
            if (registro->impacto_humano != 0)
            {
                printf("Informação já inserida no arquivo\n");
                free(registro);
                return;
            }

            scanf("%d", &registro->impacto_humano);
            getchar();

            if (registro->impacto_humano == 0)
            {
                registro->impacto_humano = 0;
            }

            fseek(arquivo, offset + 127, SEEK_SET);
            fwrite(&registro->impacto_humano, sizeof(registro->impacto_humano), 1, arquivo);
        }

        if (strcmp(dado_adicionado, "POPULATION") == 0)
        {
            if (registro->populacao != 0)
            {
                printf("Informação já inserida no arquivo\n");
                free(registro);
                return;
            }

            scanf("%d", &registro->populacao);
            getchar();

            if (registro->populacao == 0)
            {
                registro->populacao = 0;
            }

            fseek(arquivo, offset + 106, SEEK_SET);
            fwrite(&registro->populacao, sizeof(registro->populacao), 1, arquivo);
        }

        if (strcmp(dado_adicionado, "STATUS") == 0)
        {

            limpa_campo(registro->status, sizeof(registro->status));

            if (strcmp(registro->status, "NULO") != 0)
            {
                printf("Informação já inserida no arquivo\n");
            }
            readline(registro->status);

            preenche_string(registro->status, sizeof(registro->status));

            fseek(arquivo, offset + 110, SEEK_SET);
            fwrite(registro->status, sizeof(registro->status), 1, arquivo);
        }
    }

    free(registro);
}

int main()
{
    // primeiro recebemos as informacoes que precisamos
    int n;
    char nome[20];
    scanf("%d %s", &n, nome);

    // busca o arquivo
    FILE *arquivo = fopen(nome, "rb+");
    if (arquivo == NULL)
    {
        printf("Falha no processamento do arquivo\n");
        return 1;
    }

    // executa funcionalidade desejada
    switch (n)
    {
    case 1:
        registra_especie(arquivo);
        break;
    case 2:
        relatorio(arquivo);
        break;
    case 3:
        busca(arquivo);
        break;
    case 4:
        registra_informacao(arquivo);
        break;
    }

    // fecha o arquivo
    fclose(arquivo);

    binarioNaTela(nome);

    return 0;
}