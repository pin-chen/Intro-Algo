#pragma GCC optimize("Ofast,unroll-loops")
#include <fstream>
#include <string>
#include <iostream> 
std::string output;

struct node{
	std::string key, value;
	node *parent, *left, *right;
	node(std::string key, std::string value, node* parent){
		this->key = key;
		this->value = value;
		this->parent = parent;
		this->left = nullptr;
		this->right = nullptr;
	}
};

class BST{
	private:
		node *root, *R;
		std::string tmp1, tmp2;
		bool t1, t2;
		void Delete(node *now);
		void printn(node* now);
		void Level(node* now);
		void splay(node* now);
		void leftrotation(node* now);
		void rightrotation(node* now);
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
	return;
}

BST::~BST(){
	this->clear();
	return;
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
			this->splay(now);
			return now;
		}
	}
}

void BST::Insert(std::string& key, std::string&value){
	if(root == nullptr){
		root = new node(key, value, nullptr);
		output = "INSERT "+key+" SUCCESS!\n";
		return;
	}
	for(node *now = this->root;;){
		if(key > now->key){
			if(now->right == nullptr){
				now->right = new node(key, value, now);
				output = "INSERT "+key+" SUCCESS!\n";
				this->splay(now->right);
				break;
			}
			now = now->right;
		}else if(key < now->key){
			if(now->left == nullptr){
				now->left = new node(key, value, now);
				output = "INSERT "+key+" SUCCESS!\n";
				this->splay(now->left);
				break;
			}
			now = now->left;
		}else{
			output = "INSERT "+key+" FAIL!\n";
			break;
		}
	}
	return;
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
	return;
}

void BST::clear(){
	this->Delete(this->root);
	return;
}

void BST::Delete(node *now){
	if(now == nullptr) return;
	this->Delete(now->left);
	this->Delete(now->right);
	delete now;
	return;
}

void BST::Level(node *now){
	if(now == nullptr) return;
	if( (t1 || tmp1 <= now->key) && (t2 || tmp2 >= now->key)){
		this->R = now;
		return;
	}
	this->Level(now->left);
	this->Level(now->right);
}

void BST::Enum(std::string& key1, std::string& key2){
	this->t1 = !(bool) this->search(key1);
	this->t2 = !(bool) this->search(key2);
	this->tmp1 = key1;
	this->tmp2 = key2;
	output = "";
	this->Level(this->root);
	this->printn(this->R);
}

void BST::printn(node* now){
	if(now == nullptr) return;
	printn(now->left);
	if((t1 || tmp1 <= now->key) && (t2 || tmp2 >= now->key)){
		output += "ENUM "+now->key+":"+now->value+"\n";
	}
	printn(now->right);
}

void BST::leftrotation(node* now){
	node* parent = now->parent->parent;
	now->parent->parent = now;
	now->parent->right = now->left;
	now->left = now->parent;
	now->parent = parent; 
}

void BST::rightrotation(node* now){
	node* parent = now->parent->parent;
	now->parent->parent = now;
	now->parent->left = now->right;
	now->right = now->parent;
	now->parent = parent;
}

void BST::splay(node* now){
	for(; now->parent != nullptr;){
		std::cout << now->key << '\n';
		if(now->parent->parent == nullptr){
			if(now->parent->left == now){
				rightrotation(now->parent);
			}else{
				leftrotation(now->parent);
			}
	 	}else if (now->parent->parent->left == now->parent && now->parent->left == now){
            rightrotation(now->parent->parent);
            rightrotation(now->parent);
        }else if (now->parent->parent->right == now->parent && now->parent->right == now){
            leftrotation(now->parent);
            leftrotation(now->parent);
        }else if (now->parent->parent->left == now->parent && now->parent->right == now) {
            leftrotation(now->parent);
            rightrotation(now->parent);
        }else{
            rightrotation(now->parent);
            leftrotation(now->parent);
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
