#ifndef GROUP_H
#define GROUP_H

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <unordered_map>
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
	void dump(const char* outputFile);
private:
	vector<vector<pair<int, int> > > edges, groups;
	unordered_map<long long, int> groupId, userId;
	vector<pair<int, int> > kFriend, kFractionFriend;
	vector<map<int, int> > groupSizeOfKFriend;

	int getGroupId(long long room);
	int getUserId(long long user);
};


#endif //GROUP_H
