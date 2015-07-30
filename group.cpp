#include "group.h"
#include "util.h"
#include <cstdio>

using namespace std;

#define BUFFER_SIZE 100

Group::Group(const char* userFile, const char* edgeFile)
{
	freopen(userFile, "r", stdin);
	char buffer[BUFFER_SIZE];
	while (fgets(buffer, BUFFER_SIZE, stdin) != NULL) {
		size_t len = strlen(buffer);
		if (len>0 && buffer[len-1]=='\n')
			buffer[len-1] = '\0';
		vector<string> elems = Util::split(buffer, '\t');
		vector<int> elems_int = Util::string_to_int(elems);
		for (size_t i=0; i<elems_int.size(); ++i)
			printf("%d\n", elems_int[i]);
	}
}

