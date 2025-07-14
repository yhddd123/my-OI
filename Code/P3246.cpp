// Problem: P3246 [HNOI2016] 序列
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3246
// Memory Limit: 500 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353
#define pii pair<int,int>
using namespace std;
const int maxn=100010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,q,a[maxn],s;
struct ask{
	int l,r,id;
}p[maxn];
bool cmp(ask u,ask v){
	if(u.l/s==v.l/s){
		if((u.l/s)&1)return u.r>v.r;
		return u.r<v.r;
	}
	return u.l<v.l;
}
int ans[maxn];
int st[maxn],tp,pre[maxn];
int f[maxn],g[maxn];
int mn[17][maxn];
bool cmpid(int u,int v){return a[u]<a[v];}
int query(int l,int r){
	int k=log2(r-l+1);
	return min(mn[k][l],mn[k][r-(1<<k)+1],cmpid);
}
int l=1,r=0,res=0;
void work(){
	n=read();q=read();s=sqrt(n);
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=q;i++)p[i]={read(),read(),i};
	sort(p+1,p+q+1,cmp);
	for(int i=1;i<=n;i++){
		while(tp&&a[i]<a[st[tp]])tp--;
		pre[i]=st[tp];st[++tp]=i;
	}
	for(int i=1;i<=n;i++)f[i]=f[pre[i]]+(i-pre[i])*a[i];
	tp=0;
	for(int i=n;i;i--){
		while(tp&&a[i]<a[st[tp]])tp--;
		pre[i]=st[tp];st[++tp]=i;
	}
	for(int i=n;i;i--)g[i]=g[pre[i]]+(pre[i]-i)*a[i];
	for(int i=1;i<=n;i++)mn[0][i]=i;
	for(int j=1;j<=16;j++){
		for(int i=1;i+(1<<j)-1<=n;i++){
			mn[j][i]=min(mn[j-1][i],mn[j-1][i+(1<<j-1)],cmpid);
		}
	}
	for(int i=1;i<=q;i++){
		while(r<p[i].r){
			r++;
			int pos=query(l,r);
			res+=(pos-l+1)*a[pos]+f[r]-f[pos];
		}
		while(l>p[i].l){
			l--;
			int pos=query(l,r);
			res+=(r-pos+1)*a[pos]+g[l]-g[pos];
		}
		while(r>p[i].r){
			int pos=query(l,r);
			res-=(pos-l+1)*a[pos]+f[r]-f[pos];
			r--;
		}
		while(l<p[i].l){
			int pos=query(l,r);
			res-=(r-pos+1)*a[pos]+g[l]-g[pos];
			l++;
		}
		ans[p[i].id]=res;
	}
	for(int i=1;i<=q;i++)printf("%lld\n",ans[i]);
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
