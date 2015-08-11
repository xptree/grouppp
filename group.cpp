#include "group.h"
#include "util.h"
#include "disjointSet.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <set>
/*
 * #include "log4cpp/Category.hh"
 * #include "log4cpp/OstreamAppender.hh"
 * #include "log4cpp/Priority.hh"
 * #include "log4cpp/PatternLayout.hh"
 */

using namespace std;

#define BUFFER_SIZE 100
#define every(iter, iterable) auto iter = iterable.begin(); iter != iterable.end(); iter++
Group::Group(const char* userFile, const char* edgeFile) {
	/*
     * log4cpp::Category& root = log4cpp::Category::getRoot();
     * log4cpp::Category& infoCategory = root.getInstance("infoCategory");
     * infoCategory.info("group class constructor called");
	 */
	char buffer[BUFFER_SIZE];
	int last = 1;
	long long loadedBytes = 0;
	long long userFileSize = Util::getFileSize(userFile);
    // infoCategory.info("start loading from %s, size of file %.2fMB", userFile, userFileSize/1024./1024.);
	freopen(userFile, "rb", stdin);
	int room, user, timestamp;
	while (fgets(buffer, BUFFER_SIZE, stdin) != NULL) {
		size_t len = strlen(buffer);
		loadedBytes += len * sizeof(char);
		if (loadedBytes / double(userFileSize) * 100 >= last) {
			// infoCategory.info("%d%% loaded ...", int(loadedBytes / double(userFileSize) * 100));
			last += 10;
		}
		if (len>0 && buffer[len-1]=='\n')
			buffer[len-1] = '\0';
		vector<string> elems       = Util::split(buffer, '\t');
		vector<long long> elems_ll = Util::string_to_ll(elems);
		room      = getGroupId(elems_ll[0]);
		user      = getUserId(elems_ll[1]);
		timestamp = int(elems_ll[2]);
		if (room+1 > groups.size())
			groups.resize(room+1);
		groups[room].push_back(make_pair(user, timestamp));
	}
	fclose(stdin);
	last = 1;
	loadedBytes = 0;
	long long edgeFileSize = Util::getFileSize(edgeFile);
    // infoCategory.info("start loading from %s, size of file %.2fMB", edgeFile, edgeFileSize/1024./1024.);
	freopen(edgeFile, "rb", stdin);
	long long src, dst;
	while (fgets(buffer, BUFFER_SIZE, stdin) != NULL) {
		size_t len = strlen(buffer);
		loadedBytes += len * sizeof(char);
		if (loadedBytes / double(edgeFileSize) * 100 >= last) {
			// infoCategory.info("%d%% loaded ...", int(loadedBytes / double(edgeFileSize) * 100));
			last += 10;
		}
		if (len>0 && buffer[len-1]=='\n')
			buffer[len-1] = '\0';
		vector<string> elems       = Util::split(buffer, '\t');
		vector<long long> elems_ll = Util::string_to_ll(elems);
		src       = getUserId(elems_ll[0]);
		dst       = getUserId(elems_ll[1]);
		timestamp = int(elems_ll[2]);
		if (src+1 > edges.size())
			edges.resize(src+1);
		edges[src].push_back(make_pair(dst, timestamp));
		if (src != dst) {
			if (dst+1 > edges.size())
				edges.resize(dst+1);
			edges[dst].push_back(make_pair(src, timestamp));
		}
	}
	fclose(stdin);
}

Group::~Group() {}

void Group::member(int minSize, int maxSize) {
	/*
     * log4cpp::Category& root = log4cpp::Category::getRoot();
     * log4cpp::Category& infoCategory = root.getInstance("infoCategory");
	 * infoCategory.info("member called");
	 */
	int delta = 60*60*24*30;
	for (size_t group=0; group<groups.size(); ++group) {
		if (groups[group].size()<minSize or groups[group].size()>maxSize)
			continue;
		DisjointSet connection;
		vector<pair<int, int> >& nodes = groups[group];
		vector<int> T;
		map<int, int> joinTime;
		set<int> fringe, currentNode;
		for (size_t i=0; i<nodes.size();++i) {
			T.push_back(nodes[i].second);
			joinTime[nodes[i].first] = nodes[i].second;
		}
		vector<int>::iterator it = unique(T.begin(), T.end());
		T.resize(distance(T.begin(), it));
		int p = 0, checkPoint = T[0] - delta/6*5;
		for (size_t i=0; i<T.size();++i) {
			int t = T[i];
			while (p<nodes.size() and nodes[p].second<=t) {
				int u = nodes[i].first;
				fringe.erase(u);
				currentNode.insert(u);
				for (size_t j=0; j<edges[u].size(); ++j) {
					int v = edges[u][j].first;
					if (currentNode.find(v)==currentNode.end())
						fringe.insert(v);
				}
				++p;
			}
			if (checkPoint+delta<=t) {
				for (set<int>::iterator iter=fringe.begin(); iter!=fringe.end(); ++iter) {
					int u = *iter, k = 0, d = 0;
					set<int> neighbor;
					DisjointSet connection;
					for (size_t j=0;j<edges[u].size();++j){
						int v = edges[u][j].first, timestamp = edges[u][j].second;
						if (timestamp<=t) {
							++d;
							if (currentNode.find(v)!=currentNode.end()) {
								++k;
								neighbor.insert(v);
								connection.makeSet(v);
							}
						} else {
							break;
						}
					}
					for (set<int>::iterator it=neighbor.begin(); it!=neighbor.end(); ++it) {
						int v = *it;
						for (size_t j=0; j<edges[v].size(); ++j) {
							if (connection.getDisconnectComponent() == 1) break;
							int w = edges[v][j].first, timestamp = edges[v][j].second;
							if (timestamp>t) break;
							if (neighbor.find(w) != neighbor.end()) connection.merge(v, w);
						}
					}
					int disconn = connection.getDisconnectComponent();
					int groupSize = int(currentNode.size());
					int numberOfFriendInGroup = k;
					int degree = d;
					bool positive = joinTime.find(u) != joinTime.end() and joinTime[u] <= t+delta;
					auto feature = make_tuple(disconn, groupSize, numberOfFriendInGroup, degree);
					if (attrib.find(feature) == attrib.end())
						attrib[feature] = make_pair(0, 0);
					positive ? ++attrib[feature].first : ++attrib[feature].second;

					/*
					if (k+1 > kFriend.size())
						kFriend.resize(k+1);
					kFriend[k].second += 1;
					if (joinTime.find(u)!=joinTime.end() and joinTime[u]<=t+delta) {
						kFriend[k].first += 1;
						if (k+1 > groupSizeOfKFriend.size())
							groupSizeOfKFriend.resize(k+1);
						int groupSize = currentNode.size();
						if (groupSizeOfKFriend[k].find(groupSize) == groupSizeOfKFriend[k].end())
							groupSizeOfKFriend[k][groupSize] = 0;
						groupSizeOfKFriend[k][groupSize] += 1;
					}
					k = d ? int(double(k) * 100 / d + 0.5) : 0;
					if (k+1>kFractionFriend.size())
						kFractionFriend.resize(k+1);
					kFractionFriend[k].second += 1;
					if (joinTime.find(u)!=joinTime.end() and joinTime[u]<=t+delta)
						kFractionFriend[k].first += 1;
					*/
				}
				checkPoint += 2*delta;
			}
		}
	}
	// infoCategory.info("member completed");
}

