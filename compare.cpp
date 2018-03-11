#include <iostream>
#include <string.h>
using namespace std;

bool checkArgNum(int argc);

int main(int argc, char *argv[])
{
	if( !checkArgNum(argc))
	{
		cout<<"argc != 2!"<<endl;
		return -2;
	}

	cout<<"arg[1]:"<<argv[1]<<endl;
	cout<<"arg[2]:"<<argv[2]<<endl;
	cout<<strcmp(argv[1], argv[2])<<endl;
	return 0;
}
bool checkArgNum(int argc)
{
	return (argc==3);
}
