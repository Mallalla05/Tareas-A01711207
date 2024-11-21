/*
 * Fecha: 11/11/2024
 * Autor: Mariana Hernández Díaz
 * Matricula: A01711207
 */

#ifndef Graph_H_
#define Graph_H_

#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <queue>
#include <sstream>
#include <stack>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

class Graph {
private:
  int edgesList;
  int edgesMat;
  int nodes;
  vector<int> *adjList;
  int *adjMatrix;

public:
  Graph(int);
  Graph();
  void addEdgeAdjList(int, int);
  void addEdgeAdjMatrix(int, int);
  string printAdjList();
  string printAdjMat();
  string printAdjMat_clean();
  string DFS(int, int);
  string depthHelper(int, int, stack<int> &, list<int> &,
                     vector<vector<int>> &);
  string BFS(int, int);
  string breadthHelper(int, int, queue<int> &, list<int> &,
                       vector<vector<int>> &);
  string print_visited(list<int>);
  string print_path(vector<vector<int>> &, int, int);
  bool contains(list<int>, int);
  void sortAdjList();
  void loadGraphList(string, int);
  void loadGraphMat(string, int, int);
};

// En esta parte se inicia la lista de adyacencia por un string entre nodos.El
// parametro a son los nodos en el grafo.
void Graph::loadGraphList(string string_nodos, int a) {
  adjList = new vector<int>[a];
  nodes = a;
  int u, v;
  char ignore;
  istringstream ss(string_nodos);
  while (ss >> ignore >> u >> ignore >> v >> ignore) {
    addEdgeAdjList(u, v);
  }
  sortAdjList();
}

// Se inicia la matriz despues de un string para la conexion entre nodos, el a y
// b son las filas y columnas.
void Graph::loadGraphMat(string string_nodos, int a, int b) {
  adjMatrix = new int[a * b]();
  nodes = a;
  int u, v;
  char ignore;
  istringstream ss(string_nodos);

  // Lee las conexiones y las agrega a la matriz.
  while (ss >> ignore >> u >> ignore >> v >> ignore) {
    addEdgeAdjMatrix(u, v);
  }
}

// Constructor por defecto
Graph::Graph() { edgesList = edgesMat = 0; }

// Constructor que inicia el grafo con nodos especificos
Graph::Graph(int n) {
  nodes = n;
  adjList = new vector<int>[nodes];
  adjMatrix = new int[nodes * nodes];
  for (int i = 0; i < nodes * nodes; i++)
    adjMatrix[i] = 0;
  edgesList = edgesMat = 0;
}

// Agrega un arista entre nodos u y v.
void Graph::addEdgeAdjList(int u, int v) {
  adjList[u].push_back(v);
  adjList[v].push_back(u);
  edgesList++; // Incrementa el contador de aristas
}

// Es una nueva relacion entre nodos de la matriz
void Graph::addEdgeAdjMatrix(int u, int v) {
  adjMatrix[u * nodes + v] = 1;
  adjMatrix[v * nodes + u] = 1;
  edgesMat++;
}

// Devueve un string que muestra la lista y sirve para visualizar conexiones
string Graph::printAdjList() {
  stringstream aux;
  for (int i = 0; i < nodes; i++) {
    aux << "vertex " << i << " :";
    for (int j = 0; j < adjList[i].size(); j++) {
      aux << " " << adjList[i][j];
    }
    aux << " ";
  }
  return aux.str();
}

// Ordena la lista para cada nodo y la muestra de forma ordenada.
void Graph::sortAdjList() {
  for (int i = 0; i < nodes; i++)
    sort(adjList[i].begin(), adjList[i].end());
}

// Da un string con la matriz completa y ayuda ver las conexiones en forma de
// matriz.
string Graph::printAdjMat() {
  stringstream aux;
  for (int i = 0; i < nodes; i++) {
    for (int j = 0; j < nodes; j++) {
      aux << adjMatrix[i * nodes + j] << " ";
    }
  }
  return aux.str();
}

