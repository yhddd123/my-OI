// Problem: P11664 [JOI 2025 Final] 缆车 / Mi Teleférico
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P11664
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-10-29 19:44:48
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
const int maxn=300010;
const int inf=1e18;
bool mbe;

int n,m,q;
int pl[maxn],pr[maxn];
map<int,vector<int>> mp;
int lsh[maxn],len;
vector<int> a[maxn];
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
int mn[maxn<<2];
void modif(int nd,int l,int r,int p,int w){
    if(l==r){mn[nd]+=w;return ;}
    if(p<=mid)modif(ls,l,mid,p,w);
    else modif(rs,mid+1,r,p,w);
    mn[nd]=min(mn[ls],mn[rs]);
}
struct ST{
	int mn[19][maxn];
	int que(int l,int r){
		if(l>r)return inf;
		int k=__lg(r-l+1);
		return min(mn[k][l],mn[k][r-(1<<k)+1]);
	}
	void init(){
		for(int j=1;j<=18;j++){
			for(int i=1;i+(1<<j)-1<=len;i++)mn[j][i]=min(mn[j-1][i],mn[j-1][i+(1<<j-1)]);
		}
	}
}t1,t2;
void work(){
	n=read();m=read();read();
	for(int i=1;i<=m;i++){
		read();int v=read(),p=read();
		lsh[++len]=p;mp[p].pb(v);
	}
	sort(lsh+1,lsh+len+1);len=unique(lsh+1,lsh+len+1)-lsh-1;
	lsh[0]=-inf;lsh[len+1]=inf;
	for(int i=1;i<=len;i++)a[i]=mp[lsh[i]];
	for(int r=1,l=1;r<=len;r++){
		for(int p:a[r])modif(1,2,n,p,1);
		pl[r]=pl[r-1];
		while(mn[1]){
			pr[l]=r;
			for(int p:a[l])modif(1,2,n,p,-1);
			pl[r]=l;
			l++;
		}
		if(r==len){
			while(l<=len)pr[l]=len+1,l++;
		}
	}
	for(int i=1;i<=len;i++)t1.mn[0][i]=lsh[pr[i]]-lsh[i];
	for(int i=1;i<=len;i++)t2.mn[0][i]=lsh[pr[i]];
	t1.init(),t2.init();
	// for(int i=1;i<=len;i++)cout<<pl[i]<<" ";cout<<"\n";
	// for(int i=1;i<=len;i++)cout<<pr[i]<<" ";cout<<"\n";
	q=read();
	while(q--){
		int l=read(),r=read(),x=read();
		int ll=lower_bound(lsh+1,lsh+len+1,l)-lsh,rr=upper_bound(lsh+1,lsh+len+1,r)-lsh-1;
		// cout<<l<<" "<<r<<" "<<x<<" "<<lsh[ll]<<" "<<ll<<" "<<rr<<"\n";
		if(rr<len&&lsh[pr[rr+1]]-r<=x)puts("Yes");
		else if(ll-1&&l-lsh[pl[ll-1]]<=x)puts("Yes");
		else if(t2.que(ll,rr)<=r+x)puts("Yes");
		else if(l-lsh[pl[rr]]<=x)puts("Yes");
		else{
			int ql=max(1ll,l-x),qr=min(l,lsh[lower_bound(pr+1,pr+len+1,r+x)-pr]);
			// cout<<ql<<" "<<qr<<"\n";
			ql=lower_bound(lsh+1,lsh+len+1,ql)-lsh,qr=upper_bound(lsh+1,lsh+len+1,qr)-lsh-1;
			puts(t1.que(ql,qr)+l-r<=x?"Yes":"No");
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