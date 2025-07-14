// Problem: #698. 【候选队互测2022】枪打出头鸟
// Contest: UOJ
// URL: https://uoj.ac/problem/698
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-07-11 15:57:07
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=500010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,q;
struct bas{
	int p[64],tmp[64],cnt;
	void insert(int x){
		for(int i=63;~i;i--)if(x&(1ll<<i)){
			if(!p[i]){p[i]=x;return ;}
			x^=p[i];
		}
	}
	void ins(int x){
		for(int i=63;~i;i--)if(x&(1ll<<i)){
			if(!p[i]){p[i]=x;tmp[i]=x,++cnt;return ;}
			x^=p[i];
		}
	}
	int find(int x){
		int val=0;
		for(int i=63;~i;i--)if(x&(1ll<<i)){
			if(!p[i])return -1;
			x^=p[i];val^=tmp[i];
		}
		if(x)return -1;
		return val;
	}
}pre[maxn];
vector<int> pos;
int mx[64];
void work(){
	n=read();q=read();
	int k=read();
	while(k--)pre[1].ins(read());
	pos.push_back(1);
	for(int i=2;i<=n;i++){
		int k=read();bas lst=pre[pos.back()];
		while(k--){
			int x=read(),v=lst.find(x);
			// cout<<x<<" "<<v<<"\n";
			if(~v)pre[i].ins(v);
			lst.insert(x);
		}
		if(pre[i].cnt!=pre[pos.back()].cnt)pos.push_back(i);
	}
	for(int i=pos.size()-2;~i;i--)for(int j=0;j<64;j++)if(pre[pos[i+1]].p[j])pre[pos[i]].p[j]=pre[pos[i+1]].p[j];
	for(int i:pos)for(int j=0;j<64;j++)if(!pre[i].p[j]&&!mx[j])mx[j]=i;
	for(int j=0;j<64;j++)if(!mx[j])mx[j]=n+1;
	while(q--){
		int x=read();int res=n+1;
		for(int i=63;~i;i--)if(x&(1ll<<i)){
			// cout<<x<<" "<<i<<"\n";
			res=min(res,mx[i]);
			x^=pre[1].p[i];
		}
		printf("%lld\n",res);
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
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
