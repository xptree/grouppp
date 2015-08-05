#include "util.h"
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>

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

bool Util::cmpTime(pair<int, int> first, pair<int, int> second) {
	return first.second < second.second;
}

long long Util::getFileSize(const char* fileName) // path to file
{
	streampos begin,end;
	ifstream file (fileName, ios::binary);
	begin = file.tellg();
	file.seekg (0, ios::end);
	end = file.tellg();
	file.close();
	return (long long)(end-begin);
}
