#include <stdio.h>
#include <stdlib.h>

#define MAX 3
#define MIN 2

typedef struct node {
  int nChave[MAX + 1];
  int count;
  struct Node *list[MAX + 1];
} Node;

Node *root;

// Criar nodo
Node *createNode(int nChave, Node *child) {
  Node *node;

  node = (Node *)malloc(sizeof(Node));

  node->nChave[1] = nChave;
  node->count = 1;
  node->list[0] = root;
  node->list[1] = child;

  return node;
}

// Inserir nodo
void insertNode(int nChave, int pos, Node *node, Node *child) {
  int i = node->count;

  while (i > pos) {
    node->nChave[i + 1] = node->nChave[i];
    node->list[i + 1] = node->list[i];

    i--;
  }

  node->nChave[i + 1] = nChave;
  node->list[i + 1] = child;
  node->count++;
}

// Split
void split(int nChave, int *ptrVal, int pos, Node *node, Node *child, Node **newNode) {
  int median, j;

  if (pos > MIN)
    median = MIN + 1;
  else
    median = MIN;

  *newNode = (Node *)malloc(sizeof(Node));

  j = median + 1;
  while (j <= MAX) {
    (*newNode)->nChave[j - median] = node->nChave[j];
    (*newNode)->list[j - median] = node->list[j];
    j++;
  }

  node->count = median;
  (*newNode)->count = MAX - median;

  if (pos <= MIN) {
    insertNode(nChave, pos, node, child);
  } else {
    insertNode(nChave, pos - median, *newNode, child);
  }

  *ptrVal = node->nChave[node->count];
  (*newNode)->list[0] = node->list[node->count];
  node->count--;
}

// Atribuir nChaveor
int setValue(int nChave, int *ptrVal, Node *node, Node **child) {
  int pos;

  if (!node) {
    *ptrVal = nChave;
    *child = NULL;
    return 1;
  }

  if (nChave < node->nChave[1]) {
    pos = 0;
  } else {
    for (pos = node->count;
       (nChave < node->nChave[pos] && pos > 1); pos--)
      ;
    if (nChave == node->nChave[pos]) {
      printf("\nChaves duplicadas!\n");
      return 0;
    }
  }

  if (setValue(nChave, ptrVal, node->list[pos], child)) {
    if (node->count < MAX) {
      insertNode(*ptrVal, pos, node, *child);
    } else {
      split(*ptrVal, ptrVal, pos, node, *child, child);
      return 1;
    }
  }

  return 0;
}

// Inserir nChaveor
void insert(int nChave) {
  int flag, i;

  Node *nodo;

  flag = setValue(nChave, &i, root, &nodo);

  if (flag)
    root = createNode(i, nodo);
}

// imprime nodos
void imprime(Node *nodo) {
  int i;

  if (nodo) {
    for (i = 0; i < nodo->count; i++) {
      imprime(nodo->list[i]);
      printf("%d ", nodo->nChave[i + 1]);
    }
    imprime(nodo->list[i]);
  }
}

int main() {
    int n = 10;
    for(int i = 1; i <= n; i++){
        insert(i);
    }

    imprime(root);
    printf("\n");

    return 0;
}