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

vector<long long> Util::string_to_ll(vector<string>& elems)
{
	vector<long long> elems_ll;
	for (size_t i=0; i<elems.size();++i)
		elems_ll.push_back(atoll(elems[i].c_str()));
	return elems_ll;
}
