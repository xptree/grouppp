#ifndef UTIL_H
#define UTIL_H

#include <vector>
#include <string>

using namespace std;

class Util
{
public:
	static vector<string> split(const char* s, char delim);
	static vector<long long> string_to_ll(vector<string>& elems);
	static bool cmpTime(pair<int, int> first, pair<int, int> second);
	static long long getFileSize(const char* fileName);
};

#endif //UTIL_H
