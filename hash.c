#include "hash.h"
 
/* ---------------------------------------------------
   valorString  —  algoritmo djb2
   Transforma cada caractere em um número acumulado:
   hash = hash * 33 + c
   --------------------------------------------------- */
unsigned long valorString(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = (unsigned char)*str++))
        hash = ((hash << 5) + hash) + c;
    return hash;
}
 
/* ---------------------------------------------------
   chaveDivisao  —  método da divisão
   Mapeia o hash para um índice válido na tabela.
   --------------------------------------------------- */
int chaveDivisao(unsigned long valor, int tamanho) {
    return (int)(valor % (unsigned long)tamanho);
}
 
/* ---------------------------------------------------
   criaHash  —  aloca e inicializa a tabela
   --------------------------------------------------- */
TabelaHash *criaHash(int tamanho) {
    TabelaHash *tabela = (TabelaHash *)malloc(sizeof(TabelaHash));
    if (!tabela) {
        fprintf(stderr, "Erro: nao foi possivel alocar a tabela.\n");
        return NULL;
    }
 
    tabela->slots = (No **)calloc(tamanho, sizeof(No *));
    if (!tabela->slots) {
        fprintf(stderr, "Erro: nao foi possivel alocar os slots.\n");
        free(tabela);
        return NULL;
    }
 
    tabela->tamanho       = tamanho;
    tabela->quantUsuarios = 0;
    return tabela;
}

/* ---------------------------------------------------
   insereHash  —  cadastra usuário na tabela
   Rejeita duplicatas. Salva apenas o hash da senha.
   --------------------------------------------------- */
void insereHash(TabelaHash *tabela, const char *username, const char *senha) {
    if (!tabela || !username || !senha) return;
 
    if (strlen(username) == 0 || strlen(senha) == 0) {
        printf("Erro: username e senha nao podem ser vazios.\n");
        return;
    }
 
    if (buscaHash(tabela, username)) {
        printf("Erro: usuario '%s' ja existe.\n", username);
        return;
    }
 
    int indice = chaveDivisao(valorString(username), tabela->tamanho);
 
    No *novo = (No *)malloc(sizeof(No));
    if (!novo) {
        fprintf(stderr, "Erro: nao foi possivel alocar o no.\n");
        return;
    }
 
    strncpy(novo->username, username, TAM_USERNAME - 1);
    novo->username[TAM_USERNAME - 1] = '\0';
    novo->hashSenha = valorString(senha);
 
    /* insere no início da lista (encadeamento separado) */
    novo->proximo       = tabela->slots[indice];
    tabela->slots[indice] = novo;
    tabela->quantUsuarios++;
 
    printf(">> Usuario '%s' cadastrado com sucesso! (indice %d)\n", username, indice);
}
 
/* ---------------------------------------------------
   buscaHash  —  procura usuário pelo username
   Retorna ponteiro para o nó ou NULL se não achar.
   --------------------------------------------------- */
No *buscaHash(TabelaHash *tabela, const char *username) {
    if (!tabela || !username) return NULL;
 
    int indice = chaveDivisao(valorString(username), tabela->tamanho);
 
    No *atual = tabela->slots[indice];
    while (atual) {
        if (strcmp(atual->username, username) == 0)
            return atual;
        atual = atual->proximo;
    }
    return NULL;
}
 
/* ---------------------------------------------------
   removeHash  —  remove usuário e libera memória
   --------------------------------------------------- */
void removeHash(TabelaHash *tabela, const char *username) {
    if (!tabela || !username) return;
 
    int indice   = chaveDivisao(valorString(username), tabela->tamanho);
    No *atual    = tabela->slots[indice];
    No *anterior = NULL;
 
    while (atual) {
        if (strcmp(atual->username, username) == 0) {
            if (anterior)
                anterior->proximo = atual->proximo;
            else
                tabela->slots[indice] = atual->proximo;
 
            free(atual);
            tabela->quantUsuarios--;
            printf(">> Usuario '%s' removido com sucesso.\n", username);
            return;
        }
        anterior = atual;
        atual    = atual->proximo;
    }
 
    printf("Erro: usuario '%s' nao encontrado.\n", username);
}
 
/* ---------------------------------------------------
   liberaHash  —  libera toda a memória da tabela
   --------------------------------------------------- */
void liberaHash(TabelaHash *tabela) {
    if (!tabela) return;
 
    for (int i = 0; i < tabela->tamanho; i++) {
        No *atual = tabela->slots[i];
        while (atual) {
            No *proximo = atual->proximo;
            free(atual);
            atual = proximo;
        }
    }
 
    free(tabela->slots);
    free(tabela);
}
 
/* ---------------------------------------------------
   imprimeHash  —  exibe tabela com colisões
   Formato idêntico ao README do projeto.
   --------------------------------------------------- */
void imprimeHash(TabelaHash *tabela) {
    if (!tabela) return;
 
    printf("\n=== TABELA HASH (tamanho %d | usuarios %d) ===\n\n",
           tabela->tamanho, tabela->quantUsuarios);
 
    for (int i = 0; i < tabela->tamanho; i++) {
        if (!tabela->slots[i]) continue;
 
        int colisoes = 0;
        No *atual = tabela->slots[i];
        while (atual) { colisoes++; atual = atual->proximo; }
 
        printf("[Indice %2d]", i);
        if (colisoes > 1)
            printf("  *** %d COLISOES ***", colisoes);
        printf("\n");
 
        atual = tabela->slots[i];
        while (atual) {
            printf("  -> Username : %s\n", atual->username);
            printf("     Hash senha: %lu\n", atual->hashSenha);
            atual = atual->proximo;
        }
        printf("\n");
    }
}
 
/* ---------------------------------------------------
   login  —  valida usuário e senha por hash
   A senha digitada é hasheada e comparada com a salva.
   --------------------------------------------------- */
void login(TabelaHash *tabela, const char *username, const char *senha) {
    No *no = buscaHash(tabela, username);
 
    if (!no) {
        printf(">> Login falhou: usuario '%s' nao encontrado.\n", username);
        return;
    }
 
    if (valorString(senha) == no->hashSenha)
        printf(">> Login bem-sucedido! Bem-vindo, %s!\n", username);
    else
        printf(">> Login falhou: senha incorreta.\n");
}
 