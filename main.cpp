#include<iostream>
#include<vector>
#include<fstream>
#include<queue>
#include<string>
#include<unordered_map>
#include"Node.h"
#include"HuffmanTree.h"
using namespace std;
struct cmp {
	bool operator() (const HuffmanTree* pt1, const HuffmanTree* pt2) {
		return pt1->root->val > pt2->root->val;
	}
};
void codeForChars(Node * root, unordered_map<char, string>& codeMap,string now) {
	
	if (root == nullptr) return;
	if(root->c != 0) codeMap[root->c] = now;
	codeForChars(root->lchild, codeMap, now + "0");
	codeForChars(root->rchild, codeMap, now + "1");
}
int main() {
	vector<int> Stat(256);
	string ifile("D:\\in.txt"), ofile("D:\\out.txt");
	ifstream ifs(ifile);
	ofstream ofs(ofile);
	char c;
	while (ifs >> c) ++(Stat.at(c));
	/*for (size_t i = 0; i < 256; ++i) {
		if (Stat.at(i) != 0) cout << char(i) << "times:" << Stat.at(i) << endl;
	}*/
	vector<HuffmanTree*> setOfHuffman;
	for (size_t i = 0; i < 256; ++i) {
		if (Stat.at(i) != 0) setOfHuffman.push_back(new HuffmanTree(Stat.at(i), char(i)));
	}
	priority_queue<HuffmanTree*,vector<HuffmanTree *> , cmp> p;
	for (const auto& i : setOfHuffman) {
		cout <<i->root->c<<" "<< i->root->val<<endl;
	}
	for (const auto& i : setOfHuffman) {
		p.push(i);
	}
	
	while (p.size() != 1) {
		auto t1 = p.top();
		p.pop();
		auto t2 = p.top();
		p.pop();
		HuffmanTree* t = new HuffmanTree(t1, t2);
		p.push(t);
	}
	//cout << p.top()->root->val;
	unordered_map<char, string> CodeMap;
	codeForChars(p.top()->root, CodeMap, "");
	for (const auto& i : CodeMap) {
		cout << i.first << " " << i.second << endl;
	}
	return 0;
}