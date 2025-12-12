// Problem: P11989 [JOIST 2025] 勇者比太郎 3 / Bitaro the Brave 3
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P11989
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-12-11 19:18:07
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
const int maxn=6010;
const int maxm=10000010;
const int inf=1e18;
bool mbe;

int n,lim,m,q;
struct node{
	int t,h,p;
}a[maxn],b[maxn];
pii st[maxn];int tp;
int vk[maxm],vb[maxm];
void upd(int l,int r,int k,int b){
	if(l>r)return ;
	// cout<<l<<" "<<r<<" "<<k<<" "<<b<<"\n";
	vk[l]+=k,vk[r+1]-=k,vb[l]+=b,vb[r+1]-=b;
}
void work(){
	n=read();lim=read();m=read();
	for(int i=1;i<=n;i++)a[i]={read(),read(),read()};
	sort(a+1,a+n+1,[&](node u,node v){return u.p>v.p;});
	for(int l=1;l<=n;l++){
		int r=l;while(r<n&&a[l].p==a[r+1].p)r++;
		sort(a+l,a+r+1,[&](node u,node v){return u.t<v.t;});
		int p=0,p1=1,p2=l;
		while(p1<l&&p2<=r){
			if(a[p1].t<a[p2].t)b[++p]=a[p1++];
			else b[++p]=a[p2++];
		}
		while(p1<l)b[++p]=a[p1++];
		while(p2<=r)b[++p]=a[p2++];
		for(int i=1;i<=r;i++)swap(a[i],b[i]);
		int del=b[r].p-a[r+1].p;
		// cout<<del<<endl;
		st[tp=1]={0,0};
		for(int i=r,sum=0;i;i--){
			sum+=a[i].h;
			int k=del*sum,b=-del*(m-a[i].t);
			if(m-a[i].t>=inf/del)continue;
			while(tp>1&&(__int128)(st[tp].se-b)*(st[tp].fi-st[tp-1].fi)<(__int128)(k-st[tp].fi)*(st[tp-1].se-st[tp].se))tp--;
			st[++tp]={k,b};
		}
		int lst=0;
		for(int i=1;i<tp;i++){
			int p=(st[i].se-st[i+1].se)/(st[i+1].fi-st[i].fi);p=min(p,lim);
			upd(lst,p,st[i].fi,st[i].se);
			lst=p+1;
		}
		upd(lst,lim,st[tp].fi,st[tp].se);
		l=r;
	}
	for(int i=0;i<=lim;i++)vk[i]+=vk[i-1],vb[i]+=vb[i-1];
	q=read();
	int p=1;
	while(q--){
		int val=read();
		while(p<=lim&&vk[p]*p+vb[p]<=val)p++;
		printf("%lld\n",p-1);
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