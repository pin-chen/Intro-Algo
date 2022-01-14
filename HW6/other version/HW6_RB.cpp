#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <string>
using namespace std;

string output;

struct Node{
    string key, value;
    Node *left, *right, *parent;
    string color;
    Node(){} 
    Node(string key, string value){
		this->key = key;
		this->value = value;
		this->parent = nullptr;
		this->left = nullptr;
		this->right = nullptr;
	}
};

class RBTree{
public:
    // constructor
    RBTree(){
        this->NIL = new Node;
        NIL->left = nullptr;
        NIL->right = nullptr;
        NIL->parent = nullptr;
        NIL->color = "black";

        root = NIL; // ini with NIL
    }
    
    Node *root;
    Node *NIL; // represent NIL
    void rbInsert(Node *newNode);
    void rbDelete(Node *target);
    Node* rbSearch(string key);
    void outputNow(string& key1, string& key2);
    void clear();
private:
	void Delete(Node *now);
    void insertFixed(Node *newNode);
    void leftRotat(Node *x);
    void rightRotat(Node *x);
    void rbTransplant(Node *u, Node *v);
    Node* treeMinimum(Node *root);
    void deleteFixed(Node *target);
};

void RBTree::clear(){
	this->Delete(this->root);
	return;
}

void RBTree::Delete(Node *now){
	if(now == nullptr) return;
	this->Delete(now->left);
	this->Delete(now->right);
	delete now;
	return;
}

void RBTree::rbInsert(Node *newNode){
    Node *x = this->root,
         *y = NIL;
    while (x != NIL){
        y = x;
        if (newNode->key < x->key)
            x = x->left;
        else if(newNode->key > x->key)
            x = x->right;
        else{
        	output = "INSERT "+newNode->key+" FAIL!\n";
        	return;
		}    
    }
	output = "INSERT "+newNode->key+" SUCCESS!\n";
    newNode->parent = y;
    if (y == NIL){ // insert root
        this->root = newNode;
        newNode->parent = NIL;
    }
    else if (newNode->key < y->key)
        y->left = newNode;
    else
        y->right = newNode;

    // ini new node
    newNode->left = NIL;
    newNode->right = NIL;
    newNode->color = "red";
    // fix color && rotation
    this->insertFixed(newNode);
}

Node* RBTree::rbSearch(string key){
    Node *x = this->root;
    while (x->key != key && x != NIL){
        if (x->key > key)
            x = x->left;
        else if (x->key < key)
            x = x->right;
    }
    if (x->key == key)
        return x;
    else 
        return nullptr; // not found
}

void RBTree::rbDelete(Node *target){
    Node *y = target,
         *x = nullptr;
    string yOriginColor = target->color;

    if (target->left == NIL){ // only right child
        x = target->right;
        rbTransplant(target, target->right);
    }
    else if (target->right == NIL){ // only left child
        x = target->left;
        rbTransplant(target, target->left);
    }
    else{ // have both child
        y = treeMinimum(target->right);
        yOriginColor = y->color;
        x = y->right;
        if (y->parent == target)
            x->parent = y; // change x's parent even if x == NIL
        else{
            rbTransplant(y, y->right);
            y->right = target->right;
            y->right->parent = y;
        }
        rbTransplant(target, y);
        y->left = target->left;
        y->left->parent = y;
        y->color = target->color;
    }
    
    // deletion fixed up
    if (yOriginColor == "black")
        deleteFixed(x);
    
    delete target;
}

void RBTree::insertFixed(Node *newNode){
    Node *y = nullptr, 
         *z = newNode;
    while (z->parent->color == "red"){
        if (z->parent == z->parent->parent->left){
            y = z->parent->parent->right;

            if (y->color == "red"){ // case 1
                z->parent->color = "black";
                y->color = "black";
                z->parent->parent->color = "red";
                z = z->parent->parent;
            }
            else{
                if (z == z->parent->right){ // case 2
                    z = z->parent;
                    this->leftRotat(z);
                }
                z->parent->color = "black"; // case 3
                z->parent->parent->color = "red";
                this->rightRotat(z->parent->parent);
            }
        }
        else {
            y = z->parent->parent->left;

            if (y->color == "red"){ // case 4
                z->parent->color = "black";
                y->color = "black";
                z->parent->parent->color = "red";
                z = z->parent->parent;
            }
            else{
                if (z == z->parent->left){ // case 5
                    z = z->parent;
                    this->rightRotat(z);
                }
                z->parent->color = "black"; // case 6
                z->parent->parent->color = "red";
                this->leftRotat(z->parent->parent);
            }
        }
    }
    this->root->color = "black";
}

