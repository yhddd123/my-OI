// Problem: P12080 [OOI 2025] Order Statistics
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P12080
// Memory Limit: 1 MB
// Time Limit: 4000 ms
// Written by yhm.
// Start codeing:2025-05-26 19:53:45
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=400010;
const int inf=2e9;
bool mbe;

int n,m,k,q,a[maxn];
tuple<int,int,int,int,int> que[maxn];
int lsh[maxn<<1],len;
#define lb(x) (x&(-x))
struct bit{
	int tree[maxn];
	void upd(int x,int w){
		while(x<=len)tree[x]+=w,x+=lb(x);
	}
	int que(int x){
		int res=0;
		while(x)res+=tree[x],x-=lb(x);
		return res;
	}
	int que(int l,int r){
		if(l>r)return 0;
		return que(r)-que(l-1);
	}
}num,sum;
int calc(int x,int v,int p,int cnt,int m){
	int ans=0;
	int pv=lower_bound(lsh+1,lsh+len+1,v)-lsh;
	int pm=lower_bound(lsh+1,lsh+len+1,m+v+1)-lsh;
	int pl=num.que(pv-1),pr=num.que(pm-1);
	if(pl<x)ans+=sum.que(pv,p-1)+cnt*lsh[p]-(x-pl)*v;
	if(x<pr)ans+=sum.que(p,pm-1)-cnt*lsh[p]-(pr-x)*(v+1);
	pr=max(pr,x);
	if(pr<=n)ans+=(n-pr)*m;
	// cout<<x<<" "<<v<<" "<<p<<" "<<m<<" "<<ans<<"\n";
	return ans;
}
int calc(int m,int k,int x){
	int l=1,r=len,res=1;
	while(l<=r){
		int mid=l+r>>1;
		if(num.que(mid)<x)res=mid+1,l=mid+1;
		else r=mid-1;
	}
	int p=res,cnt=x-num.que(p-1);
	l=lsh[p]-m,r=lsh[p],res=lsh[p];
	while(l<=r){
		int mid=l+r>>1;
		if(calc(x,mid,p,cnt,m)<=m*k)res=mid,r=mid-1;
		else l=mid+1;
	}
	return res;
}
int calc1(int m,int k,int x){
	if(x==n+1)return 0;
	int w=calc(m,k,x);
	int l=1,r=len,res=1;
	while(l<=r){
		int mid=l+r>>1;
		if(num.que(mid)<x)res=mid+1,l=mid+1;
		else r=mid-1;
	}
	int p=res,cnt=x-num.que(p-1);
	int ans1=0,ans2=0;
	int pv=lower_bound(lsh+1,lsh+len+1,w)-lsh;
	int pm=lower_bound(lsh+1,lsh+len+1,m+w)-lsh;
	int pl=num.que(pv-1),pr=num.que(pm-1);
	if(pl<x)ans1+=sum.que(pv,p-1)+cnt*lsh[p]-(x-pl)*w;
	if(x<pr)ans2+=sum.que(p,pm-1)-cnt*lsh[p]-(pr-x)*w;
	pr=max(pr,x);
	if(pr<=n)ans2+=(n-pr)*m;
	int ans=sum.que(len)-(sum.que(1,p-1)+cnt*lsh[p]);
	return w+ans-min(m*k-ans1,ans2);
}
void work(){
	n=read();m=read();k=read();q=read();
	for(int i=1;i<=n;i++)a[i]=lsh[++len]=read();
	for(int i=1;i<=q;i++){
		int op=read();
		if(op==1)que[i]={1,read(),read(),read(),0};
		if(op==2)que[i]={2,read(),lsh[++len]=read(),0,0};
		if(op==3)que[i]={3,read(),read(),read(),read()};
	}
	sort(lsh+1,lsh+len+1),len=unique(lsh+1,lsh+len+1)-lsh-1;
	for(int i=1;i<=n;i++)a[i]=lower_bound(lsh+1,lsh+len+1,a[i])-lsh;
	for(int i=1;i<=q;i++){
		auto[op,w,x,y,z]=que[i];
		if(op==2)x=lower_bound(lsh+1,lsh+len+1,x)-lsh;
		que[i]={op,w,x,y,z};
	}
	for(int i=1;i<=n;i++)num.upd(a[i],1),sum.upd(a[i],lsh[a[i]]);
	for(int i=1;i<=n;i++)printf("%lld ",calc(m,k,i));puts("");
	for(int i=1;i<=q;i++){
		auto[op,w,x,y,z]=que[i];
		if(op==1)printf("%lld\n",calc(w,x,y));
		if(op==2){
			num.upd(a[w],-1),sum.upd(a[w],-lsh[a[w]]);
			a[w]=x;
			num.upd(a[w],1),sum.upd(a[w],lsh[a[w]]);
		}
		if(op==3)printf("%lld\n",calc1(w,x,y)-calc1(w,x,z+1));
	}
}

bool med;
int T;
signed main(){
	// freopen("monsters.in","r",stdin);
	// freopen("monsters.out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}