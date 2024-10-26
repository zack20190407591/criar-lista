#include <stdio.h>
#include <stdlib.h>

#define MAX 100 // Tamanho máximo da lista

typedef struct No {
    int chave;   // Identificador do nó
    int valor;   // Valor armazenado no nó
} No;

typedef struct Lista {
    No *itens[MAX]; // Array para armazenar os nós
    int contagem;   // Contador de elementos
} Lista;

void inicializaLista(Lista *lista) {
    lista->contagem = 0; // Inicializa o contador
}

void exibeLista(Lista *lista) {
    printf("Lista: ");
    for (int i = 0; i < lista->contagem; i++) {
        printf("%d - %d | ", lista->itens[i]->chave, lista->itens[i]->valor);
    }
    printf("\n");
}

No *buscaPorChave(Lista *lista, int chave) {
    for (int i = 0; i < lista->contagem; i++) {
        if (lista->itens[i]->chave == chave) {
            return lista->itens[i]; // Retorna o nó se encontrado
        }
    }
    return NULL; // Retorna NULL se não encontrar
}

int adicionaNo(Lista *lista, No *no) {
    if (lista->contagem >= MAX) {
        printf("Lista cheia, não é possível adicionar o nó.\n");
        return 0; // Retorna 0 se a lista estiver cheia
    }
    lista->itens[lista->contagem++] = no; // Adiciona o novo nó
    return 1; // Retorna 1 se a adição for bem-sucedida
}

void insereNoInicio(Lista *lista, No *no) {
    if (lista->contagem >= MAX) {
        printf("Lista cheia.\n");
        return;
    }
    for (int i = lista->contagem; i > 0; i--) {
        lista->itens[i] = lista->itens[i - 1]; // Desloca os elementos
    }
    lista->itens[0] = no; // Insere no início
    lista->contagem++;
}

void insereNoFim(Lista *lista, No *no) {
    adicionaNo(lista, no); // Usa a função existente para adicionar no fim
}

void insereEmOrdem(Lista *lista, No *no) {
    if (lista->contagem >= MAX) {
        printf("Lista cheia, não é possível inserir em ordem.\n");
        return;
    }
    int i;
    for (i = 0; i < lista->contagem; i++) {
        if (lista->itens[i]->valor > no->valor) {
            break; // Encontra a posição correta
        }
    }
    for (int j = lista->contagem; j > i; j--) {
        lista->itens[j] = lista->itens[j - 1]; // Desloca os elementos
    }
    lista->itens[i] = no; // Insere na posição correta
    lista->contagem++;
}

void removeNo(Lista *lista, int chave) {
    int pos = -1;
    for (int i = 0; i < lista->contagem; i++) {
        if (lista->itens[i]->chave == chave) {
            free(lista->itens[i]); // Libera a memória do nó encontrado
            pos = i; // Armazena a posição
            break;
        }
    }
    if (pos == -1) {
        printf("Elemento não encontrado.\n");
        return; // Retorna se o elemento não foi encontrado
    }
    for (int i = pos; i < lista->contagem - 1; i++) {
        lista->itens[i] = lista->itens[i + 1]; // Move os elementos
    }
    lista->contagem--; // Reduz o contador
}

No *criaNo(int chave, int valor) {
    No *no = (No *)malloc(sizeof(No)); // Aloca memória para um novo nó
    no->chave = chave;
    no->valor = valor;
    return no; // Retorna o novo nó
}

int main() {
    Lista minhaLista;
    inicializaLista(&minhaLista);

    // Criar nós e inserir na lista
    No *no1 = criaNo(1, 30);
    No *no2 = criaNo(2, 10);
    No *no3 = criaNo(3, 20);

    insereEmOrdem(&minhaLista, no1); // Insere 30
    insereEmOrdem(&minhaLista, no2); // Insere 10
    insereEmOrdem(&minhaLista, no3); // Insere 20

    exibeLista(&minhaLista);

    No *encontrado = buscaPorChave(&minhaLista, 2);
    if (encontrado) {
        printf("Elemento encontrado: %d - %d\n", encontrado->chave, encontrado->valor);
    }

    removeNo(&minhaLista, 1);
    exibeLista(&minhaLista);

    // Libera a memória remanescente
    for (int i = 0; i < minhaLista.contagem; i++) {
        free(minhaLista.itens[i]);
    }

    return 0;
}