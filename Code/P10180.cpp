// Problem: P10180 半彩三重奏
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10180
// Memory Limit: 512 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1000010;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,q,a[maxn];
int f[maxn],siz[maxn];
int fd(int x){
	if(x==f[x])return x;
	return fd(f[x]);
}
int st[maxn][2],tp;
void merge(int u,int v){
	if(u==v)return ;
	if(siz[u]<siz[v])swap(u,v);
	st[++tp][0]=v,st[tp][1]=siz[v];
	f[v]=u;siz[u]+=siz[v];
}
#define pii pair<int,int>
unordered_map<int,int>mp;pii id[maxn];
vector<pii> ans[maxn];int idx;
int res[maxn],sum[maxn];
int get(int u,int v){return min(u,v)*n+max(u,v);}
void work(){
	n=read();q=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)f[i]=i,siz[i]=1;
	for(int i=2;i<=n;i++){
		int u=read();
		if(a[u]==a[i])merge(fd(u),fd(i));
		else{
			int p=get(a[u],a[i]);
			if(!mp[p])mp[p]=++idx,id[idx]={a[u],a[i]};
			ans[mp[p]].push_back(make_pair(u,i));
		}
	}
	for(int i=1;i<=n;i++)if(f[i]==i)sum[a[i]]+=siz[i]*siz[i];
	for(int i=1;i<=idx;i++){
		// cout<<id[i].first<<" "<<id[i].second<<" a\n";
		res[i]=sum[id[i].first]+sum[id[i].second];
		int lst=tp;
		for(pii j:ans[i]){
			int u=fd(j.first),v=fd(j.second);
			res[i]+=2*siz[u]*siz[v];
			merge(u,v);
		}
		while(tp!=lst){
			siz[f[st[tp][0]]]-=st[tp][1];
			f[st[tp][0]]=st[tp][0];
			tp--;
		}
		// for(int j=1;j<=n;j++)if(j==f[j])cout<<j<<" "<<f[j]<<" "<<siz[j]<<"\n";
	}
	while(q--){
		int u=read(),v=read();
		if(mp.count(get(u,v)))printf("%lld\n",res[mp[get(u,v)]]);
		else printf("%lld\n",sum[u]+sum[v]);
	}
}

int T;
signed main(){
	T=1;
	while(T--)work();
}