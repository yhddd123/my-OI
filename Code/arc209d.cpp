// Problem: D - A_A_i
// Contest: AtCoder - AtCoder Regular Contest 209 (Div. 1)
// URL: https://atcoder.jp/contests/arc209/tasks/arc209_d
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-11-09 21:05:41
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
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
const int maxn=500010;
const int inf=1e9;
bool mbe;

int n,a[maxn],nxt[maxn];
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	nxt[n+1]=n+1;for(int i=n;i;i--)nxt[i]=(a[i]==-1||a[i]==1)?i:nxt[i+1];
	vector<int> p1;
	if(a[1]!=-1){
		if(a[a[1]]==-1)a[a[1]]=1;
	}
	else a[1]=1;
	for(int i=2,pos=(a[1]==1?1:-1);i<=n;i++){
		if(a[i]!=-1){
			if(a[i]==1){
				if(pos==-1)pos=i;
				for(int j:p1)a[j]=i;
				p1.clear();
			}
			if(a[a[i]]==-1){
				if(a[i]<i){
					a[nxt[i]]=1;
					for(int j:p1)a[j]=nxt[i];
					p1.clear();
				}
				else a[a[i]]=1;
			}
		}
		else{
			if(a[1]==1)a[i]=1;
			else if(pos!=-1)a[i]=pos;
			else if(nxt[i+1]==n+1){
				if(p1.size()){
					for(int j:p1)a[j]=i;
					p1.clear();
					a[i]=1;
				}
				else{
					a[i]=i;
					int p=1;for(int j=1;j<=n;j++)if(a[j]<a[p])p=j;
					a[i]=p;
				}
			}
			else p1.pb(i);
		}
	}
	// for(int i=1;i<=n;i++)cout<<a[i]<<" ";cout<<"\n";
	for(int i=1;i<=n;i++)printf("%lld ",a[a[i]]);puts("");
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