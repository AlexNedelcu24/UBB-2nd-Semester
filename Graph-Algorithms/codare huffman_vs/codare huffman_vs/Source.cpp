#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;

ifstream in("f.in");
ofstream out("f.out");

string text;
int freq[256]{};
int letters = 0;
string code[256];

struct FreqPair {
	int freq = 0;
	char chr = 0;
	bool operator<(const FreqPair& oth) const {
		return freq < oth.freq || (freq == oth.freq && chr < oth.chr);
	}
};

multimap<FreqPair, string> Q;

int main()
{
	getline(in, text);

	for (char chr : text) {
		freq[int(chr)]++;
		if (freq[int(chr)] == 1) letters++;
	}

	out << letters << '\n';
	for (int i = 0; i < 256; ++i) {
		if (freq[i]) {
			out << char(i) << " " << freq[i] << '\n';
			Q.insert({ { freq[i], char(i) }, string(1, i) });
		}
	}

	while (--letters) {
		auto x = *Q.begin();
		for (char chr : x.second) {
			code[int(chr)] = "0" + code[int(chr)];
		}
		Q.erase(Q.begin());

		auto y = *Q.begin();
		for (char chr : y.second) {
			code[int(chr)] = "1" + code[int(chr)];
		}
		Q.erase(Q.begin());

		Q.insert({ { x.first.freq + y.first.freq, min(x.first.chr, y.first.chr) }, x.second + y.second });
	}

	for (char chr : text) {
		out << code[int(chr)];
	}
}