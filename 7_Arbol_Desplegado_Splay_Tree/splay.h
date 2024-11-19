/*
 * Autor: Mariana Hernández Díaz
 * Matricula: A01711207
 * Fecha: 04 / Nov / 2024
 */

#ifndef Splay_H_
#define Splay_H_

#include <iostream>
#include <sstream>
#include <string>

// Se declaran las clases es decir el arbol y los nodos
template <class T> class SplayTree;

template <class T> class Node {
private:
  T value;
  Node *left, *right, *parent;
  Node<T> *succesor();
  Node<T> *rot_right(Node<T> *);
  Node<T> *rot_left(Node<T> *);

public:
  Node(T);
  Node(T, Node<T> *, Node<T> *, Node<T> *);
  Node<T> *add(T);     // Agrega un nodo nuevo
  Node<T> *find(T);    // Busca un nodo en especifico
  Node<T> *remove(T);  // Quita un nodo
  void removeChilds(); // Quita los nodos hijos
  void inorder(std::stringstream &) const;
  void print_tree(std::stringstream &) const;
  void preorder(std::stringstream &) const;
  Node<T> *splay(Node<T> *, Node<T> *);
  friend class SplayTree<T>;
};

template <class T>
Node<T>::Node(T val) : value(val), left(0), right(0), parent(0) {}
template <class T>
Node<T>::Node(T val, Node<T> *le, Node<T> *ri, Node<T> *p)
    : value(val), left(le), right(ri), parent(p) {}
// Agrega un valor al arbol como en los BST
template <class T> Node<T> *Node<T>::add(T val) {
  if (val < value) {
    if (left != 0) {
      return left->add(val);
    } else {
      left = new Node<T>(val);
      left->parent = this;
      return left;
    }
  } else {
    if (right != 0) {
      return right->add(val);
    } else {
      right = new Node<T>(val);
      right->parent = this;
      return right;
    }
  }
}
// Busca un valor en especifico de los nods
template <class T> Node<T> *Node<T>::find(T val) {
  if (val == value) {
    return this;
  } else {
    if (val < value) {
      if (left != 0) {
        return left->find(val);
      } else {
        return 0;
      }
    } else {
      if (right != 0) {
        return right->find(val);
      } else {
        return 0;
      }
    }
  }
}
// Ayuda a encontrar el sucesor del arbol
template <class T> Node<T> *Node<T>::succesor() {
  Node<T> *le, *ri;
  le = left;
  ri = right;
  if (right->left == 0) {
    right = right->right;
    ri->right = 0;
    return ri;
  }
  Node<T> *parent, *child;
  parent = right;
  child = right->left;
  while (child->left != 0) {
    parent = child;
    child = child->left;
  }
  parent->left = child->right;
  child->right = 0;
  return child;
}
// Elimina el nodo o mas bien el valor especifico de este
template <class T> Node<T> *Node<T>::remove(T val) {
  if (val < value) {
    if (left != 0) {
      left = left->remove(val);
    }
  } else if (val > value) {
    if (right != 0) {
      right = right->remove(val);
    }
  } else {
    if (left == 0 && right == 0) {
      delete this;
      return 0;
    } else if (left == 0) {
      Node<T> *temp = right;
      right->parent = parent;
      delete this;
      return temp;
    } else if (right == 0) {
      Node<T> *temp = left;
      left->parent = parent;
      delete this;
      return temp;
    } else {
      Node<T> *succ = right->succesor();
      value = succ->value;
      right = right->remove(succ->value);
    }
  }
  return this;
}
// Quita los nodos hijos de forma recusiva

template <class T> void Node<T>::removeChilds() {
  if (left != 0) {
    left->removeChilds();
    delete left;
    left = 0;
  }
  if (right != 0) {
    right->removeChilds();
    delete right;
    right = 0;
  }
}
// Realiza una rotacion a la derecha

