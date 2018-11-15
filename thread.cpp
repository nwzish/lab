#include<iostream>
#include<thread>
#include<vector>
#include<algorithm>

using namespace std;

double sum1=0;
double sum2=0;

struct myclass{
	bool operator()(int i,int j){return i<j;}
} myobject;

vector<int> myvector;

void task1(){
	cout<<"task1 is starting...\n";
	double c=0;
	while(c<25000000){
		c++;sum1+=c;
	}
	cout<<"task1 is completed...\n";
}

void task2(){
	cout<<"task2 is starting..."<<endl;
	double c=0;
	while(c<2500000){
		c++; sum2+=c;
	}
	cout<<"task2 is completed..."<<endl;
}

void task3(){
	cout<<"task3 is starting..."<<endl;
	myvector = {12 ,1,23,52,36,45,12,58,45,56,25};
	sort(myvector.begin(),myvector.end(),myobject);
	cout<<"task3 is completed"<<endl;
}

int main(){
	thread t1(task1); thread t2(task2); thread t3(task3);
	thread::id id1 = t1.get_id();
	thread::id id2 = t2.get_id();
	thread::id id3 = t3.get_id();

	if(t1.joinable()){
		t1.join();
		cout<<"t1 id ="<<id1<<endl;
	}


	if(t2.joinable()){
		t2.join();
		cout<<"t2 id ="<<id2<<endl;
	}

	if(t3.joinable()){
		t3.join();
		cout<<"t3 id ="<<id3<<endl;
	}

	cout<<"sum1 "<<sum1<<" sum2 "<<sum2<<endl;

}




























