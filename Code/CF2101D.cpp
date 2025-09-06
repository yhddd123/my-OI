// Problem: D. Mani and Segments
// Contest: Codeforces - Codeforces Round 1024 (Div. 1)
// URL: https://codeforces.com/problemset/problem/2101/D
// Memory Limit: 256 MB
// Time Limit: 3000 ms
// Written by yhm.
// Start codeing:2025-09-06 08:19:29
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
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n,a[maxn];
int id[maxn],p[maxn],pos[maxn];
int pl[maxn],pr[maxn];
int f[maxn];
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
int mx[maxn<<2];
void build(int nd,int l,int r){
	mx[nd]=0;
	if(l==r)return ;
	build(ls,l,mid),build(rs,mid+1,r);
}
void upd(int nd,int w){mx[nd]=max(mx[nd],w);}
void down(int nd){upd(ls,mx[nd]),upd(rs,mx[nd]),mx[nd]=0;}
void updata(int nd,int l,int r,int ql,int qr,int w){
	if(l>=ql&&r<=qr)return upd(nd,w);
	if(mx[nd])down(nd);
	if(ql<=mid)updata(ls,l,mid,ql,qr,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
}
void modif(int nd,int l,int r,int p,int w){
	if(l==r){mx[nd]=w;return ;}
	if(mx[nd])down(nd);
	if(p<=mid)modif(ls,l,mid,p,w);
	else modif(rs,mid+1,r,p,w);
}
int query(int nd,int l,int r,int p){
	if(l==r)return mx[nd];
	if(mx[nd])down(nd);
	if(p<=mid)return query(ls,l,mid,p);
	else return query(rs,mid+1,r,p);
}
void sovle(){
	for(int i=1;i<=n;i++)id[i]=i;
	sort(id+1,id+n+1,[&](int u,int v){return a[u]>a[v];});
	set<int> s;
	build(1,1,n);
	for(int i=1;i<=n;i++){
		int u=id[i];
		int pp=0;
		auto it=s.lower_bound(u);
		if(it!=s.begin())it--,pp=query(1,1,n,(*it));
		s.insert(u);
		if(u<n)updata(1,1,n,u+1,n,u);
		p[u]=pp,pos[u]=pp;modif(1,1,n,u,p[u]);
	}
	s.clear();
	sort(id+1,id+n+1,[&](int u,int v){return a[u]<a[v];});
	build(1,1,n);
	for(int i=1;i<=n;i++){
		int u=id[i];
		int pp=0;
		auto it=s.lower_bound(u);
		if(it!=s.begin())it--,pp=query(1,1,n,(*it));
		s.insert(u);
		if(u<n)updata(1,1,n,u+1,n,u);
		p[u]=pp,pos[u]=max(pos[u],pp);modif(1,1,n,u,p[u]);
	}
}
// int t[15][15];
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	sovle();
	for(int i=1;i<=n;i++)pl[i]=pos[i];	 
	reverse(a+1,a+n+1);
	sovle();
	reverse(a+1,a+n+1);
	for(int i=1;i<=n;i++)pr[i]=n-pos[n-i+1]+1;
	for(int i=1;i<=n;i++)f[i]=(i-pl[i])*(pr[i]-i);
	int ans=0;for(int i=1;i<=n;i++)ans+=f[i];
	// for(int i=1;i<=n;i++){
		// for(int j=pl[i]+1;j<=i;j++){
			// for(int k=i;k<pr[i];k++)t[j][k]++;
		// }
	// }
	// for(int i=1;i<=n;i++)cout<<pl[i]<<" ";cout<<"\n";
	// for(int i=1;i<=n;i++)cout<<pr[i]<<" ";cout<<"\n";
	// cout<<ans<<"\n";
	if(a[1]>a[2])a[0]=0;
	else a[0]=n+1;
	if(a[n-1]>a[n])a[n+1]=n+1;
	else a[n+1]=0;
	for(int i=1,j;i<n;i=j){
		j=i+1;while(j+1<=n&&(a[i]-a[j])*(a[j]-a[j+1])>=0)j++;
		// cout<<i<<" "<<j<<" "<<ans<<"\n";
		for(int k=i;k<=j;k++)ans-=(j-k)*(k-i+1);
		// for(int k=i;k<=j;k++){
			// for(int p=i;p<=k;p++)for(int q=k+1;q<=j;q++)t[p][q]--;
		// }
		int l=i,r=j;
		if(a[i]>a[j]){
			while(r>=i&&a[i-1]>a[r])r--;
			while(l<=j&&a[j+1]<a[l])l++;
		}
		else{
			while(l<=j&&a[j+1]>a[l])l++;
			while(r>=i&&a[i-1]<a[r])r--;
		}
		// cout<<i<<" "<<j<<" "<<l<<" "<<r<<"\n";
		if(l<r){
			ans-=(i-1-pl[r])*(pr[l]-j-1)*(r-l);
			// for(int p=pl[r]+1;p<i;p++)for(int q=j+1;q<pr[l];q++)t[p][q]-=r-l;
		}
		if(l<j){
			ans-=(pr[l]-j-1)*(j-l)*(l-i);
			ans-=(pr[l]-j-1)*(j-l)*(j-l+1)/2;
			// for(int p=l;p<j;p++)for(int q=j+1;q<pr[l];q++)t[p][q]-=j-p;
		}
		if(i<r){
			// cout<<i-1-pl[r]<<" "<<r-i<<" "<<j-r<<"\n";
			ans-=(i-1-pl[r])*(r-i)*(j-r);
			ans-=(i-1-pl[r])*(r-i)*(r-i+1)/2;
			// for(int p=pl[r]+1;p<i;p++)for(int q=i+1;q<=r;q++)t[p][q]-=q-i;
		}
	}
	// for(int i=1;i<=n;i++){
		// for(int j=1;j<=n;j++)cout<<t[i][j]<<" ";cout<<"\n";
	// }
	printf("%lld\n",ans);
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