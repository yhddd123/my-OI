// Problem: P11987 [JOIST 2025] 集邮比赛 4 / Collecting Stamps 4
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P11987
// Memory Limit: 1024 MB
// Time Limit: 3000 ms
// Written by yhm.
// Start codeing:2025-12-11 18:08:55
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
const int maxn=1000010;
const int inf=2e18;
bool mbe;

int n,m,q;
int a[maxn],b[maxn];
int lsh[maxn<<1],len;
int ask[maxn],ans[maxn<<1];
pii c[maxn];
int f[maxn];
int pre[maxn];
#define lb(x) (x&(-x))
int tree[maxn];
void upd(int x,int w){
	while(x<=2*n)tree[x]+=w,x+=lb(x);
}
int que(int x){
	int res=0;
	while(x)res+=tree[x],x-=lb(x);
	return res;
}
void clr(){
	for(int i=1;i<=2*n;i++)tree[i]=0;
}
void work(){
	n=read();m=read();
	for(int i=1;i<=2*n;i++)a[i]=read();
	for(int i=1;i<=2*n;i++)b[i]=read();
	q=read();
	for(int i=1;i<=q;i++)ask[i]=read();
	for(int i=1;i<=2*n;i++){
		if(!c[a[i]].fi)c[a[i]].fi=i;
		else c[a[i]].se=i;
	}
	for(int i=1;i<=n;i++)pre[c[i].se+1]++;
	for(int i=1;i<=2*n;i++)pre[i]+=pre[i-1];
	for(int i=2*n,suf=0;i;i--){
		if(i==c[a[i]].fi)suf++;
		f[i]+=pre[i]*suf;
	}
	for(int i=1;i<=2*n;i++)pre[i]=0;
	sort(c+1,c+n+1,[&](pii u,pii v){return u.fi<v.fi;});
	for(int i=n;i;i--){
		upd(2*n-c[i].fi+1,1);
		pre[c[i].fi]+=que(2*n-c[i].se+1);
	}
	for(int i=2*n-1;i;i--)pre[i]+=pre[i+1];
	for(int i=1;i<=2*n;i++)f[i]+=pre[i],pre[i]=0;
	clr();
	for(int i=1;i<=n;i++){
		upd(c[i].se,1);
		pre[c[i].se+1]+=que(c[i].fi);
	}
	for(int i=1;i<=2*n;i++)pre[i]+=pre[i-1];
	for(int i=1;i<=2*n;i++)f[i]+=pre[i],pre[i]=0;
	clr();
	// for(int i=1;i<=2*n;i++)cout<<f[i]<<" ";cout<<"\n";
	for(int i=n;i;i--){
		int num=que(c[i].se);
		pre[c[i].fi+1]+=num,pre[c[i].se+1]-=num;
		// if(num)cout<<c[i].fi+1<<" "<<c[i].se<<" "<<num<<" a\n";
		upd(c[i].se,1);
	}
	for(int i=1;i<=2*n;i++)pre[i]+=pre[i-1];
	for(int i=1;i<=2*n;i++)f[i]+=pre[i],pre[i]=0;
	clr();
	for(int i=1;i<=n;i++)upd(2*n-c[i].se+1,1);
	for(int i=n;i;i--){
		upd(2*n-c[i].se+1,-1);
		int num=que(2*n-c[i].se+1);
		// if(num)cout<<c[i].fi+1<<" "<<c[i].se<<" "<<num<<" d\n";
		pre[c[i].fi+1]+=num,pre[c[i].se+1]-=num;
	}
	for(int i=1;i<=2*n;i++)pre[i]+=pre[i-1];
	for(int i=1;i<=2*n;i++)f[i]-=pre[i],pre[i]=0;
	clr();
	// for(int i=1;i<=2*n;i++)cout<<f[i]<<" ";cout<<"\n";
	for(int i=1;i<=q;i++)lsh[++len]=ask[i];
	for(int i=1;i<=2*n;i++)lsh[++len]=n*n-f[i];
	sort(lsh+1,lsh+len+1),len=unique(lsh+1,lsh+len+1)-lsh-1;
	for(int i=1;i<=len;i++)ans[i]=inf;
	for(int i=1;i<=2*n;i++){
		int p=lower_bound(lsh+1,lsh+len+1,n*n-f[i])-lsh;
		ans[p]=min(ans[p],b[i]);
	}
	for(int i=len-1;i;i--)ans[i]=min(ans[i],ans[i+1]);
	// for(int i=1;i<=len;i++)cout<<lsh[i]<<" "<<ans[i]<<"\n";
	for(int i=2;i<=len;i++)ans[i]=min(ans[i],ans[i-1]+(lsh[i]-lsh[i-1])*m);
	for(int i=1;i<=q;i++){
		int p=lower_bound(lsh+1,lsh+len+1,ask[i])-lsh;
		printf("%lld\n",ans[p]);
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