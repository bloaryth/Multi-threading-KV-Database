#include<iostream>
#include<fstream>
#include<cstring>
#include<string>
#include<ctime>
#include<cstdlib>
#define random(a,b) (rand()%(b-a+1)+a)
using namespace std;

const int itn = 1000;                      //you can change whatever itn you like here

int main() {
	ofstream out;
	out.open("data.txt");
	
	srand((unsigned)time(NULL));
	for (int i = 1; i <= 100; ++i) {
		string S;
		int length = random(5,25);
			for (int j = 0; j < length; ++j) {
				int num = random(0,61);
				if (num >=0 && num <= 9) {
					S += '0' + num;
				}
				else if (num >= 10 && num <= 35) S += ('a' + num - 10);
				else S += ('A' + num - 36);
			} 
		out << "PUT " << i << ' ' << S << "\n";
	}
	for (int i = 101; i <= itn; ++i) {
		int tmp = random(1,3);
		string String;
		if (tmp == 1) {
			int length = random(5,25);
			for (int j = 0; j < length; ++j) {
				int num = random(0,61);
				if (num >=0 && num <= 9) {
					String += '0' + num;
				}
				else if (num >= 10 && num <= 35) String += ('a' + num - 10);
				else String += ('A' + num - 36);
			} 
			out << "PUT " << i << ' ' << String << "\n";
		}
		else if (tmp == 2) {
			out << "DEL " << random(1,i) << "\n";
		}
		else {
			out << "GET " << random(1,i) << "\n";
		}
	}
	out.close();
	
	return 0;
} 
