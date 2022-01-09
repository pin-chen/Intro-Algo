#pragma GCC optimize("Ofast,unroll-loops")
#include <fstream>
#include <string>

std::string output;

struct node{
	std::string key, value;
	node *parent, *left, *right;
	node(std::string& key, std::string& value, node* parent){
		this->key = key;
		this->value = value;
		this->parent = parent;
		this->right = nullptr;
		this->left = nullptr;
	}
	node(std::string& key, std::string& value){
		this->key = key;
		this->value = value;
		this->parent = nullptr;
		this->right = nullptr;
		this->left = nullptr;
	}
};

class BST{
	private:
		node *root, *R;
		std::string tmp2;
		bool t2;
		void Delete(node* now);
		void printn(node* now);
		void Level(node* now);
		void RR(node* now);
		void LR(node* now);
		void splay(node* now);
	public:
		BST();
		~BST();
		void Insert(std::string& key, std::string& value);
		void erase(std::string& key);
		node* search(std::string& key);
		void Enum(std::string& key1, std::string& key2);
		void clear();
};

BST::BST(){
	root = nullptr;
}

BST::~BST(){
	this->clear();
}

node* BST::search(std::string& key){
	for(node *now = this->root;;){
		if(now == nullptr){
			return nullptr;
		}else if(key > now->key){
			now = now->right;
		}else if(key < now->key){
			now = now->left;
		}else{
			return now;
		}
	}
}

void BST::Insert(std::string& key, std::string&value){
	if(root == nullptr){
		root = new node(key, value);
		output = "INSERT "+key+" SUCCESS!\n";
		return;
	}
	for(node *now = this->root;;){
		if(key > now->key){
			if(now->right == nullptr){
				now->right = new node(key, value, now);
				output = "INSERT "+key+" SUCCESS!\n";
				splay(now);
				return;
			}
			now = now->right;
		}else if(key < now->key){
			if(now->left == nullptr){
				now->left = new node(key, value, now);
				output = "INSERT "+key+" SUCCESS!\n";
				splay(now);
				return;
			}
			now = now->left;
		}else{
			output = "INSERT "+key+" FAIL!\n";
			return;
		}
	}
}

void BST::erase(std::string& key){
	node* now = this->search(key);
	if(now == nullptr){
		output = "ERASE "+key+" FAIL!\n";
		return;
	}
	node *x, *y;
	if(now->left == nullptr || now->right == nullptr){
		y = now;
	}else{
		for(y = now->right; y->left != nullptr; y = y->left);
	}
	if(y->left != nullptr){
		x = y->left;
	}else{
		x = y->right;
	}
	if(x != nullptr){
		x->parent = y->parent;
	}
	if(y->parent == nullptr){
		this->root = x;
	}else if(y == y->parent->left){
		y->parent->left = x;
	}else{
		y->parent->right = x;
	}
	if(y != now){
		now->key = y->key;
		now->value = y->value;
	}
	delete y;
	output = "ERASE "+key+" SUCCESS!\n";
}

void BST::clear(){
	this->Delete(this->root);
}

void BST::Delete(node *now){
	if(now == nullptr) return;
	this->Delete(now->left);
	this->Delete(now->right);
	delete now;
}

void BST::Level(node *now){
	if(now == nullptr) return;
	if(t2 || tmp2 >= now->key){
		this->R = now;
		return;
	}
	this->Level(now->left);
	this->Level(now->right);
}

void BST::Enum(std::string& key1, std::string& key2){
	node* now = this->search(key1);
	this->t2 = !(bool) this->search(key2);
	this->tmp2 = key2;
	output = "";
	if(now){
		splay(now);
		output += "ENUM "+now->key+":"+now->value+"\n";
		this->printn(now->right);
	}else{
		this->Level(this->root);
		this->printn(this->R);
	}
}

void BST::printn(node* now){
	if(now == nullptr) return;
	printn(now->left);
	if(t2 || tmp2 >= now->key){
		output += "ENUM "+now->key+":"+now->value+"\n";
	}
	printn(now->right);
}

void BST::LR(node* now){
	node* y = now->right;
    now->right = y->left;
    if(y->left != nullptr) 				y->left->parent = now;
    y->parent = now->parent;
    if(now->parent == nullptr)	 		this->root = y;
    else if (now == now->parent->left)	now->parent->left = y;
    else								now->parent->right = y;
    y->left = now;
    now->parent = y;
}

void BST::RR(node* now){
	node* y = now->left;
    now->left = y->right;
    if (y->right != nullptr)			y->right->parent = now;
    y->parent = now->parent;
    if (now->parent == nullptr)			this->root = y;
    else if (now == now->parent->left)	now->parent->left = y;
    else								now->parent->right = y;
    y->right = now;
    now->parent = y;
}

void BST::splay(node* now){
	for(;now->parent != nullptr;){
	    if(now->parent->parent == nullptr){
	        if (now->parent->left == now)	RR(now->parent);
	        else							LR(now->parent);
	    }else if(now->parent->parent->left == now->parent && now->parent->left == now){
	        RR(now->parent->parent);
	        RR(now->parent);
	    }else if(now->parent->parent->right == now->parent && now->parent->right == now){
	        LR(now->parent->parent);
	        LR(now->parent);
	    }else if(now->parent->parent->left == now->parent && now->parent->right == now){
	        LR(now->parent);
	        RR(now->parent);
	    }else{
	        RR(now->parent);
	        LR(now->parent);
	    }
	}
}

int main(){
	std::ifstream in("input.txt");
	std::ofstream out("output.txt");
	std::string cmd, key, value;
	BST bst;
	while(in >> cmd){
		switch(cmd[2]){
			case 'S':{//insert
				in >> key >> value;
				key.erase(0,4);
				value.erase(0,6);
				bst.Insert(key, value);
				break;
			}
			case 'N':{//find
				in >> key;
				key.erase(0,4);
				node* x = bst.search(key);
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
				bst.erase(key);
				break;
			}
			case 'U':{//enum
				in >> key >> value;
				key.erase(0,4);
				value.erase(0,4);
				bst.Enum(key, value);
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
