#ifndef UTIL_H
#define UTIL_H

#include <vector>
#include <string>

using namespace std;

class Util
{
public:
	static vector<string> split(const char* s, char delim);
	static vector<int> string_to_int(vector<string>& elems);
};

#endif //UTIL_H