void RBTree::leftRotat(Node *x){
    Node *y = x->right;
    // append y left to x right
    x->right = y->left;
    if (y->left != NIL)
        y->left->parent = x;
    // Link y to x parent
    y->parent = x->parent;
    if (x->parent == NIL) // x is root
        this->root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    // Link y and x
    y->left = x;
    x->parent = y;
}

void RBTree::rightRotat(Node *x){
    Node *y = x->left;
    // append y right to x left
    x->left = y->right;
    if (y->right != NIL)
        y->right->parent = x;
    // Link y to x parent
    y->parent = x->parent;
    if (x->parent == NIL)
        this->root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    // Link y and x
    y->right = x;
    x->parent = y;
}

void RBTree::rbTransplant(Node *u, Node *v){
    if (u->parent == NIL) // root
        this->root = u;
    else if (u == u->parent->left) // u is left child
        u->parent->left = v;
    else    // u is right child
        u->parent->right = v; 
    v->parent = u->parent;
}

Node* RBTree::treeMinimum(Node *root){
    Node *x = root,
         *formor = nullptr;
    while (x != NIL){ // find leftest
        formor = x;
        x = x->left;
    }
    return formor;
}

void RBTree::deleteFixed(Node *x){
    Node *sible = nullptr;
    while (x != this->root && x->color == "black"){
        if (x == x->parent->left){
            sible = x->parent->right; // x's sibling
            // case1: x sibling red
            if (sible->color == "red"){
                sible->color = "black";
                x->parent->color = "red";
                leftRotat(x->parent);
                sible = x->parent->right;
            }
            // case2: x sibling black, two childs black
            if (sible->left->color == "black" && sible->right->color == "black"){
                sible->color = "red";
                x = x->parent;
            }
            else{
                // case3: sibling have right red
                if (sible->right->color == "black"){
                    sible->left->color = "black";
                    sible->color = "red";
                    rightRotat(sible);
                    sible = x->parent->right;
                }
                // case4: sibling have left red (must became case 4 after case 3)
                sible->color = x->parent->color;
                x->parent->color = "black"; // avoid double red
                sible->right->color = "black";
                leftRotat(x->parent);
                x = this->root;
            }
        }
        else{ // x is right child
            sible = x->parent->left; // x's sibling
            // case1: x sibling red
            if (sible->color == "red"){
                sible->color = "black";
                x->parent->color = "red";
                rightRotat(x->parent);
                sible = x->parent->left;
            }
            // case2: x sibling black, two childs black
            if (sible->left->color == "black" && sible->right->color == "black"){
                sible->color = "red";
                x = x->parent;
            }
            else{
                // case3: sibling have left red
                if (sible->left->color == "black"){
                    sible->right->color = "black";
                    sible->color = "red";
                    leftRotat(sible);
                    sible = x->parent->left;
                }
                // case4: sibling have right red (must became case 4 after case 3)
                sible->color = x->parent->color;
                x->parent->color = "black"; // avoid double red
                sible->left->color = "black";
                rightRotat(x->parent);
                x = this->root;
            }
        }
    }
    x->color = "black";
}

void RBTree::outputNow(string& key1, string& key2){
    output = "";
    // output with inorder traversal (iterative)
    stack<Node*> stk;
    Node *now = this->root;
    while ( !stk.empty() || now != NIL){
        // first left
        if (now != NIL){
            stk.push(now);
            now = now->left;
        }
        else{
            Node *top = stk.top();
            stk.pop();
            if(key1 <= top->key && key2 >= top->key){
				output += "ENUM "+top->key+":"+top->value+"\n";
			}
            now = top->right; // right
        }
    }
    
}
int main(){
	ifstream in("input.txt");
	ofstream out("output.txt");
	string cmd, key, value;
	RBTree bst;
	while(in >> cmd){
		//cout << bst.root->key << '\n';
		switch(cmd[2]){
			case 'S':{//insert
				in >> key >> value;
				key.erase(0,4);
				value.erase(0,6);
				Node* node = new Node(key, value);
				bst.rbInsert(node);
				break;
			}
			case 'N':{//find
				in >> key;
				key.erase(0,4);
				Node* x = bst.rbSearch(key);
				if(x == nullptr){
					output = key+" NOT FOUND!\n";
				}else{
					output = "FIND "+key+":"+x->value+"!\n";
				}
				break;
			}
			case 'A':{//erase
				in >> key;
				key.erase(0,4);
				Node* x = bst.rbSearch(key);
				if(x == nullptr){
					output = "ERASE "+key+" FAIL!\n";
				}else{
					output = "ERASE "+key+" SUCCESS!\n";
					bst.rbDelete(x);
				}
				
				break;
			}
			case 'U':{//enum
				in >> key >> value;
				key.erase(0,4);
				value.erase(0,4);
				bst.outputNow(key, value);
				break;
			}
			case 'E':{//clear
				bst.clear();
				break;
			}
		}
		out << output;
	}
	
	return 0;
}
