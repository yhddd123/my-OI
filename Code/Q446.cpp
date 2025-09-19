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
const int maxn=1000010;
const int inf=1e9;
bool mbe;

int n,m=20;long long ans;
int to[maxn*20][2],idx=1;
bool vis[1<<20];
void ins(int x){
	if(vis[x])return ;vis[x]=1;
	int nd=1;
	for(int i=19;~i;i--){
		int v=(x>>i)&1;
		if(v)ins(x^(1<<i));
		if(!to[nd][v])to[nd][v]=++idx;
		nd=to[nd][v];
	}
}
int que(int x){
	int nd=1,res=0;
	for(int i=19;~i;i--){
		int v=(x>>i)&1;
		if(v)nd=to[nd][0];
		else{
			if(to[nd][1])nd=to[nd][1],res|=1<<i;
			else nd=to[nd][0];
		}
	}
	return res;
}
void work(){
	n=read();
	for(int i=1,v=0;i<=n;i++){
		v^=read();
		ins(v);
		printf("%lld ",v+2*que(v));
	}
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}