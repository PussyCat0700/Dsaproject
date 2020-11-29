#include<iostream>
#include<vector>//
#include<fstream>//
#include<queue>//为了用优先队列
#include<string>
#include<unordered_map>//
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
	/*
	 * 第一个vector容器，名字为Stat,长度256
	 * 用于对ASCII范围内的256个字符出现的频度进行统计；
	 * 每一个元素的下标代表其ASCII码，值代表其出现次数
	 */
	string ifile("D:\\in.txt"), ofile("D:\\out.txt");
	ifstream ifs(ifile);
	ofstream ofs(ofile);
	char c;
	while (ifs >> c) ++Stat.at(c);
	//统计各字符出现次数，并写入Stat容器中
	//（这里利用了元素下标即ASCII码的性质,
	//从文件读入字符写入char变量c后，以c的值【ASCII码】进行索引）
	/*for (size_t i = 0; i < 256; ++i) {
		if (Stat.at(i) != 0) cout << char(i) << "times:" << Stat.at(i) << endl;
	}*/
	//废弃的打印语句，用于检查容器Stat是否存放了所有的值
	vector<HuffmanTree*> setOfHuffman;
	/*
	 * 第二个也是最后一个vector容器，名字为setOfHuffman，长度未定
	 * 这个容器存放根据Stat的统计结果生成的Huffman树【指针形式】
	 * 从这一步开始，Huffman树的建立正式开始，有兴趣的同学可以翻看教材比较步骤哦~基本一致
	 */
	for (size_t i = 0; i < 256; ++i) {
		if (Stat.at(i) != 0) setOfHuffman.push_back(new HuffmanTree(Stat.at(i), char(i)));
	}
	//根据Stat结果建树，树放入setOfHuffman容器中（对应教材第一步，这时候的树都只有一个结点）。
	for (const auto& i : setOfHuffman) {
		cout << i->root->c << " " << i->root->val << endl;
	}
	//打印语句，用于检查容器setOfHuffman是否按照Stat的内容正确存放了所有的树。
	priority_queue<HuffmanTree*,vector<HuffmanTree *> , cmp> p;
	/* 接下来我们要对树进行合并和排序，这两件事都可以通过对优先队列的操作完成！
	 * 定义：priority_queue<Type, Container, Functional>
	 * Type 就是数据类型;
	 * Container 就是容器类型;
	 * （Container必须是用数组实现的容器，比如vector,deque等等，但不能用 list。STL里面默认用的是vector）
	 * Functional 就是比较的方式。
	 * 这里昊昊写的是存放Huffman树的小顶堆，名字叫p，和Huffman树的构造需求一致
	 * 参见教材：优先队列与堆
	 */
	for (const auto& i : setOfHuffman) {
		p.push(i);
	}
	//将setOfHuffman里的所有单结点树放入优先队列p，树的合并要正式开始了！
	while (p.size() != 1) {
		auto* t1 = p.top();
		p.pop();
		auto* t2 = p.top();
		p.pop();
		HuffmanTree* t = new HuffmanTree(t1, t2);
		p.push(t);
	}
	//由于标准库queue支持的priority_queue在每次pop后都会自动排序，
	//所以我们只需要让它像计算器一样：每次弹出，弹出，合并，放回就好。
	//直到p只剩一个树，这个树就是我们的Huffman编码树
	//（对应教材第二步以后的步骤）
	//cout << p.top()->root->val;
	unordered_map<char, string> CodeMap;
	codeForChars(p.top()->root, CodeMap, "");
	for (const auto& i : CodeMap) {
		cout << i.first << " " << i.second << endl;
	}
	/*
	 * 树构造完以后还不够，我们得想办法去给字符编码
	 * 昊昊写了一个名叫CodeMap的哈希表（unordered_map)
	 * 用codeForChars函数将这个哈希表构建起来：
	 * char（字符）->string（编码）
	 * 然后打印出来（对应哈希表内容，first是Key，second是Value）
	 */
	getchar();
	return 0;
}
