// Problem: CF1267I Intriguing Selection
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1267I
// Memory Limit: 500 MB
// Time Limit: 5000 ms
// Written by yhm.
// Start codeing:2025-10-24 15:27:23
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
// #define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n,A[maxn];
mt19937 rnd(time(0));
bool chk(int u,int v){
	printf("? %d %d\n",u,v);fflush(stdout);
	// return A[u]>A[v];
	char op[5];scanf("%s",op);
	return op[0]=='<';
}
void work(){
	n=read();
	// for(int i=1;i<=2*n;i++)A[i]=i;
	// shuffle(A+1,A+2*n+1,rnd);
	// for(int i=1;i<=2*n;i++)A[i]=read();
	vector<int> a,b;
	for(int i=1;i<=(n+1)/2;i++)a.pb(i);
	for(int i=(n+1)/2+1;i<=n+1;i++)b.pb(i);
	stable_sort(a.begin(),a.end(),[&](int u,int v){return chk(u,v);});
	stable_sort(b.begin(),b.end(),[&](int u,int v){return chk(u,v);});
	// for(int u:a)cout<<u<<" ";cout<<"\n";
	// for(int u:b)cout<<u<<" ";cout<<"\n";
	// cout<<"run\n";
	for(int i=n+2;i<=2*n;i++){
		if(!chk(a[0],b[0]))swap(a,b);
		if(chk(a[0],i)){
			int p=a.size();
			for(int j=1;j<a.size();j++)if(!chk(a[j],i)){p=j;break;}
			for(int j=1;j<p;j++)a[j-1]=a[j];a[p-1]=i;
		}
	}
	chk(a[0],b[0]);
	printf("!\n");fflush(stdout);
	// for(int i=1;i<=2*n;i++)cout<<A[i]<<" ";cout<<"\n";
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}