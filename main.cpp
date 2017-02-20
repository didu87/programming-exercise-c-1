#include<iostream>
#include<string>
#include<sstream>

#include<time.h>
#include<iomanip>
#include<cstdlib>

#include"normalize.h"

using namespace std;

string tests[10][2]={
	{"../bar",              "/bar"},
	{"/foo/bar",            "/foo/bar"},
	{"/foo/bar/./baz/",     "/foo/bar/baz/"},
	{"/foo/../../baz",      "/baz"},
	{"/../foo",             "/foo"},
	{"/../../foo/",         "/foo/"},
	{"/./foo/./",           "/foo/"},
	{"//foo///bar",         "/foo/bar"},
	{"//foo/.././/bar",     "/bar"},
	{"/",                   "/"}
};

void test_correct() {
	cout<<"Test correctness on simple examples:"<<endl;
	for(int i=0;i<10;i++) {
		string input=tests[i][0];
		string answer=tests[i][1];
		string output=normalize(input);
		cout<<left<<setw(20)<<input<<"\t"<<left<<setw(10)<<answer<<"\t\t";
		if(output==answer)
			cout<<"[ok]"<<endl;
		else
			cout<<"[err]"<<endl;
	}
	cout<<endl;
}

double time_ms() {
	clock_t cl=clock();
	double ms=(double)1000 * cl / CLOCKS_PER_SEC;
	return ms;
}

void test_speed() {
	cout<<"Test speed with large input:"<<endl;
    string tokens[]={"foo", "bar", "baz", ".", ".."};  
	int total_size=0;
	double total_time=0;
    for(int i=1;i<=1000;i++) {
		ostringstream oss;   
        string token;
        for(int j=0;j<i;j++) {
            token=tokens[rand()%5];
           	oss<<"/"<<token;
        }   
        if(token=="." || token=="..")
            oss<<"/";
       	string test_input=oss.str(); 

		double t1=time_ms();
		normalize(test_input);
		double t2=time_ms();
		double dt=t2-t1;
		total_time+=dt;
		total_size+=test_input.size();
    }   
		
	cout<<"size: "<<total_size<<" bytes, time: "<<total_time<<" ms, ";
	double speed = 1000 * ((double)total_size / total_time) / (1024 * 1024);
	cout<<"speed: "<<setprecision(2)<< speed<<"Mbps"<<endl;
}

int main(void) {
	test_correct();
	test_speed();
	return 0;
}
