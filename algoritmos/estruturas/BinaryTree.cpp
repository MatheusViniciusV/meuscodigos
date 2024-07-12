//Objetivo: Estruturar os dados de forma a permitir busca binária.
//Complexidade (inserção): O(log n)
//Complexidade (pesquisa): O(log n)
//Complexidade (percurso): O(n)

struct Node {
    char valor;
    Node *esquerda, *direita;
};

void inserir(Node *&node, char valor) {
    if(node == NULL) {
        node = new Node;
        node->esquerda = node->direita = NULL;
        node->valor = valor;
    } else if(valor < node->valor) {
        inserir(node->esquerda, valor);
    } else {
        inserir(node->direita, valor);
    }
}

bool pesquisa(Node *node, char valor) {
    if(node != NULL) {
        if(node->valor == valor)
            return true;
        else
            return pesquisa(node->esquerda, valor) or pesquisa(node->direita, valor);
    }
    
    return false;
}

void posfixado(Node *node) {
    if(node != NULL) {
        posfixado(node->esquerda);
        posfixado(node->direita);
        cout << node->valor << endl;
    }
}

void infixado(Node *node) {
    if(node != NULL) {
        infixado(node->esquerda);
        cout << node->valor << endl;
        infixado(node->direita);
    }
}

void prefixado(Node *node) {
    if(node != NULL) {
        cout << node->valor << endl;
        prefixado(node->esquerda);
        prefixado(node->direita);
    }
}
