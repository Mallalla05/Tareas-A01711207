/*
 * Autor: Mariana Hernández Díaz
 * Matricula: A01711207
 * Fecha: 21 / Nov / 2024
 */

#ifndef QUADRATIC_H_
#define QUADRATIC_H_

#include <sstream>
#include <string>

template <class Key, class Value> class Quadratic {
private:
  unsigned int (*func)(const Key);
  unsigned int size;
  unsigned int count;
  Key *keys;
  Key initialValue;
  Value *values;
  // Ayuda a obtener la clave de la tabla
  long indexOf(const Key) const;

public:
  // Inicia la tabla con tamaño y valor inicial
  Quadratic(unsigned int, Key, unsigned int (*f)(const Key));
  ~Quadratic();
  bool full() const;
  bool put(Key, Value);
  bool contains(const Key) const;
  Value get(const Key);
  void clear();
  std::string toString() const;
};
// Inicia los arreglos y valores,establece el valor inicial.
template <class Key, class Value>
Quadratic<Key, Value>::Quadratic(unsigned int sze, Key init,
                                 unsigned int (*f)(const Key)) {
  size = sze;
  keys = new Key[size];
  initialValue = init;
  for (unsigned int i = 0; i < size; i++) {
    keys[i] = init;
  }
  values = new Value[size];
  for (int i = 0; i < sze; i++) {
    values[i] = 0;
  }
  func = f;
  count = 0;
}
// Libera la memoria asignada de los arreglos
template <class Key, class Value> Quadratic<Key, Value>::~Quadratic() {
  delete[] keys;
  keys = nullptr;
  delete[] values;
  values = nullptr;
  size = 0;
  func = nullptr;
  count = 0;
}
// Revisa si la tabla esta llena
template <class Key, class Value> bool Quadratic<Key, Value>::full() const {
  return (count >= size);
}
// Encuentra el indice y devuelve -1 si no existe
template <class Key, class Value>
long Quadratic<Key, Value>::indexOf(const Key k) const {
  unsigned int i, start;
  int c = 0;
  start = i = func(k) % size;
  do {
    if (keys[i] == k) {
      return i;
    }
    c++;
    i = (start + c * c) % size;
  } while (keys[i] != initialValue && start != i);
  return -1;
}
// Añade un valor en la tabla y maneja colisiones
template <class Key, class Value>
bool Quadratic<Key, Value>::put(Key k, Value v) {
  unsigned int i, start;
  int c = 0;
  long pos = indexOf(k);
  if (pos != -1) {
    values[pos] = v;
    return true;
  }
  start = i = func(k) % size;
  do {
    if (keys[i] == initialValue) {
      keys[i] = k;
      values[i] = v;
      count++;
      return true;
    }
    c++;
    i = (start + c * c) % size;
  } while (c < size);
  return false;
}
// Revisa si la tabla tiene un valor
template <class Key, class Value>
bool Quadratic<Key, Value>::contains(const Key k) const {
  return (indexOf(k) != -1);
}
// Devuelve el valor de la clave
template <class Key, class Value>
Value Quadratic<Key, Value>::get(const Key k) {
  long pos = indexOf(k);
  if (pos != -1) {
    return values[pos];
  }
  throw std::out_of_range("Key not found");
}
// Limpia la tabla y restablece los valores iniciales
template <class Key, class Value> void Quadratic<Key, Value>::clear() {
  count = 0;
  for (unsigned int i = 0; i < size; i++) {
    keys[i] = initialValue;
  }
}
// Da una cadena de los elementos de la tabla
template <class Key, class Value>
std::string Quadratic<Key, Value>::toString() const {
  std::stringstream aux;
  for (unsigned int i = 0; i < size; i++) {
    if (keys[i] != initialValue) {
      aux << "(" << i << " " << keys[i] << " : " << values[i] << ") ";
    }
  }
  return aux.str();
}

#endif /* QUADRATIC_H_ */