// Da el string mas claro
string Graph::printAdjMat_clean() {
  stringstream aux;
  aux << "\n nodes \t|";
  for (int i = 0; i < nodes; i++) {
    aux << "\t" << i;
  }
  aux << "\n";
  for (int i = 0; i < nodes; i++) {
    aux << "__________";
  }
  aux << "\n";
  for (int i = 0; i < nodes; i++) {
    aux << i << "\t|";
    for (int j = 0; j < nodes; j++) {
      aux << "\t" << adjMatrix[i * nodes + j];
    }
    aux << "\n";
  }
  return aux.str();
}

// Hace la busqueda desde el nodo 'start' hasta el nodo 'goal'buscando lo mas
// lejos que se pueda para retroceder.
string Graph::DFS(int start, int goal) {
  stack<int> st;
  list<int> visited;
  vector<vector<int>> paths(nodes, vector<int>(1, -1));
  st.push(start);
  string ans = depthHelper(start, goal, st, visited, paths);
  ans = ans + print_path(paths, start, goal);
  return ans;
}

// Ayuda a DFS a administrar el stack.
string Graph::depthHelper(int current, int goal, stack<int> &st,
                          list<int> &visited, vector<vector<int>> &paths) {
  if (current == goal) {
    return print_visited(visited);
  } else if (st.empty()) {
    return "node not found";
  } else {
    current = st.top();
    st.pop();
    visited.push_back(current);
    for (int i = 0; i < adjList[current].size(); i++) {
      if (!contains(visited, adjList[current][i])) {
        st.push(adjList[current][i]);
        paths[adjList[current][i]][0] = current;
      }
    }
    return depthHelper(current, goal, st, visited, paths);
  }
}

// Hace una busqueda del nodo 'start' hasta el nodo 'goal' de forma que sea de
// nivel por nivel.
string Graph::BFS(int start, int goal) {
  queue<int> qu;
  list<int> visited;
  vector<vector<int>> paths(nodes, vector<int>(0));
  qu.push(start);
  string ans = breadthHelper(start, goal, qu, visited, paths);
  ans = ans + print_path(paths, start, goal);
  return ans;
}

// Ayuda a BFS a administrar el queue y caminos.
string Graph::breadthHelper(int current, int goal, queue<int> &qu,
                            list<int> &visited, vector<vector<int>> &paths) {
  if (current == goal) {
    return print_visited(visited);
  } else if (qu.empty()) {
    return "node not found";
  } else {
    current = qu.front();
    qu.pop();
    visited.push_back(current);
    for (int i = 0; i < adjList[current].size(); i++) {
      if (!contains(visited, adjList[current][i])) {
        qu.push(adjList[current][i]);
        paths[adjList[current][i]].push_back(current);
      }
    }
    return breadthHelper(current, goal, qu, visited, paths);
  }
}

// Revisa si el nodo para ver si esta en la lista y este no se cicla.
bool Graph::contains(list<int> ls, int node) {
  list<int>::iterator it;
  it = find(ls.begin(), ls.end(), node);
  if (it != ls.end())
    return true;
  else
    return false;
}

// Devuelve un string que ya se visitaron.
string Graph::print_visited(list<int> q) {
  stringstream aux;
  aux << "visited: ";
  while (!q.empty()) {
    aux << q.front() << " ";
    q.pop_front();
  }
  return aux.str();
}

// Imprime el camino del nodo 'start' al nodo 'goal' basado en el vector.
string Graph::print_path(vector<vector<int>> &path, int start, int goal) {
  int node = path[goal][0];
  stack<int> reverse;
  reverse.push(goal);
  stringstream aux;
  aux << "path:";
  while (node != start) {
    reverse.push(node);
    node = path[node][0];
  }
  reverse.push(start);
  while (!reverse.empty()) {
    aux << " " << reverse.top();
    reverse.pop();
  }
  return aux.str();
}
#endif /* GRAPH_H_ */
