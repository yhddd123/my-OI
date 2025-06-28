// Problem: P3586 [POI 2015] LOG
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3586
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2025-05-28 09:24:07
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
const int inf=1e9;
bool mbe;

int n,q,a[maxn];
int lsh[maxn],len;
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
}num,sum;
tuple<int,int,int> que[maxn];
void work(){
	n=read();q=read();
	lsh[++len]=0;
	for(int i=1;i<=q;i++){
		char op[3];scanf("%s",op);
		if(op[0]=='U')que[i]={1,read(),read()};
		else que[i]={2,read(),read()};
		lsh[++len]=get<2>(que[i]);
	}
	sort(lsh+1,lsh+len+1),len=unique(lsh+1,lsh+len+1)-lsh-1;
	num.upd(1,n);
	for(int i=1;i<=n;i++)a[i]=1;
	for(int i=1;i<=q;i++){
		auto[op,u,v]=que[i];
		v=lower_bound(lsh+1,lsh+len+1,v)-lsh;
		if(op==1){
			num.upd(a[u],-1),sum.upd(a[u],-lsh[a[u]]);
			a[u]=v;
			num.upd(a[u],1),sum.upd(a[u],lsh[a[u]]);
		}
		else{
			int m=num.que(v-1);
			if(n-m>=u)puts("TAK");
			else if(sum.que(v-1)>=(u-n+m)*lsh[v])puts("TAK");
			else puts("NIE");
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