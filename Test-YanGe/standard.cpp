#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<map>
#include<fstream>
using namespace std;

map<int,string> standard;

int main() {
	fstream out;
	
	freopen("data.txt","r",stdin);
	
	string s;
	while(cin >> s) {              //!cin.eof()
		int index;
		string String;
		if (s == "PUT") {
			cin >> index;
			cin >> String;
			standard[index]=String;
			
		}
		else if (s == "DEL") {
			cin >> index;
			map<int,string>::iterator iter = standard.begin();
			for (;iter != standard.end();) {
				if (iter -> first == index) {
					standard.erase(iter++);
				}
				else {
					++iter;
				}
			}
		}
		else if (s == "GET") {
			cin >> index;
			map<int,string>::iterator iter;
			iter = standard.find(index);
			if (iter != standard.end()){
				cout << iter -> second << "\n";
			}
			else cout << "Not found!\n";
			if (cin.eof()) break;
		}
	}
	
	return 0;
} 
