// Problem: CF2152H2 Victorious Coloring (Hard Version)
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF2152H2
// Memory Limit: 1000 MB
// Time Limit: 3000 ms
// Written by yhm.
// Start codeing:2025-10-13 14:55:54
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#include<ext/pb_ds/priority_queue.hpp>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
using namespace __gnu_pbds;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=250010;
const int inf=2e9;
bool mbe;

int n,q,a[maxn<<1];
tuple<int,int,int> e[maxn];
int ff[maxn<<1],idx,ls[maxn<<1],rs[maxn<<1];
int fd(int x){
	if(ff[x]==x)return x;
	return ff[x]=fd(ff[x]);
}
__gnu_pbds::priority_queue<int,greater<int>> f[maxn<<1];
int st[maxn<<1],tp;
int val[maxn<<1];
void work(){
	n=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read(),w=read();
		e[i]={w,u,v};
	}
	sort(e+1,e+n);
	for(int i=1;i<2*n;i++)ff[i]=i,a[i]=ls[i]=rs[i]=0;idx=n;
	for(int i=n-1;i;i--){
		auto[w,u,v]=e[i];
		a[u]+=w,a[v]+=w;
		u=fd(u),v=fd(v);
		ff[u]=ff[v]=++idx;ls[idx]=u,rs[idx]=v;
		a[idx]-=2*w;
	}
	for(int i=n+1;i<=idx;i++)a[i]+=a[ls[i]]+a[rs[i]];
	// for(int i=1;i<=idx;i++)cout<<a[i]<<" ";cout<<"\n";
	for(int i=1;i<=idx;i++){
		if(i<=n){if(a[i]<=inf)f[i].push(a[i]);continue;}
		f[i].swap(f[ls[i]]);f[i].join(f[rs[i]]);
		// cout<<i<<" "<<a[i]<<" "<<ls[i]<<" "<<rs[i]<<"\n";
		// for(int v:f[i])cout<<v<<" ";cout<<"\n";
		if(!f[i].size())continue;
		if(f[i].top()>a[i]){
			int k=1,b=0,lst=f[i].top();f[i].pop();
			while(f[i].size()){
				int p=f[i].top();
				if(k*(p-lst)+b>=p-a[i])break;
				f[i].pop();
				b+=k*(p-lst),lst=p,k++;
			}
			int p=f[i].size()?f[i].top():inf;
			// cout<<k<<" "<<b<<" "<<lst<<" "<<p<<"\n";
			if(k*(p-lst)+b>=p-a[i]){
				int l=lst,r=p,res=p;
				while(l<=r){
					int mid=l+r>>1;
					if(k*(mid-lst)+b>=mid-a[i])res=mid,r=mid-1;
					else l=mid+1;
				}
				int v=k*(res-lst)+b-(res-a[i]);
				// cout<<i<<" "<<v<<" "<<k<<"\n";
				for(int j=2;j<2+v;j++)f[i].push(res-1);
				for(int j=2+v;j<=k;j++)f[i].push(res);
			}
			if(a[i]<=inf)f[i].push(a[i]);
		}
		// for(int v:f[i])cout<<v<<" ";cout<<"\n";
	}
	tp=0;while(f[idx].size())st[++tp]=f[idx].top(),f[idx].pop();
	// for(int i=1;i<=tp;i++)cout<<st[i]<<" ";cout<<"\n";
	for(int i=1;i<=tp;i++)val[i]=val[i-1]+(st[i]-st[i-1])*(i-1);
	q=read();
	while(q--){
		int l=read();
		int p=upper_bound(st+1,st+tp+1,l)-st-1;
		printf("%lld\n",val[p]+(l-st[p])*p);
	}
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