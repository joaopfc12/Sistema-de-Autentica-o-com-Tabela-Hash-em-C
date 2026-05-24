#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_TABELA   13
#define TAM_USERNAME 64
#define TAM_SENHA    64

typedef struct No {
    char           username[TAM_USERNAME];
    unsigned long  hashSenha;
    struct No     *proximo;
} No;

typedef struct {
    No  **slots;
    int   tamanho;
    int   quantUsuarios;
} TabelaHash;

unsigned long  valorString  (const char *str);
int            chaveDivisao (unsigned long valor, int tamanho);

TabelaHash    *criaHash     (int tamanho);
void           liberaHash   (TabelaHash *tabela);
void           insereHash   (TabelaHash *tabela, const char *username, const char *senha);
No            *buscaHash    (TabelaHash *tabela, const char *username);
void           removeHash   (TabelaHash *tabela, const char *username);
void           imprimeHash  (TabelaHash *tabela);
void           login        (TabelaHash *tabela, const char *username, const char *senha);

void           menuPrincipal(TabelaHash *tabela);

#endif
