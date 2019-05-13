/* Your code here! */
#include "dsets.h"
#include <vector>

void DisjointSets::addelements(int num) {
  for (int i = 0; i < num; i++) {
    _elems.push_back(-1);
  }
}


int DisjointSets::find(int elem) {
  if ( _elems[elem] < 0) {
    return elem;
  } else {
    int root = find(_elems[elem]);
    _elems[elem] = root;
    return root;
  }

}




void DisjointSets::setunion (int a, int b) {
  a = find(a);
  b = find(b);
  int unionSize = _elems[a] + _elems[b];
  if (_elems[a] < _elems[b]) {
    _elems[b] = a;
    _elems[a] = unionSize;
  } else {
    _elems[a] = b;
    _elems[b] = unionSize;
  }

}

int DisjointSets::size(int elem) {
  return -1*(_elems[find(elem)]);

}
