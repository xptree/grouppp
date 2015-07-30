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
	~Group();
	void member(int minSize=10, int maxSize=1000);
	void clean();
private:
	vector<vector<pair<int, int> > > edges;
	vector<vector<pair<int, int> > > groups;
	map<long long, int> groupId;
	map<long long, int> userId;

	int getGroupId(long long room);
	int getUserId(long long user);
};


#endif //GROUP_H
