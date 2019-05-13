#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"

#include <string>
#include <iostream>

using namespace std;
/**
* @return The number of vertices in the Graph
*/
template <class V, class E>
unsigned int Graph<V,E>::size() const {
  // TODO: Part 2
  //return 0;
  return vertexMap.size();
}


/**
* @return Returns the degree of a given vertex.
* @param v Given vertex to return degree.
*/
template <class V, class E>
unsigned int Graph<V,E>::degree(const V & v) const {
  // TODO: Part 2
  //return 0;
  string key = v.key();
  auto lookup = adjList.find(key);
  if(lookup != adjList.end()) {
    return (*adjList.find(v.key())).second.size();
  } else {
    return 0;
  }

}


/**
* Inserts a Vertex into the Graph by adding it to the Vertex map and adjacency list
* @param key The key of the Vertex to insert
* @return The inserted Vertex
*/
template <class V, class E>
V & Graph<V,E>::insertVertex(std::string key) {
  // TODO: Part 2
  V & v = *(new V(key));
  vertexMap.insert(pair<string, V&>(key, v));
  list<edgeListIter> null_list;
  adjList.insert(pair<string, list<edgeListIter> > (key, null_list));
  return v;


}


/**
* Removes a given Vertex
* @param v The Vertex to remove
*/
template <class V, class E>
void Graph<V,E>::removeVertex(const std::string & key) {
  // TODO: Part 2
  auto lookup = vertexMap.find(key);
  if (lookup == vertexMap.end()) { return; }

  vertexMap.erase(key);

  for (auto edgeIt: adjList[key]) {
    removeEdge(edgeIt);
  }
  adjList.erase(key);


}


/**
* Inserts an Edge into the adjacency list
* @param v1 The source Vertex
* @param v2 The destination Vertex
* @return The inserted Edge
*/
template <class V, class E>
E & Graph<V,E>::insertEdge(const V & v1, const V & v2) {
  // TODO: Part 2
  E & e = *(new E(v1, v2));
  auto lookup1 = adjList.find(v1.key());
  auto lookup2 = adjList.find(v2.key());
  if (lookup1 == adjList.end() || lookup2 == adjList.end()) { return e; }

  edgeList.push_front(e);
  edgeListIter it = edgeList.begin();
  // if undirected, add to dest and source; else only add to source
  if (!e.directed()) {
    (lookup2 -> second).push_front(it);
  }
  (lookup1 -> second).push_front(it);

  return e;

}


/**
* Removes an Edge from the Graph
* @param key1 The key of the source Vertex
* @param key2 The key of the destination Vertex
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const std::string key1, const std::string key2) {
  // TODO: Part 2
  auto lookup1 = vertexMap.find(key1);
  auto lookup2 = vertexMap.find(key2);
  if (lookup1 == vertexMap.end() || lookup2 == vertexMap.end()) { return; }

  for (auto edgIt: adjList[key1]) {

      if ((edgIt -> get()).dest().key() == key2) {
          removeEdge(edgIt);
          return;
      }

  }

}


/**
* Removes an Edge from the adjacency list at the location of the given iterator
* @param it An iterator at the location of the Edge that
* you would like to remove
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const edgeListIter & it) {
  // TODO: Part 2
  auto sourceV = (it -> get()).source();
  auto destV = (it -> get()).dest();
// if edge is direced, only find in the source vertex
if ((it -> get()).directed()) {

  for (auto edgIt : adjList.at(sourceV.key())) {
    if (edgIt == it) {
      adjList.at(sourceV.key()).remove(edgIt);
    }
  }

} else {

  for (auto edgIt1 : adjList.at(sourceV.key())) {
    if (edgIt1 == it) {
      adjList.at(sourceV.key()).remove(edgIt1);
    }
  }

  for (auto edgIt2 : adjList.at(destV.key())) {
    if (edgIt2 == it) {
      adjList.at(destV.key()).remove(edgIt2);
    }
  }

}

edgeList.erase(it);



}


/**
* @param key The key of an arbitrary Vertex "v"
* @return The list edges (by reference) that are adjacent to "v"
*/
template <class V, class E>
const std::list<std::reference_wrapper<E>> Graph<V,E>::incidentEdges(const std::string key) const {
  // TODO: Part 2
  std::list<std::reference_wrapper<E>> edges;
  std::list<edgeListIter> edgelist = adjList.find(key)->second;
  for (auto it : edgelist) {
    edges.push_front(it->get());
  }
  return edges;
}


/**
* Return whether the two vertices are adjacent to one another
* @param key1 The key of the source Vertex
* @param key2 The key of the destination Vertex
* @return True if v1 is adjacent to v2, False otherwise
*/
template <class V, class E>
bool Graph<V,E>::isAdjacent(const std::string key1, const std::string key2) const {
  // TODO: Part 2
  if (vertexMap.find(key1) == vertexMap.end() || vertexMap.find(key2) == vertexMap.end()) {
   return false;
 }
  string source, dest;
  if (!edgeList.front().get().directed() && degree(key1) > degree(key2)) {
    source = key2;
    dest = key1;
  } else {
    source = key1;
    dest = key2;
  }

  for (auto edgIt: adjList.at(source)) {
    if (edgIt -> get().dest().key() == dest || edgIt -> get().source().key() == dest) { return true; }
  }
  return false;
}