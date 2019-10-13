# COS480
Repositório destinado aos trabalhos da disciplina Construção de Banco de Dados (COS480)

## Compilação
Entre na pasta /src.
Altere no main.cpp para a DATA_STRUCT desejada.
Execute os comandos abaixo, adicionando o .cpp da DATA_STRUCT desejada. (exemplo abaixo para DATA_STRUCT Sorted)
### Compilar para debuggar (com flag de debugger)
g++ -g -I ../include/ Block.cpp Column.cpp Header.cpp Sorted.cpp Record.cpp Schema.cpp main.cpp -o main
### Compilar para executar (com flags de otimização)
g++ -O3 -I ../include/ Block.cpp Column.cpp Header.cpp Sorted.cpp Record.cpp Schema.cpp main.cpp -o main