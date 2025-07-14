// Problem: P9529 [JOISC2022] 一流团子师傅
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P9529
// Memory Limit: 1 MB
// Time Limit: 10000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
const int maxn=10010;

// #include "dango3.h"

int t[maxn],idx;
int n,m,a[maxn];
int Query(const std::vector<int> &x){
	int num=m;++idx;
	if(idx>50000){printf("Wa\nQuery\n");exit(0);}
	for(int i:x)t[a[i]]++;
	for(int i=1;i<=n;i++)num=min(num,t[i]);
	for(int i:x)t[a[i]]=0;
	return num;
}
void Answer(const std::vector<int> &a){
	if(!Query(a)){
		printf("Wa\nAnswer\n");
		for(int i:a)printf("%d ",i);printf("\n");
		exit(0);
	}
}

int Query(const std::vector<int> &x);
void Answer(const std::vector<int> &a);

vector<int> q,nw;
void Solve(int n, int m){
	for(int i=1;i<=n*m;i++)q.push_back(i);
	srand(time(0));
	for(int i=1;i<m;i++){
		random_shuffle(q.begin(),q.end());
		nw.clear();nw.push_back(q.back()),q.pop_back();
		while((int)nw.size()<n){
			while(1){
				int v=q.front();q.erase(q.begin());
				if(Query(q)==m-i){nw.push_back(v);break;}
				else q.push_back(v);
			}
			// cerr<<nw.size()<<"\n";
		}
		Answer(nw);
	}
	Answer(q);
}

signed main(){
	cin>>n>>m;
	for(int i=1;i<=n*m;i++)cin>>a[i];
	Solve(n,m);
	printf("ac");
}