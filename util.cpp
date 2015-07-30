#include "util.h"
#include <sstream>

using namespace std;

vector<string> Util::split(const char* s, char delim)
{
	string str(s);
	stringstream ss(str);
	vector<string> elems;
	for (string item; getline(ss, item, delim);elems.push_back(item));
	return elems;
}

vector<int> Util::string_to_int(vector<string>& elems)
{
	vector<int> elems_int;
	for (size_t i=0; i<elems.size();++i)
		elems_int.push_back(atoi(elems[i].c_str()));
	return elems_int;
}
