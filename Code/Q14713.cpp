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
bool check(){
	vector<int> A,B;
	for(int i=1;i<=n;i++)A.pb(i),B.pb(i);
	sort(A.begin(),A.end(),[&](int u,int v){return a[u]<a[v]||(a[u]==a[v]&&u<v);});
	sort(B.begin(),B.end(),[&](int u,int v){return b[u]>b[v]||(b[u]==b[v]&&u<v);});
	vector<bool> visa(n+1),visb(n+1);
	int s=0;for(int i:A)if(s+a[i]<=m)s+=a[i],visa[i]=1;
	s=0;for(int i:B)if(s+a[i]<=m)s+=a[i],visb[i]=1;
	for(int i=1;i<=n;i++)if(visa[i]!=visb[i])return 0;
	return 1;
}
vector<int> id,id1,id2;
bool vis[maxn];
void ok(){
	puts("Yes");
	for(int i=1;i<=n;i++)printf("%lld ",a[i]);puts("");
	for(int i=1;i<=n;i++)printf("%lld ",b[i]);puts("");
}
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read(),vis[i]=!b[i];
	id1.clear(),id2.clear(),id.clear();
	for(int i=1;i<=n;i++){
		if(a[i])id.pb(i),id1.pb(i);
		else id2.pb(i);
	}
	sort(id.begin(),id.end(),[&](int u,int v){return a[u]<a[v]||(a[u]==a[v]&&u<v);});
	for(int i=0;i<=id.size();i++){
		for(int j=0;j<i;j++)if(vis[id[j]])b[id[j]]=inf;
		for(int j=i;j<id.size();j++)if(vis[id[j]])b[id[j]]=1;
		sort(id1.begin(),id1.end(),[&](int u,int v){return b[u]>b[v]||(b[u]==b[v]&&u<v);});
		sort(id2.begin(),id2.end(),[&](int u,int v){return b[u]>b[v]||(b[u]==b[v]&&u<v);});
		int sum=m;for(int j=0;j<i;j++)sum-=a[id[j]];
		for(int j:id2)a[j]=inf;
		// cout<<i<<" "<<id1.size()<<" "<<id2.size()<<" "<<sum<<"\n";
		if(sum<0)break;
		if(!sum){
			if(check())return ok();
			else break;
		}
		for(int j:id2){
			int mx=inf-1;
			if(i!=id.size())mx=min(mx,a[id[i]]-(j>id[i]));
			// cout<<i<<" "<<j<<" "<<mx<<"\n";
			if(mx){
				mx=min(mx,sum);
				a[j]=mx,sum-=mx;
			}
			if(!sum)break;
		}
		if(check())return ok();
	}
	puts("No");	
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