#include<iostream>
#include<string>
#include<vector>
#include<sstream>

using namespace std;

string normalize(const string &path) {
	istringstream iss(path);
	vector<string> path_tokens;

	string token;
	while(getline(iss,token,'/')) {
		if(!token.empty() && token!=".") {
			if(token=="..") {
				if(!path_tokens.empty())
					path_tokens.pop_back();
			}
			else
				path_tokens.push_back(token);
		}
	}

	ostringstream oss;	
	for(int i=0;i<path_tokens.size();i++) {
		oss<<"/"<<path_tokens[i];
	}
	if(path[path.size()-1]=='/')
		oss<<"/";

	return oss.str();
}
