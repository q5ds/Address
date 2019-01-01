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
//	path = "E:\\"; path += "�ֻ�ͨѶ¼"; path += ".dat";
//	file.open(path.c_str(), ios::out | ios::binary | ios::ate);  //���ļ������û���ļ����������ļ�
//	if (file.is_open())
//	{
//		cout << "�Բ����ļ���ʧ�ܣ�" << endl;
//		return 0;
//	}
//
//	return 0;
//}
enum Flag { SUCCEED, FILE_OPEN_FAILURE, USER_ALREADY_EXISTS };

map<string, long long> directory;				//map�ṩ����һ�ּ�ֵ����������������ݶ��ǳɶԳ��ֵ�
pair<string, long long> user;          //pair��һ��ģ�����ͣ����а�����������ֵ���������ݵ����Ϳ��Բ�ͬ

Flag init();
Flag uinit();

int main() {
	map<string, long long>::iterator t;   //����һ��������
					//��������iterator����һ�ֶ������ܹ�����������׼ģ��������еĲ��ֻ�ȫ��Ԫ�أ�ÿ��������������������е�ȷ���ĵ�ַ��
	char choose;
	bool con = true;
	while (con) {
		cout << "a,����(""����0 0ʱ�˳�"");  b,ɾ��;  c,�޸�;  d,��ѯ�� e,��ӡ;   q,�˳�;\n";
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
						while (cin.get() != '\n');  // cin.get()�Ǳ����س��������������е�.��cin�Ƕ����س���.
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
			// inquery��ѯ
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
