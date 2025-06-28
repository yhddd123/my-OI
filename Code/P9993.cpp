// Problem: P9993 [Ynoi Easy Round 2024] TEST_133
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P9993
// Memory Limit: 512 MB
// Time Limit: 40000 ms
// Written by yhm.
// Start codeing:2025-03-17 18:10:32
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
inline void write(int x){static char buf[20];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
const int maxn=500010;
const int inf=1e18;
bool mbe;

int n,q,a[maxn],his[maxn];
const int B=512;
int pl[maxn],pr[maxn],num,id[maxn];
int p[maxn],val[maxn],mx[maxn],add[maxn],mxadd[maxn];
void push(int i){
	for(int j=pl[i];j<=pr[i];j++)his[j]=max(his[j],a[j]+mxadd[i]),a[j]+=add[i];
	add[i]=mxadd[i]=0;
}
void build(int i){
	for(int j=pl[i];j<=pr[i];j++)p[j]=j;
	sort(p+pl[i],p+pr[i]+1,[&](int u,int v){return a[u]<a[v];});
	for(int j=pl[i];j<=pr[i];j++)val[j]=a[p[j]];
	mx[pl[i]]=his[p[pl[i]]];for(int j=pl[i]+1;j<=pr[i];j++)mx[j]=max(mx[j-1],his[p[j]]);
	add[i]=mxadd[i]=0;
}
void upd(int l,int r,int x){
	push(id[l]);
	for(int j=l;j<=r;j++)his[j]=max(his[j],a[j]+x),a[j]+=x;
	build(id[l]);
}
int que(int l,int r,int x){
	int ans=-inf;
	for(int j=l;j<=r;j++)if(a[j]+add[id[l]]<x)ans=max({ans,his[j],a[j]+mxadd[id[l]]});
	return ans;
}
void work(){
	n=read();q=read();
	for(int i=1;i<=n;i++)a[i]=his[i]=read();
	for(int l=1,r;l<=n;l=r+1){
		r=min(l+B-1,n);++num;pl[num]=l,pr[num]=r;
		for(int j=l;j<=r;j++)id[j]=num;
		build(num);
	}
	while(q--){
		int op=read(),l=read(),r=read(),x=read();
		if(op==1){
			if(id[l]==id[r])upd(l,r,x);
			else{
				upd(l,pr[id[l]],x),upd(pl[id[r]],r,x);
				for(int i=id[l]+1;i<id[r];i++)mxadd[i]=max(mxadd[i],add[i]+x),add[i]+=x;
			}
		}
		else{
			int ans=-inf;
			if(id[l]==id[r])ans=que(l,r,x);
			else{
				ans=max(que(l,pr[id[l]],x),que(pl[id[r]],r,x));
				for(int i=id[l]+1;i<id[r];i++){
					int pos=lower_bound(val+pl[i],val+pr[i]+1,x-add[i])-val-1;
					if(pos>=pl[i])ans=max({ans,mx[pos],val[pos]+mxadd[i]});
				}
			}
			if(ans==-inf)puts("-inf");
			else write(ans),puts("");
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