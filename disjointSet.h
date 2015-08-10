#ifndef DISJOINTSET_H
#define DISJOINTSET_H

#include <unordered_map>

using namespace std;

class DisjointSet
{
public:
	DisjointSet() { disconnectComponent = 0; }
	~DisjointSet() {}
	void makeSet(int u);
	int find(int u);
	void merge(int u, int v);
	int getDisconnectComponent() const;
private:
	unordered_map<int, int> father;
	int disconnectComponent;
};

#endif //DISJOINTSET_H
