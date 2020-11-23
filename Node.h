#pragma once
class Node {
public:
	int val;
	char c;
	Node* lchild, * rchild;
	Node(int _val,Node * lc,Node * rc);
	Node(int _val,char _c);
};
Node::Node(int _val, Node* lc, Node* rc):val(_val),lchild(lc),rchild(rc),c(0){}
Node::Node(int _val,char _c=0):val(_val),lchild(nullptr),rchild(nullptr),c(_c){}