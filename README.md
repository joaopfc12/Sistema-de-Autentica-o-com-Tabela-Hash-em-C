# Sistema de Autenticação com Tabela Hash em C

Sistema de autenticação simples desenvolvido em C utilizando tabela hash implementada do zero, com encadeamento separado para tratamento de colisões.

---

## Estrutura dos arquivos

```
.
├── hash.h    # Definições de structs, constantes e protótipos
├── hash.c    # Implementação da tabela hash e funções auxiliares
├── main.c    # Menu interativo e ponto de entrada do programa
└── README.md
```

---

## Como compilar

Necessário ter o **GCC** instalado.

```bash
gcc -Wall -Wextra -o auth hash.c main.c
```

## Como executar

```bash
./auth
```

---

## Funcionalidades

| Opção | Descrição |
|-------|-----------|
| 1 | Cadastrar usuário (username + hash da senha) |
| 2 | Login (valida senha via hash) |
| 3 | Remover usuário |
| 4 | Imprimir tabela (mostra índices, usuários e colisões) |
| 0 | Sair |

---

## Detalhes técnicos

### Função de hash — `valorString` (djb2)
Transforma a senha em um número `unsigned long` usando o algoritmo **djb2**:

```c
hash = hash * 33 + c   // para cada caractere c da string
```

O índice na tabela é calculado pelo **método da divisão** (`chaveDivisao`):

```c
indice = hash % tamanho_da_tabela
```

> A senha original **nunca é armazenada**. Apenas o valor numérico do hash é salvo.

### Tratamento de colisões — Encadeamento Separado
Cada slot da tabela é uma **lista encadeada**. Quando dois usuários mapeiam para o mesmo índice, o novo nó é inserido no início da lista daquele slot.

```
slots[3] -> [carol] -> [dave] -> NULL
```

O programa detecta e exibe colisões ao imprimir a tabela (`*** N COLISOES ***`).

### Funções implementadas

| Função | Descrição |
|--------|-----------|
| `criaHash` | Aloca a tabela dinamicamente com `malloc` |
| `insereHash` | Cadastra usuário; rejeita duplicatas |
| `buscaHash` | Busca usuário pelo username |
| `removeHash` | Remove nó da lista e libera com `free` |
| `liberaHash` | Libera toda a memória da tabela |
| `imprimeHash` | Exibe índices ocupados e colisões |

### Alocação dinâmica
- `TabelaHash` e o array de slots são alocados com `malloc` em `criaHash`
- Cada novo usuário (`No`) é alocado com `malloc` em `insereHash`
- Toda a memória é liberada com `free` em `removeHash` e `liberaHash`

---

## Exemplo de execução

```
Inicializando tabela hash (tamanho 11)...

1. Cadastrar usuario
>> Usuario 'alice' cadastrado com sucesso! (indice 0)

2. Login
>> Login bem-sucedido! Bem-vindo, alice!

4. Imprimir tabela
[Indice  0]
  -> Username : alice
     Hash senha: 7572920765732010
```
