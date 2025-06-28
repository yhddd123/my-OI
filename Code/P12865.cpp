// Problem: P12865 [JOI Open 2025] 冒泡排序机 / Bubble Sort Machine
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P12865
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-06-20 14:45:45
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
const int maxn=500010;
const int inf=1e9;
bool mbe;

int n,q,a[maxn],cnt;
int lsh[maxn],len;
#define mid (l+r>>1)
#define ls lc[nd]
#define rs rc[nd]
int num[maxn<<6],sum[maxn<<6];
int lc[maxn<<6],rc[maxn<<6],rt[maxn],idx;
void updata(int &nd,int l,int r,int p){
	int lst=nd;nd=++idx;ls=lc[lst],rs=rc[lst],num[nd]=num[lst]+1,sum[nd]=sum[lst]+lsh[p];
	if(l==r)return ;
	if(p<=mid)updata(ls,l,mid,p);
	else updata(rs,mid+1,r,p);
}
int query(int nd,int l,int r,int k){
	if(l==r)return k*lsh[l];
	if(num[ls]>=k)return query(ls,l,mid,k);
	else return sum[ls]+query(rs,mid+1,r,k-num[ls]);
}
int calc(int p){
	return query(rt[min(p+cnt,n)],1,len,p);
}
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)lsh[++len]=a[i];
	sort(lsh+1,lsh+len+1),len=unique(lsh+1,lsh+len+1)-lsh-1;
	for(int i=1;i<=n;i++)a[i]=lower_bound(lsh+1,lsh+len+1,a[i])-lsh;
	for(int i=1;i<=n;i++)updata(rt[i]=rt[i-1],1,len,a[i]);
	q=read();
	while(q--){
		int op=read();
		if(op==1)++cnt;
		else{
			int l=read(),r=read();
			printf("%lld\n",calc(r)-calc(l-1));
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