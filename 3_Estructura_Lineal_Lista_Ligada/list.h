//
// Creaada el: 23 / 09 / 2024
// Autora: Mariana Hernández Díaz
// Matricula: A01711207
//

#ifndef list_h
#define list_h

#include <sstream>
#include <string>

using namespace std;

//Se declaran las clases
template <class T> class List;
template <class T> class Node {
private:
  T value;
  Node<T> *next;

  Node(T);
  Node(T, Node<T> *);
  Node(const Node<T> &);

  friend class List<T>;
};

//Inicia el constructor
template <class T> Node<T>::Node(T val) {
  value = val;
  next = 0;
}

template <class T> Node<T>::Node(T val, Node<T> *nxt) {
  value = val;
  next = nxt;
}

template <class T> Node<T>::Node(const Node<T> &nxt) {
  value = nxt.value;
  next = nxt.next;
}

template <class T> class List {
private:
  Node<T> *head;
  int size;

public:
  List();
  List(const List<T> &);
  ~List();
  void insertion(int);
  T search(int);
  void update(int, int);
  void deleteAt(int);
  string toString() const;
};

//Se inicia la lista vacia
template <class T> List<T>::List() {
  head = 0;
  size = 0;
}

template <class T> List<T>::List(const List<T> &lista) {
  head = lista.head;
  size = lista.size;
}

//Elimina los nodos y reinicia el tamañao
template <class T> List<T>::~List() {
  size = 0;
  head = 0;
}

template <class T> void List<T>::insertion(int val) {
  if (head != 0) {
    Node<T> *p = head;
    while (p->next != 0) {
      p = p->next;
    }
    p->next = new Node<T>(val);
  } else {
    head = new Node<T>(val);
  }
  size++;
}

template <class T> T List<T>::search(int val) {
  if (head == 0)
    return -1;
  if (head->value == val)
    return 0;

  Node<T> *p = head;
  T res = -1;
  T cont = 0;

  while (p->next != 0) {
    if (p->next->value == val) {
      res = cont + 1;
      break;
    }
    cont++;
    p = p->next;
  }
  return res;
}

template <class T> void List<T>::update(int index, int val) {
  if (head != 0) {
    Node<T> *p = head;
    T cont = 0;
    while (p->next != 0 && cont != index) {
      cont++;
      p = p->next;
    }
    if (cont == index) {
      p->value = val;
    }
  }
}

//Elimina un nodo dado
template <class T> void List<T>::deleteAt(int index) {
  if (head != 0) {
    if (index == 0) {
      Node<T> *aux = head;
      head = head->next;
      delete aux;
    } else {
      Node<T> *p = head;
      Node<T> *aux;
      T cont = 0;
      while (p->next != 0 && cont < index - 1) {
        cont++;
        p = p->next;
      }
      aux = p->next;
      if (aux != 0) {
        p->next = aux->next;
        delete aux;
      }
    }
  }
}

template <class T> string List<T>::toString() const {
  stringstream aux;
  Node<T> *p = head;
  aux << "[";
  while (p != 0) {
    aux << p->value;
    if (p->next != 0) {
      aux << ", ";
    }
    p = p->next;
  }
  aux << "]";
  return aux.str();
}

#endif // list_h
