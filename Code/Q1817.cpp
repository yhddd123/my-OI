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
const int maxn=1<<18;
const int inf=1e9;
bool mbe;

int n,a[maxn],b[maxn];
map<int,int> pos;
void dfs(int d,int s,vector<int> id){
	if(!id.size())return ;
	if(d==-1){
		b[id[0]]=s;
		return ;
	}
	vector<int> id1,id2;
	for(int i:id){
		if(!((a[i]>>d)&1))id1.pb(i);
		else id2.pb(pos[a[i]^(1ll<<d)]);
	}
	dfs(d-1,s,id1);
	for(int i:id2)b[pos[a[i]^(1ll<<d)]]=b[i],b[i]=0;
	dfs(d-1,s|(1ll<<d),id2);
	// cout<<d<<" "<<s<<" "<<id1.size()<<" "<<id2.size()<<" d\n";
	// for(int i:id)cout<<i<<" "<<a[i]<<" "<<b[i]<<"\n";cout<<"\n";
}
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read(),pos[a[i]]=i;
	vector<int> id(n);
	for(int i=1;i<=n;i++)id[i-1]=i;
	dfs(59,0,id);
	for(int i=1;i<=n;i++)printf("%lld\n",b[i]);
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