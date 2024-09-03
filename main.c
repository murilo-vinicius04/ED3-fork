#include <stdio.h>
#include "estruturas.h"
#include "estruturas.c"
#include "relatorio.c"

int main()
{
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
