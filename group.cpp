#include "group.h"
#include "util.h"
#include <cstdio>

using namespace std;

#define BUFFER_SIZE 100

Group::Group(const char* userFile, const char* edgeFile) {
	char buffer[BUFFER_SIZE];
	freopen(userFile, "r", stdin);
	int room, user, timestamp;
	while (fgets(buffer, BUFFER_SIZE, stdin) != NULL) {
		size_t len = strlen(buffer);
		if (len>0 && buffer[len-1]=='\n')
			buffer[len-1] = '\0';
		vector<string> elems = Util::split(buffer, '\t');
		vector<long long> elems_ll = Util::string_to_ll(elems);
		room = getGroupId(elems_ll[0]);
		user = getUserId(elems_ll[1]);
		timestamp = int(elems_ll[2]);
		groups.resize(room+1);
		groups[room].push_back(make_pair(user, timestamp));
	}
	fclose(stdin);
	freopen(edgeFile, "r", stdin);
	long long src, dst;
	while (fgets(buffer, BUFFER_SIZE, stdin) != NULL) {
		size_t len = strlen(buffer);
		if (len>0 && buffer[len-1]=='\n')
			buffer[len-1] = '\0';
		vector<string> elems = Util::split(buffer, '\t');
		vector<long long> elems_ll = Util::string_to_ll(elems);
		src = getUserId(elems_ll[0]);
		dst = getUserId(elems_ll[1]);
		timestamp = int(elems_ll[2]);
		edges.resize(src+1);
		edges[src].push_back(make_pair(dst, timestamp));
		if (src != dst) {
			edges.resize(dst+1);
			edges[dst].push_back(make_pair(src, timestamp));
		}
	}

}

int Group::getGroupId(long long room) {
	map<long long, int>::iterator iter;
	iter = groupId.find(room);
	if (iter != groupId.end())
		groupId[room] = groupId.size();
	return groupId[room];
}

int Group::getUserId(long long user) {
	map<long long, int>::iterator iter;
	iter = userId.find(user);
	if (iter != userId.end())
		userId[user] = userId.size();
	return userId[user];
}
