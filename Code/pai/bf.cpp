// Problem: P11983 [JOIST 2025] 展览会 3 / Exhibition 3
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P11983
// Memory Limit: 1024 MB
// Time Limit: 3000 ms
// Written by yhm.
// Start codeing:2025-12-04 18:01:39
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
const int maxn=100010;
const int inf=1e9;
bool mbe;

int n,m,t[maxn],lst;
pii a[maxn];
int ans[maxn];
int ff[maxn];
int fd(int x){
	if(ff[x]==x)return x;
	return ff[x]=fd(ff[x]);
}
int id[maxn],k;
int chk(){
	sort(id+1,id+k+1,[&](int u,int v){return a[u].se<a[v].se;});
	int num=0;for(int i=1,p=0;i<=k;i++)if(p<a[id[i]].fi)++num,p=a[id[i]].se;
	sort(id+1,id+k+1);
	return num;
}
void work(){
	n=read();m=read();lst=m;
	for(int i=1;i<=n;i++)t[read()]++;
	for(int i=1;i<=m;i++)a[i]={read(),read()};
	for(int i=1;i<=m+1;i++)ff[i]=i;
	for(int v=n;v&&lst;v--)if(t[v]){
		k=0;for(int p=fd(1);p<=m;p=fd(p+1)){
			id[++k]=p;
			if(chk()>t[v])k--;
		}
		// for(int i=1;i<=k;i++)cout<<id[i]<<" ";cout<<"\n";
		for(int i=1;i<=k;i++){
			ff[id[i]]=fd(id[i]+1),ans[id[i]]=v;lst--;
		}
	}
	for(int i=1;i<=m;i++)printf("%lld\n",ans[i]);
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