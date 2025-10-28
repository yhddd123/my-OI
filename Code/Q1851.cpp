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
const int maxn=100010;
const int inf=1e9;
bool mbe;

int n,m,q,a[maxn];
vector<int> e[maxn];
int d[maxn],id[maxn],idx;
const int B=64;
#define ull unsigned long long
int op[B],p[B],val[B];
int st[B],tp,rnk[B];
ull f[maxn],g[maxn],suf[B];
void work(){
	n=read();m=read();q=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		e[u].pb(v);
		d[v]++;
	}
	queue<int> qq;
	for(int i=1;i<=n;i++)if(!d[i])qq.push(i);
	while(!qq.empty()){
		int u=qq.front();qq.pop();id[++idx]=u;
		for(int v:e[u]){
			d[v]--;
			if(!d[v])qq.push(v);
		}
	}
	for(int l=0,r;l<q;l=r+1){
		r=min(l+B-1,q-1);
		for(int i=1;i<=n;i++)f[i]=g[i]=0;
		ull s1=0;tp=0;for(int i=0;i<=r-l;i++){
			op[i]=read();p[i]=0;
			if(op[i]==1){
				int u=read();val[i]=read();
				f[u]|=1ll<<i;
				s1|=1ll<<i;
			}else if(op[i]==2){
				int u=read();val[i]=read();p[i]=u;
				f[u]|=1ll<<i;
				st[tp++]=i;
			}else val[i]=read();
		}
		sort(st,st+tp,[&](int u,int v){return val[u]<val[v];});
		for(int i=0;i<tp;i++)rnk[st[i]]=i;
		for(int i=r-l;~i;i--)suf[i]=(i==r-l?0:suf[i+1])|(op[i]==2?(1ll<<rnk[i]):0);
		for(int i=0;i<=r-l;i++)g[p[i]]|=1ll<<rnk[i];
		for(int ii=1;ii<=n;ii++){
			int u=id[ii];
			ull fu=f[u],gu=g[u];
			for(int v:e[u])f[v]|=fu,g[v]|=gu;
		}
		for(int i=0;i<=r-l;i++)if(op[i]==3){
			int u=val[i],v=a[u];
			for(int j=0;j<i;j++)if(f[u]&(1ll<<j)){
				if(op[j]==1)v=val[j];
				else v=min(v,val[j]);
			}
			printf("%d\n",v);
		}
		// cout<<"run\n";
		for(int i=1;i<=n;i++){
			ull fu=f[i]&s1,gu=g[i];
			if(fu){
				int p=63-__builtin_clzll(fu);
				gu&=suf[p];
				if(gu)a[i]=min(val[p],val[st[__builtin_ctzll(gu)]]);
				else a[i]=val[p];
			}
			else if(gu){
				a[i]=min(a[i],val[st[__builtin_ctzll(gu)]]);
			}
		}
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