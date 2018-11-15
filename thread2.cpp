#include<iostream>
#include<thread>
#define ll long long
using namespace std;
ll sum1=0;
ll sum2=0;
void task1(ll v){
	cout<<"task1 r"<<endl;
	ll c=0;
	while(c<v){c++; sum1+=c; cout<<"t1 "<<c<<endl;}
	cout<<"task1 end"<<endl;
}

void task2(ll v){
	cout<<"task2 r"<<endl;
	ll c=0;
	while(c<v){c++;sum1+=c; cout<<"t2 "<<c<<endl;}
	cout<<"task2 end"<<endl;
}

int main(){
	thread t1{task1,100};
	thread t2{task2,9};
	if(t1.joinable()){
		t1.join();

	}
	if(t2.joinable()){
		t2.join();
	}
	cout<<sum1<<endl;
}