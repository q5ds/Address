#include <stdio.h>
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <utility>
#include <algorithm>
#define filename "directory.txt"
using namespace std;
//
//int main()
//{
//	fstream file;
//	string path;
//	path = "E:\\"; path += "手机通讯录"; path += ".dat";
//	file.open(path.c_str(), ios::out | ios::binary | ios::ate);  //打开文件，如果没有文件，则创立新文件
//	if (file.is_open())
//	{
//		cout << "对不起，文件打开失败！" << endl;
//		return 0;
//	}
//
//	return 0;
//}
enum Flag { SUCCEED, FILE_OPEN_FAILURE, USER_ALREADY_EXISTS };

map<string, long long> directory;				//map提供的是一种键值对容器，里面的数据都是成对出现的
pair<string, long long> user;          //pair是一种模板类型，其中包含两个数据值，两个数据的类型可以不同

Flag init();
Flag uinit();

int main() {
	map<string, long long>::iterator t;   //声明一个迭代器
					//迭代器（iterator）是一种对象，它能够用来遍历标准模板库容器中的部分或全部元素，每个迭代器对象代表容器中的确定的地址。
	char choose;
	bool con = true;
	while (con) {
		cout << "a,创建(""输入0 0时退出"");  b,删除;  c,修改;  d,查询； e,打印;   q,退出;\n";
		cin >> choose;
		switch (choose) {
			// create
		case 'a':
			if (init() == FILE_OPEN_FAILURE) {
				cout << "FILE OPEN FAILURE" << endl;
				exit(0);
			}
			if (directory.empty() == false)
				cout << "The Directory Already Exist\n";
			else {
				user.first = 1;
				while (user.first != "0" || user.second != 0) {
					cin >> user.first >> user.second;
					directory.insert(user);
					if (cin.good() == false) {
						cin.clear();
						while (cin.get() != '\n');  // cin.get()是保留回车在输入流队列中的.而cin是丢弃回车的.
						cout << "Input Error!\nPlease Try Again\n";
					}
				}
			}
			break;
			// delete
		case 'b':
			cin >> user.first;
			for (t = directory.begin(); t != directory.end(); ++t)
				if (user.first == t->first)
					break;
			if (directory.end() == t)
				cout << "No this user\n";
			else
				directory.erase(t);
			break;
			// change
		case 'c':
			cin >> user.first;
			for (t = directory.begin(); t != directory.end(); ++t)
				if (user.first == t->first)
					break;
			if (directory.end() == t)
				cout << "No this user\n";
			else {
				cin >> user.second;
				directory[user.first] = user.second;
			}
			break;
			// inquery查询
		case 'd':
			cin >> user.first;
			for (t = directory.begin(); t != directory.end(); ++t)
				if (user.first == t->first)
					break;
			if (directory.end() == t)
				cout << "No this user\n";
			else
				cout << t->second << endl;
			break;
			// print
		case 'e':
			for (t = directory.begin(); t != directory.end(); ++t)
				cout << t->first << '\t' << t->second << endl;
			break;
		case 'q':
			uinit();
			con = false;
			break;
		default:
			cout << "Input Error!\nTry Again!" << endl;
			cin >> choose;
		}
	}
}

Flag init() {
	fstream infile;
	infile.open(filename, std::fstream::in);
	if (infile.is_open() == false)
		return FILE_OPEN_FAILURE;

	while (infile.good()) {
		infile >> user.first >> user.second;
		if (user.first != "")
			directory.insert(user);
	}

	infile.close();
	return SUCCEED;
}

Flag uinit() {
	fstream outfile;
	outfile.open(filename, std::fstream::out);
	if (outfile.is_open() == false)
		return FILE_OPEN_FAILURE;

	for (auto t = directory.begin(); t != directory.end(); ++t) {
		if (t != directory.begin())
			cout << endl;
		outfile << t->first << ' ' << t->second;
	}

	return SUCCEED;
}
