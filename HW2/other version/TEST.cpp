#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main(){
	fstream result("result.txt",ios::in);
	fstream output("output.txt",ios::in);
	string r, o;
	int x = 0;
	int error = 0;
	while(getline(result,r) && getline(output,o)){
		r.push_back(' ');
		x++;
		if(!r.compare(o)){
			
		}else{
			error++;
			cout << x << '\n';
			//cout << "r:" << r<<'\n';
			
			
			//cout << "o:"<<o<<'\n';
		}
	}
	if(error==0){
		cout << "AC " << x - error <<"/" << x <<'\n';
	}else{
		cout << "WA " << x - error <<"/" << x <<'\n';
	}
	return 0;
}

/*
struct HASH{ 
    size_t operator()(const std::pair<int, int>& p) const { 
    	return p.first^p.second; 
    }
};*/
