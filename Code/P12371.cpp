// Problem: P12371 【模板】最大团/最大独立集
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P12371
// Memory Limit: 1 MB
// Time Limit: 3000 ms
// Written by yhm.
// Start codeing:2025-05-29 16:20:43
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define ll long long
#define mod 998244353ll
#define pii pair<ll,int>
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
const int maxn=50;
const int inf=1e9;
bool mbe;

int n,m;ll e[maxn];
pii dfs(ll s){
	if(!s)return {0,1};
	pii mx={0,-1};
	for(ll ss=s;ss;ss-=(ss&(-ss))){
		int u=__lg(ss&(-ss));
		mx=max(mx,{__builtin_popcountll(e[u]&s),u});
	}
	// cout<<s<<" "<<mx.fi<<" "<<mx.se<<"\n";
	if(mx.fi<=2){
		pii res={0,1};
		ll s1=0,s2=0,fl=1,S=s;
		auto ddfs=[&](auto &&self,int u,int op)->void{
			S^=1ll<<u;(!op?s1:s2)|=1ll<<u;fl&=(__builtin_popcountll(e[u]&s)==2);
			while(S&e[u])self(self,__lg((S&e[u])&(-(S&e[u]))),op^1);
		};
		while(S){
			s1=0,s2=0,fl=1;
			ddfs(ddfs,__lg(S&(-S)),0);
			if(fl){
				if(__builtin_popcountll(s1)<=__builtin_popcountll(s2))res.fi|=s1;
				else res.fi|=s2;
				int num=__builtin_popcountll(s1)+__builtin_popcountll(s2);
				res.se=res.se*((num&1)?num:2);
			}
			else{
				if(__builtin_popcountll(s1)>=__builtin_popcountll(s2))res.fi|=s1;
				else res.fi|=s2;
				int num=__builtin_popcountll(s1)+__builtin_popcountll(s2);
				res.se=res.se*((num&1)?1:num/2+1);
			}
		}
		return res;
	}
	pii res=dfs(s^(1ll<<mx.se));
	auto[S,v]=dfs(s^(s&(e[mx.se]|(1ll<<mx.se))));S|=1ll<<mx.se;
	if(__builtin_popcountll(res.fi)<__builtin_popcountll(S))res={S,v};
	else if(__builtin_popcountll(res.fi)==__builtin_popcountll(S))res.se=res.se+v;
	return res;
}
void sovle(){
	// for(int i=0;i<n;i++)cout<<e[i]<<" ";cout<<"\n";
	pii res=dfs((1ll<<n)-1);
	printf("%d %d\n",__builtin_popcountll(res.fi),res.se);
	for(int i=0;i<n;i++)if(res.fi&(1ll<<i))printf("%d ",i+1);puts("");
}
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int u=read()-1,v=read()-1;
		e[u]|=1ll<<v,e[v]|=1ll<<u;
	}
	for(int i=0;i<n;i++)e[i]=((1ll<<n)-1-(1ll<<i))^e[i];sovle();
	for(int i=0;i<n;i++)e[i]=((1ll<<n)-1-(1ll<<i))^e[i];sovle();
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