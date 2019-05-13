#include <queue>
#include <algorithm>
#include <string>
#include <list>
#include <unordered_map>
#include <limits>
using namespace std;
# define INF 0x3f3f3f3f

/**
 * Returns an std::list of vertex keys that creates some shortest path between `start` and `end`.
 *
 * This list MUST include the key of the `start` vertex as the first vertex in the list, the key of
 * the `end` vertex as the last element in the list, and an ordered list of all vertices that must
 * be traveled along the shortest path.
 *
 * For example, the path a -> c -> e returns a list with three elements: "a", "c", "e".
 *
 * @param start The key for the starting vertex.
 * @param end   The key for the ending vertex.
 */
template <class V, class E>
 std::list<std::string> Graph<V,E>::shortestPathBFS(const std::string start, const std::string end) {

  queue<string> q_;
  unordered_map<string, string> parents; // child, parent
  unordered_map<string, bool> visited_;
  vector<list<string> > paths;
  
  q_.push(start);
  while (!q_.empty()) {
    string current = q_.front();
    q_.pop();
    visited_[current] = true;

    if (current == end) {
            list<string> path;
            string cur = current;
            path.push_front(cur);
            while (cur != start) {
              string parent = parents[cur];
              path.push_front(parent);
              cur = parent;
            }
            paths.push_back(path);
     }
    
    list<E_byRef> edges = incidentEdges(current);
    for (auto edge: edges) {
      string child = edge.get().dest().key();
      if (child == current) { child = edge.get().source().key(); }
      if (!visited_[child]) {
          q_.push(child);
          visited_[child] = true;
          parents.insert(pair<string, string>(child, current));   
      }
    }

  }
 
    int idx = 0;
    int shortest = paths[0].size();
    for (int i = idx; i < (int)paths.size(); i++) {
      if ((int)paths[i].size() < shortest) {
        shortest = paths[i].size();
        idx = i;
      }
    }
    return paths[idx];
}



/* This algorithm use Dijkstra's MST approach */
template <class V, class E>
 std::list<std::string> Graph<V,E>::shortestPath(const std::string start, const std::string end) {

   unordered_map<string, int>dist;
   unordered_map<string, string>parents; // child, parent
   unordered_map<string, bool>visited; 
   queue<string> pq; // does not have any properties maintaining min, should maintain in the loop



   int vertexSize = (int)vertexMap.size();
   
   for (auto thepair : vertexMap) {
     dist.insert(pair<string, int>(thepair.first, INT_MAX));
     parents.insert(pair<string,string>(thepair.first, "NA"));
     visited.insert(pair<string, bool>(thepair.first, false));
   }

   dist[start] = 0;
   visited[start] = true;
   pq.push(start);

   while(!pq.empty()) {
      string current = pq.front();
      pq.pop();
      visited[current] = true;

      list<E_byRef> edges = incidentEdges(current);
      for (auto edge : edges) {
        string child = edge.get().dest().key();
        if (child == current) { child = edge.get().source().key(); }
        
        int edgeWeight = (int)(edge.get().weight());
        if ((!visited[child]) && (dist[current] + edgeWeight) < dist[child]) {
          dist[child] = (dist[current] + edgeWeight);
          parents[child] = current;
        }
      }
      //maintaining pq, sort by distance 
      UpdatingPQ(pq, visited, dist);
    }

    list<string> path;
    path.push_front(end);
    string current = end;
    while (current != start) {
      string parent = parents[current];
      path.push_front(parent);
      current = parent;
    }
    return path;

 }

/* helper function, sort the priority queue by distance, so that the element with shortest distance is at the front */
 template <class V, class E>
 void Graph<V,E>::UpdatingPQ(queue<string> &pq,  unordered_map<string, bool> &visited,  unordered_map<string, int> &dist) {
      int min = INT_MAX;
      int realIDX= -1;
      int IDX = 0;
      for (auto pair2: vertexMap) {
        
        if((!visited[pair2.first]) && dist[pair2.first] < min) {
          min = dist[pair2.first];
          realIDX = IDX;
        }
        IDX++;
      }
      if(realIDX >= 0) {
        auto it = vertexMap.begin();
        while (realIDX > 0) {
          it++;
          realIDX--;
        }
        pq.push((*it).first);
      }

 
 }
