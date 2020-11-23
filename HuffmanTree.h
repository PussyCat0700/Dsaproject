#pragma once
#include"Node.h"
class HuffmanTree {
public:
	Node* root;
	HuffmanTree(int _val,char _c);
	HuffmanTree(HuffmanTree* lc, HuffmanTree* rc);
	
};
//:root(&Node(lc->val + rc->val,lc,rc))
HuffmanTree::HuffmanTree(int _val,char _c) {
	root = new Node(_val,_c);
}
HuffmanTree::HuffmanTree(HuffmanTree* lc, HuffmanTree* rc){
	root = new Node(lc->root->val + rc->root->val,lc->root,rc->root);
}
