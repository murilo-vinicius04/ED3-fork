# Exercicio1ED3

os arquivos estruturas.h e estruturas.c buscam implementar uma classe chamada Registro com cada um dos campos especificados:

a.SPECIES_ID -> 4 bytes (int)

b. NAME -> 41 bytes

c. SCIENTIFIC_NAME -> 61 bytes

d. POPULATION-> 4 bytes (int)

e. STATUS-> 9 bytes

f. LOCATION -> 8 bytes (2 floats de 4 bytes)

g. HUMAN_IMPACT -> 4 bytes (int)

Metodos do registro em estruturas.c:

le_registro: recebe o nome do arquivo e o byte offset do registro e retorna o registro com os valores lidos
[aqui por exemplo implementamos a funcao que busca um registro especifico ou que escreve novos registros]
printa_formatado: recebe o registro e printa seus valores segundo formatacao desejada

funcoes auxiliares em funcoes.c:

tamanho_bytes: recebe arquivo e retorna numero de bytes que aquele arquivo possui
limpa: recebe um string com varios caracteres "$" de lixo ao seu final e retorna o string ja limpo,
ou seja, sem os caracteres de lixo

main.c:

Esse arquivo recebe qual das 4 funcoes que vc quer que execute e chama essa funcao
