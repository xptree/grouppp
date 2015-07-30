#ifndef GROUP_H
#define GROUP_H

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class Group
{
public:
	Group(const char* userFile, const char* edgeFile);
//	~Group();
private:
	vector<vector<pair<int, int> > > edges;
	vector<vector<pair<int, int> > > users;
};


#endif //GROUP_H