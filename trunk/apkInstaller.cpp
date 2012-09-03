#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <direct.h>
using namespace std;

void main()
{
	string dir, apkName, command;
	ifstream fin;
	cout << "Directory with .apk's to be installed (push Enter if Current Directory): ";
	getline(cin, dir);
	for (unsigned int c=0;c<dir.size();c++)
	{
		if (*(dir.begin()+c)=='\\')
		{
			dir.insert(dir.begin()+c,'\\');
			c++;
		}
	}
	if (!dir.empty()) //if not in right directory, change to it
		_chdir(dir.c_str());

	system("dir /b *.apk > install"); //create install.txt with .apk names

	fin.open("install");
	while (getline(fin,apkName))
	{
		apkName.insert(apkName.begin(),'\"'); apkName.insert(apkName.end(),'\"');
		command = "adb install "+apkName;
		system(command.c_str());
	}
	fin.close(); fin.clear();
	system("del install");
	cout << "\nComplete";
}