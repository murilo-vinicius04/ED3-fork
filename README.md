# ED3

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

main.c:

Esse arquivo recebe qual das 4 funcoes que vc quer que execute e chama essa funcao
