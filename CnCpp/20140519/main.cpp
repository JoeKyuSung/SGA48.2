#include <iostream>
#include <fstream>
#include <conio.h>

using namespace std;

struct Item
{
	char name[20];
	int price;
};

int main()
{
	const char* filename = "item.save";

	fstream file;
	bool bExist;

	file.open(filename, ios_base::in);

	if (file.good())
		bExist = true;
	else
		bExist = false;

	file.close();

	if (bExist)
	{
		file.open(filename, ios_base::in | ios_base::binary);
		Item myItem;

		while (file.good())
		{
			if (!file.read((char*)&myItem, sizeof(Item)).good())
				break;

			cout << myItem.name << "\t" << myItem.price << endl;
		}

		file.close();
	}
	else
	{
		file.open(filename, ios_base::out | ios_base::binary);
		Item myItem;

		for (int i = 0; i < 3; i++)
		{
			cout << "Enter Item name : ";
			cin >> myItem.name;

			cout << "Enter Item price : ";
			cin >> myItem.price;

			file.write((const char*)&myItem, sizeof(Item));
		}

		file.close();
	}


	_getch();
	return 0;
}