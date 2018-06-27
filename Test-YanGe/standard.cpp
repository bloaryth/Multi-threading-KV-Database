#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<map>
#include<fstream>
#include<ctime>
using namespace std;

map<int,string> standard;

int main() {
	
	clock_t stTime = clock();
	
	fstream out;
	
	freopen("data.txt","r",stdin);
	freopen("stdout.txt", "w", stdout);
	
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
			
			bool flag = false;
			
			for (;iter != standard.end();) {
				if (iter -> first == index) {
					standard.erase(iter++);
					flag = true;
				}
				else {
					++iter;
				}
			}
			if(iter == standard.end() && !flag)
			{
				cout << "Del " << index << " failed.\n";
			}
		}
		else if (s == "GET") {
			cin >> index;
			map<int,string>::iterator iter;
			iter = standard.find(index);
			if (iter != standard.end()){
				cout << iter -> second << "\n";
			}
			else cout << "Get " << index << " failed.\n";
			if (cin.eof()) break;
		}
	}
	
	clock_t edTime = clock();
	
	cerr << "Elapsed Time: " << (edTime - stTime) / (double)CLOCKS_PER_SEC << "\n";
	
	return 0;
} 
