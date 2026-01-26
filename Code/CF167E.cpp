// Problem: CF167E Wizards and Bets
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF167E
// Memory Limit: 250 MB
// Time Limit: 3000 ms
// Written by yhm.
// Start codeing:2026-01-26 17:01:20
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
// #define mod 998244353ll
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
const int maxn=610;
const int inf=1e9;
bool mbe;

int n,m,k,mod,ans=1;
vector<int> e[maxn];
int in[maxn];
int f[maxn];
int id[maxn],idx;
inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
int a[maxn][maxn];
void work(){
	n=read();m=read();mod=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		e[u].pb(v),in[v]++;
	}
	vector<int> id1,id2;
	for(int i=1;i<=n;i++){
		if(!in[i])id1.pb(i);
		if(!e[i].size())id2.pb(i);
	}
	k=id1.size();
	queue<int> q;
	for(int u:id1)q.push(u);
	while(!q.empty()){
		int u=q.front();q.pop();id[++idx]=u;
		for(int v:e[u]){
			in[v]--;
			if(!in[v])q.push(v);
		}
	}
	for(int i=0;i<k;i++){
		int s=id1[i];
		for(int i=1;i<=n;i++)f[i]=0;
		f[s]=1;
		for(int i=1;i<=n;i++){
			int u=id[i];
			for(int v:e[u])inc(f[v],f[u]);
		}
		for(int j=0;j<k;j++){
			int t=id2[j];
			a[i+1][j+1]=f[t];
		}
	}
	for(int i=1;i<=k;i++){
		for(int j=i+1;j<=k;j++){
			while(a[i][i]){
				int d=a[j][i]/a[i][i];
				if(d){
					for(int l=i;l<=k;l++)inc(a[j][l],mod-a[i][l]*d%mod);
				}
				swap(a[i],a[j]),ans=-ans;
			}
			swap(a[i],a[j]),ans=-ans;
		}
	}
	(ans+=mod)%=mod;
	for(int i=1;i<=k;i++)ans=ans*a[i][i]%mod;
	printf("%lld\n",ans);
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