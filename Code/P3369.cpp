// Problem: P3369 【模板】普通平衡树
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3369
// Memory Limit: 128 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-04-10 16:48:52
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
const int maxn=3200010;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,ans;
int tree[maxn][2],ls[maxn],rs[maxn],sum[maxn],idx=1;
void insert(int x){
	int nd=1;
	for(int i=24;~i;i--){
		int v=(x>>i)&1;
		if(!tree[nd][v])tree[nd][v]=++idx;
		nd=tree[nd][v];sum[nd]++;
	}
}
void del(int x){
	int nd=1;
	for(int i=24;~i;i--){
		int v=(x>>i)&1;
		nd=tree[nd][v];sum[nd]--;
	}
}
int rnk(int x){
	int nd=1,res=0;
	for(int i=24;~i;i--){
		int v=(x>>i)&1;
		if(v)res+=sum[tree[nd][0]];
		nd=tree[nd][v];
	}
	return res+1;
}
int que(int x){
	int nd=1,res=0;
	for(int i=24;~i;i--){
		if(sum[tree[nd][0]]<x){
			x-=sum[tree[nd][0]];
			nd=tree[nd][1];res+=(1<<i);
		}
		else nd=tree[nd][0];
	}
	return res;
}
int pre(int x){return que(rnk(x)-1);}
int nxt(int x){return que(rnk(x+1));}
void work(){
	n=read();int m=10000000;
	while(n--){
		int op=read(),x=read();
		if(op==1)insert(x+m);
		if(op==2)del(x+m);
		if(op==3)ans=rnk(x+m),printf("%d\n",ans);
		if(op==4)ans=que(x)-m,printf("%d\n",ans);
		if(op==5)ans=pre(x+m)-m,printf("%d\n",ans);
		if(op==6)ans=nxt(x+m)-m,printf("%d\n",ans);
	}
}

// \
444

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
	// cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
