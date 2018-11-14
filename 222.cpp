#include<bits/stdc++.h>

using namespace std;

const int maxx = 10000; 
vector<int> g[maxx];
vector<int> gr[maxx];
int vis[maxx],visr[maxx];
stack<int> ts;

void dfs(int x){
	if(vis[x]==1) return;
	vis[x]=1;
	for(int i=0;i<g[x].size();i++){
		if(vis[g[x][i]]==0){
			dfs(g[x][i]);
		}
	}
	ts.push(x);
}

void dfsr(int x){
	if(visr[x]==1) return;
	visr[x]=1;
	for(int i=0;i<gr[x].size();i++){
		if(visr[gr[x][i]]==0){
			dfsr(gr[x][i]);
		}
	}

}
int main(){
	int n,e; cin>>n>>e;
	for(int i=0;i<e;i++){
		int x,y;
		cin>>x>>y;
		g[x].push_back(y);
		gr[y].push_back(x);
	{
	
	for(int i=1;i<=n;i++){
		if(vis[i]==0) dfs(i);
	}
	
	int count=0;
	while(!ts.empty()){
		int x=ts.top();
		ts.pop();
		if(visr[x]==0){
			count++;
			dfsr(x);
		}
	}
	
	
	
	cout<<count<<endl;
	
	
	
}