template <class T> Node<T> *Node<T>::rot_right(Node<T> *x) {
  Node<T> *y = x->left;
  x->left = y->right;
  if (y->right)
    y->right->parent = x;
  y->right = x;
  // Enlace con el padre de x
  y->parent = x->parent;
  x->parent = y;
  // Enlace entre x y y
  if (y->parent) {
    if (y->parent->left && y->parent->left->value == x->value)
      y->parent->left = y;
    else
      y->parent->right = y;
  }
  return y;
}
// Realiza una rotacion a la izquierda
template <class T> Node<T> *Node<T>::rot_left(Node<T> *x) {
  Node<T> *y = x->right;
  x->right = y->left;
  if (y->left)
    y->left->parent = x;
  y->left = x;
  // Enlace con el padre de x
  y->parent = x->parent;
  x->parent = y;
  // Enlace entre x y y
  if (y->parent) {
    if (y->parent->left && y->parent->left->value == x->value)
      y->parent->left = y;
    else
      y->parent->right = y;
  }
  return y;
}
// Realiza las rotaciones zig zag para que el nodo vaya a la raiz.
template <class T> Node<T> *Node<T>::splay(Node<T> *root, Node<T> *x) {
  while (x->parent != 0) {
    if (x->parent->value == root->value) {
      if (x->parent->left && x->parent->left->value == x->value) {
        rot_right(x->parent);
      } else {
        rot_left(x->parent);
      }
    } else {
      Node<T> *p = x->parent;
      Node<T> *g = p->parent;
      if (p->left && g->left && x->value == p->left->value &&
          p->value == g->left->value) {
        rot_right(g);
        rot_right(p);
      } else if (p->right && g->right && x->value == p->right->value &&
                 p->value == g->right->value) {
        rot_left(g);
        rot_left(p);
      } else if (p->left && g->right && x->value == p->left->value &&
                 p->value == g->right->value) {
        rot_right(p);
        rot_left(g);
      } else {
        rot_left(p);
        rot_right(g);
      }
    }
  }
  return x;
}
// Esta parte recorre el arbol en inorden
template <class T> void Node<T>::inorder(std::stringstream &aux) const {
  if (left != 0) {
    left->inorder(aux);
  }
  if (aux.tellp() != 1) {
    aux << " ";
  }
  aux << value;
  if (right != 0) {
    right->inorder(aux);
  }
}
// Permite imprimir el arbol
template <class T> void Node<T>::print_tree(std::stringstream &aux) const {
  if (parent != 0) {
    aux << "\n node " << value;
    aux << " parent " << parent->value;
  } else
    aux << "\n root " << value;
  if (left != 0)
    aux << " left " << left->value;
  if (right != 0)
    aux << " right " << right->value;
  aux << "\n";
  if (left != 0) {
    left->print_tree(aux);
  }
  if (right != 0) {
    right->print_tree(aux);
  }
}
// Recorre el arbol en preorden
template <class T> void Node<T>::preorder(std::stringstream &aux) const {
  aux << value;
  if (left != 0) {
    aux << " ";
    left->preorder(aux);
  }
  if (right != 0) {
    aux << " ";
    right->preorder(aux);
  }
}

template <class T> class SplayTree {
private:
  Node<T> *root;

public:
  SplayTree();
  ~SplayTree();
  bool empty() const;
  void add(T);      // Añade un nuevo valor
  bool find(T);     // Busca un nuevo valor
  void remove(T);   // Elimina un valor
  void removeAll(); // limpia todo el arbol
  std::string inorder() const;
  std::string print_tree() const;
  std::string preorder() const;
};
// Constructor por default,inicia el arbol vacio
template <class T> SplayTree<T>::SplayTree() : root(0) {}
// Destructor por default,limpia el arbol
template <class T> SplayTree<T>::~SplayTree() { removeAll(); }
// revisa si el arbol esta vacio
template <class T> bool SplayTree<T>::empty() const { return (root == 0); }
// se añade un nuevo valor en el arbol y lo mueve a la raiz
template <class T> void SplayTree<T>::add(T val) {
  if (root != 0) {
    Node<T> *added = root->add(val);
    root = root->splay(root, added);
  } else {
    root = new Node<T>(val);
  }
}
// Elimina un valor del arbol y modifica la raiz
template <class T> void SplayTree<T>::remove(T val) {
  if (root != 0) {
    if (val == root->value) {
      Node<T> *succ = root->succesor();
      if (succ != 0) {
        succ->left = root->left;
        succ->right = root->right;
        succ->parent = 0;
        if (succ->left)
          succ->left->parent = succ;
        if (succ->right)
          succ->right->parent = succ;
      }
      delete root;
      root = succ;
    } else {
      Node<T> *p = root->find(val);
      if (p != 0) {
        Node<T> *parent = p->parent;
        p = parent->remove(val);
        if (p) {
          root = root->splay(root, p);
        }
      }
    }
  }
}
// Limpia el arbol y elimina todos los nodos
template <class T> void SplayTree<T>::removeAll() {
  if (root != 0) {
    root->removeChilds();
  }
  delete root;
  root = 0;
}
// Busca el valor y lo mueve a la raiz
template <class T> bool SplayTree<T>::find(T val) {
  if (root != 0) {
    Node<T> *found = root->find(val);
    root = root->splay(root, found);
    return (root->value == val);
  } else {
    return false;
  }
}
// Da el recorrido como cadena de inorden
template <class T> std::string SplayTree<T>::inorder() const {
  std::stringstream aux;
  aux << "[";
  if (!empty()) {
    root->inorder(aux);
  }
  aux << "]";
  return aux.str();
}
// Da la estructura del arbol como cadena
template <class T> std::string SplayTree<T>::print_tree() const {
  std::stringstream aux;
  aux << "\n ================================ ";
  if (!empty()) {
    root->print_tree(aux);
  }
  aux << " ================================ \n";
  return aux.str();
}
// Da los valores de preorden en dorma de cadena
template <class T> std::string SplayTree<T>::preorder() const {
  std::stringstream aux;
  aux << "[";
  if (!empty()) {
    root->preorder(aux);
  }
  aux << "]";
  return aux.str();
}

#endif /* Splay_H_ */
