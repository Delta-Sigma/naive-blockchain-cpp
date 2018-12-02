#include <iostream>
#include <time.h>
#include <string>
using namespace std;

int main()
{
	time_t timestamp;
	time(&timestamp);
	cout << timestamp << endl;
	//string s;
	cout << to_string(timestamp) << endl;
/*	string input;
	while (true)
	{
		getline(cin, input);
		hash <string> hash_fn;
		size_t hash = hash_fn(input);
		cout << hash << endl;
	}
	*/
	//cout << endl << _INT_SIZE;


	system("Pause");
	return 0;
}