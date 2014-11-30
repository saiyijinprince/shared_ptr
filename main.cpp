#include "shared_ptr.h"
#include <string>

using namespace std;

int main()
{
	shared_ptr<int> c(new int(5));

	//outer scope
	{
		shared_ptr<string> s(new string("TESTING"));
		shared_ptr<string> t(new string("HEEELLLLLLOOOOOO"));

		//inner scope
		{ 
			shared_ptr<string> new_s(s);
			new_s = t;
		} // t object should have a ref count of 2 before it exits this scope and then 1 after it exits
	
	} // s and t should be deleted when outer scope is exited.
	return 0;
}