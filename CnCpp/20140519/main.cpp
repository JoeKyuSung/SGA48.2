#include <iostream>
#include <fstream>
#include <conio.h>

using namespace std;

int main()
{
	const char* filename = "item.save";

	fstream file;

	// write
	//file.open(filename, ios_base::out | ios_base::binary);

	//int i;

	//cout << "Enter integer : ";
	//cin >> i;
	//file.write((const char*)&i, sizeof(int));

	// read
	file.open(filename, ios_base::in | ios_base::binary);

	int i;
	file.read((char*)&i, sizeof(int));

	cout << i;


	file.close();

	_getch();
	return 0;
}