// Problem: P9732 [CEOI 2023] Trade
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P9732
// Memory Limit: 2048 MB
// Time Limit: 7000 ms
// Written by yhm.
// Start codeing:2026-01-19 08:00:44
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
const int maxn=250010;
const int inf=1e18;
bool mbe;

int n,k,a[maxn],b[maxn];
int lsh[maxn],len;
#define mid ((l+r)>>1)
#define ls lc[nd]
#define rs rc[nd]
int num[maxn<<5],sum[maxn<<5];
int lc[maxn<<5],rc[maxn<<5],idx,rt[maxn];
void updata(int &nd,int l,int r,int p){
	int lst=nd;nd=++idx;num[nd]=num[lst]+1,sum[nd]=sum[lst]+lsh[p];ls=lc[lst],rs=rc[lst];
	if(l==r)return ;
	if(p<=mid)updata(ls,l,mid,p);
	else updata(rs,mid+1,r,p);
}
int kthsum(int nd1,int nd2,int l,int r,int k){
	if(l==r)return lsh[l]*k;
	if(num[rc[nd1]]-num[rc[nd2]]>=k)return kthsum(rc[nd1],rc[nd2],mid+1,r,k);
	else return kthsum(lc[nd1],lc[nd2],l,mid,k-(num[rc[nd1]]-num[rc[nd2]]))+sum[rc[nd1]]-sum[rc[nd2]]; 
}
int kthval(int nd1,int nd2,int l,int r,int k){
	if(l==r)return l;
	if(num[rc[nd1]]-num[rc[nd2]]>=k)return kthval(rc[nd1],rc[nd2],mid+1,r,k);
	else return kthval(lc[nd1],lc[nd2],l,mid,k-(num[rc[nd1]]-num[rc[nd2]]));
}
int calc(int l,int r){
	// cout<<l<<" "<<r<<" "<<kthsum(rt[r],rt[l-1],1,len,k)<<"\n";
	return kthsum(rt[r],rt[l-1],1,len,k)-(a[r]-a[l-1]);
}
int f[maxn],p[maxn];
void sovle(int l,int r,int pl,int pr){
	if(l>r)return ;
	f[mid]=-inf;
	for(int i=pl;i<=pr&&mid-i+1>=k;i++){
		int val=calc(i,mid);
		if(val>=f[mid])f[mid]=val,p[mid]=i;
	}
	sovle(l,mid-1,pl,p[mid]),sovle(mid+1,r,p[mid],pr);
}
int mn[18][maxn];
void chkmn(int l,int r,int w){
	int k=__lg(r-l+1);
	mn[k][l]=min(mn[k][l],w);
	mn[k][r-(1<<k)+1]=min(mn[k][r-(1<<k)+1],w);
}
void down(){
	for(int j=17;j;j--){
		for(int i=1;i+(1<<j)-1<=n;i++){
			mn[j-1][i]=min(mn[j-1][i],mn[j][i]);
			mn[j-1][i+(1<<j-1)]=min(mn[j-1][i+(1<<j-1)],mn[j][i]);
		}
	}
}
void work(){
	n=read();k=read();
	for(int i=1;i<=n;i++)a[i]=a[i-1]+read();
	for(int i=1;i<=n;i++)b[i]=read();
	for(int i=1;i<=n;i++)lsh[++len]=b[i];
	sort(lsh+1,lsh+len+1),len=unique(lsh+1,lsh+len+1)-lsh-1;
	for(int i=1;i<=n;i++)b[i]=lower_bound(lsh+1,lsh+len+1,b[i])-lsh;
	for(int i=1;i<=n;i++)updata(rt[i]=rt[i-1],1,len,b[i]);
	sovle(k,n,1,n);
	// for(int i=k;i<=n;i++)cout<<f[i]<<" ";cout<<"\n";
	int ans=-inf;for(int i=k;i<=n;i++)ans=max(ans,f[i]);
	mems(mn,0x3f);
	for(int i=k,lst=1;i<=n;i++)if(f[i]==ans){
		for(int j=lst;j<=p[i];j++)if(calc(j,i)==ans)chkmn(j,i,kthval(rt[i],rt[j-1],1,len,k));
		lst=p[i];
	}
	down();
	printf("%lld\n",ans);
	for(int i=1;i<=n;i++)putchar(mn[0][i]<=b[i]?'1':'0');
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