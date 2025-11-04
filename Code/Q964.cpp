#include<bits/stdc++.h>
// #define int long long
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
const int maxn=500100;
const int B=512;
const int inf=1e9;
bool mbe;

int n,q,a[maxn];
struct ask{
	int l,r,id;
}que[maxn];
int ans[maxn];
struct ds{
	int a[maxn],b[maxn>>3],c[maxn>>6],d[maxn>>3],e[maxn>>6];
	void upd(int p,int w){
		p++;
		// cout<<p<<" "<<w<<"\n";
		a[p]+=w,b[p>>3]+=w,c[p>>6]+=w;
		int &vd=d[p>>3]=-inf;
		for(int i=(p>>3)<<3,s=0;i<((p>>3)+1)<<3;i++){
			vd=max(vd,s+a[i]);
			s+=a[i];
		}
		int &ve=e[p>>6]=-inf;
		for(int i=(p>>6)<<3,s=0;i<((p>>6)+1)<<3;i++){
			ve=max(ve,s+d[i]);
			s+=b[i];
		}
	}
	int query(){
		int p=-1,t=0;
		for(int i=0,s=0;i<=n>>6;i++){
			if(s+e[i]>=0)p=i,t=s;
			s+=c[i];
		}
		if(p==-1)return -1;
		int x=-1;
		int s=t;
		for(int i=p<<6;i<(p+1)<<6;i++){
			s+=a[i];
			if(s>=0)x=i;
		}
		return x;
	}
}d;
int t[maxn];
inline void add(int p){
	d.upd(a[p],1);
}
inline void del(int p){
	d.upd(a[p],-1);
}
void work(){
	n=read();q=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=0;i<=n+1;i++)d.upd(i,-1);
	// for(int i=0;i<=n;i++)cout<<d.a[i]<<" ";cout<<"\n";
	for(int i=1;i<=q;i++)que[i]={read(),read(),i};
	sort(que+1,que+q+1,[&](ask u,ask v){
		if(u.l/B==v.l/B)return ((u.l/B)&1)?u.r>v.r:u.r<v.r;
		return u.l<v.l;
	});
	for(int i=1,l=1,r=0;i<=q;i++){
		while(r<que[i].r)add(++r);
		while(l>que[i].l)add(--l);
		while(r>que[i].r)del(r--);
		while(l<que[i].l)del(l++);
		ans[que[i].id]=d.query();
		// cout<<i<<" "<<que[i].l<<" "<<que[i].r<<" "<<que[i].id<<" "<<ans[que[i].id]<<"\n";
	}
	for(int i=1;i<=q;i++)printf("%d\n",ans[i]);
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