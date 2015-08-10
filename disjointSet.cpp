/*
 * File Name: disjointSet.cpp
 * Author: YOUR NAME
 * Create Time: 2015/08/10 01:36
 * TODO:
 */

#include "disjointSet.h"
#include <cstdio>
#include <cstdlib>

void DisjointSet::makeSet(int u) {
	if (father.find(u) == father.end()) {
		father[u] = u;
		disconnectComponent += 1;
	}
}

int DisjointSet::find(int u) {
	int root = u;
	for (; root!=father[root]; root=father[root])
	for (int x=u, oldfather=0; x!=root; x=oldfather) {
		oldfather = father[x];
		father[x] = root;
	}
	return root;
}

void DisjointSet::merge(int u, int v) {
	int x = find(u), y = find(v);
	if (x != y) {
		father[x] = y;
		disconnectComponent -= 1;
	}
}
int DisjointSet::getDisconnectComponent() const {
	return disconnectComponent;
}
