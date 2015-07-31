#include "group.h"

using namespace std;

int main()
{
	Group group("user_10000", "edge_10000");
	group.clean();
	group.member(10,1000);
	group.dump("output.txt");
	return 0;
}
