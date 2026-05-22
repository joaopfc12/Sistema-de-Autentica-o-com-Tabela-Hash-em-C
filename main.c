#include "hash.h"

static void limpaBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

static void leString(char *destino, int tamanho, const char *prompt) {
    printf("%s", prompt);
    if (fgets(destino, tamanho, stdin)) {
        size_t len = strlen(destino);
        if (len > 0 && destino[len - 1] == '\n') {
            destino[len - 1] = '\0';
        }
    }
}

void menuPrincipal(TabelaHash *tabela) {
    int opcao;
    char username[TAM_USERNAME];
    char senha[TAM_SENHA];

    do {
        printf("  SISTEMA DE AUTENTICACAO\n");
        printf("1. Cadastrar usuario\n");
        printf("2. Login\n");
        printf("3. Remover usuario\n");
        printf("4. Imprimir tabela\n");
        printf("0. Sair\n");
        printf("Opcao: ");

        if (scanf("%d", &opcao) != 1) {
            limpaBuffer();
            printf("Opcao invalida.\n");
            continue;
        }
        limpaBuffer();

        switch (opcao) {
            case 1:
                printf("\n CADASTRO \n");
                leString(username, TAM_USERNAME, "Username: ");
                leString(senha,    TAM_SENHA,    "Senha   : ");
                insereHash(tabela, username, senha);
                break;

            case 2:
                printf("\n--- LOGIN ---\n");
                leString(username, TAM_USERNAME, "Username: ");
                leString(senha,    TAM_SENHA,    "Senha   : ");
                login(tabela, username, senha);
                break;

            case 3:
                printf("\n--- REMOVER USUARIO ---\n");
                leString(username, TAM_USERNAME, "Username: ");
                removeHash(tabela, username);
                break;

            case 4:
                imprimeHash(tabela);
                break;

            case 0:
                printf("Encerrando sistema...\n");
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
        }

    } while (opcao != 0);
}

int main(void) {
    printf("Inicializando tabela hash (tamanho %d)...\n", TAM_TABELA);

    TabelaHash *tabela = criaHash(TAM_TABELA);
    if (!tabela) {
        fprintf(stderr, "Falha ao criar a tabela. Encerrando.\n");
        return 1;
    }

    menuPrincipal(tabela);

    liberaHash(tabela);
    return 0;
}
