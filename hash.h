#ifndef HASH_H

#define HASH_H

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

/* ── Constantes ─────────────────────────────────── */

#define TAM_TABELA   13

#define TAM_USERNAME 64

#define TAM_SENHA    64

/* ── Nó da lista encadeada ───────────────────────── */

typedef struct No {

    char          use

    No  **slots;

    int   tamanho;

    int   quantUsuarios;

} TabelaHash;

/* ── Protótipos: funções de hash ─────────────────── */

unsigned long  valorString  (const char *str);

int            chaveDivisao (unsigned long valor, int tamanho);

/* ── Protótipos: operações da tabela ─────────────── */

TabelaHash    *criaHash     (int tamanho);

void           liberaHash   (TabelaHash *tabela);

void           insereHash   (TabelaHash *tabela, const char *username, const char *senha);

No            *buscaHash    (TabelaHash *tabela, const char *username);

void           removeHash   (TabelaHash *tabela, const char *username);

void           imprimeHash  (TabelaHash *tabela);

void           login        (TabelaHash *tabela, const char *username, const char *senha);

/* ── Protótipos: menu ────────────────────────────── */

void           menuPrincipal(TabelaHash *tabela);

#endif /* HASH_H */
