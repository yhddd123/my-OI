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
const int maxn=3010;
const int inf=1e9;
bool mbe;

int n,m;
int a[maxn],b[maxn];
vector<int> id,id1,id2;
bool vis[maxn];
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read(),vis[i]=;
	id1.clear(),id2.clear(),id.clear();
	for(int i=1;i<=n;i++){
		if(a[i])id.pb(i),id1.pb(i);
		else id2.pb(i);
	}
	sort(id.begin(),id.end(),[&](int u,int v){return a[u]<a[v]||(a[u]==a[v]&&u<v);});
	for(int i=0;i<=id.size();i++){
		for(int j=0;j<i;j++)if(!b[id[j]])b[id[j]]=inf;
		for(int j=i;j<id.size();j++)b[id[j]]=1;
		sort(id1.begin(),id2.end(),[&](int u,int v){return b[u]>b[v]||(b[u]==b[v]&&u<v);});
		sort(id2.begin(),id2.end(),[&](int u,int v){return b[u]>b[v]||(b[u]==b[v]&&u<v);});
		int sum=m;for(int j=0;j<i;j++)sum-=a[id[j]];
		for(int )
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