void Group::clean() {
	/*
     * log4cpp::Category& root = log4cpp::Category::getRoot();
     * log4cpp::Category& infoCategory = root.getInstance("infoCategory");
	 * infoCategory.info("clean called");
	 */
	for (size_t group=0; group<groups.size(); ++group) {
		vector<pair<int, int> > tmp(groups[group]);
		groups[group].clear();
		sort(tmp.begin(), tmp.end(), Util::cmpTime);
		set<int> Hash;
		for (size_t i=0; i<tmp.size(); ++i) {
			if (Hash.find(tmp[i].first) != Hash.end()) {
				// printf("%lu %d\n", group, tmp[i].first);
				continue;
			}
			Hash.insert(tmp[i].first);
			groups[group].push_back(tmp[i]);
		}
	}
	for (size_t user=0; user<edges.size(); ++user) {
		vector<pair<int, int> > tmp(edges[user]);
		edges[user].clear();
		sort(tmp.begin(), tmp.end(), Util::cmpTime);
		set<int> Hash;
		for (size_t i=0; i<tmp.size(); ++i) {
			if (Hash.find(tmp[i].first) != Hash.end()) {
				// printf("%lu %d\n", user, tmp[i].first);
				continue;
			}
			Hash.insert(tmp[i].first);
			edges[user].push_back(tmp[i]);
		}
	}
	// infoCategory.info("clean completed");
}

void Group::dumpAttrib(const char* outputFile) {
	/*
     * log4cpp::Category& root = log4cpp::Category::getRoot();
     * log4cpp::Category& infoCategory = root.getInstance("infoCategory");
	 * infoCategory.info("dump attrib called");
	 */
	freopen(outputFile, "wb", stdout);
	for (every(it, attrib)) {
		int disconn = get<0>(it->first);
		int groupSize = get<1>(it->first);
		int numberOfFriendInGroup = get<2>(it->first);
		int degree = get<3>(it->first);
		printf("%d\t%d\t%d\t%d\t%d\t%d\n", disconn, groupSize, numberOfFriendInGroup, degree, it->second.first, it->second.second);
	}
	fclose(stdout);
	// infoCategory.info("dump attrib completed");
}
void Group::dump(const char* outputFile) {
	/*
	 * First output the length of kFriend, then output the contents of kFriend.
	 * Second output kFractionFriend.
	 */
	/*
     * log4cpp::Category& root = log4cpp::Category::getRoot();
     * log4cpp::Category& infoCategory = root.getInstance("infoCategory");
	 * infoCategory.info("dump called");
	 */
	freopen(outputFile, "w", stdout);
	printf("%lu\n", kFriend.size());
	for (size_t i=0; i<kFriend.size(); ++i)
		printf("%d\t%d\n", kFriend[i].first, kFriend[i].second);
	printf("%lu\n", kFractionFriend.size());
	for (size_t i=0; i<kFractionFriend.size(); ++i)
		printf("%d\t%d\n", kFractionFriend[i].first, kFractionFriend[i].second);
	for (size_t i=0; i<groupSizeOfKFriend.size(); ++i)
		for (map<int, int>::iterator it=groupSizeOfKFriend[i].begin(); it!=groupSizeOfKFriend[i].end(); ++it) {
			printf("%d\t%d\t%d\n", i, it->first, it->second);
		}
	fclose(stdout);
	// infoCategory.info("dump completed");
}

int Group::getGroupId(long long room) {
	if (groupId.find(room) == groupId.end())
		groupId[room] = groupId.size();
	return groupId[room];
}

int Group::getUserId(long long user) {
	if (userId.find(user) == userId.end())
		userId[user] = userId.size();
	return userId[user];
}
