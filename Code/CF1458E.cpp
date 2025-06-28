// Problem: CF1458E Nim Shortcuts
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1458E
// Memory Limit: 500 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-04-17 12:43:10
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
// #define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define tup tuple<int,int,int>
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
const int maxn=200010;
const int inf=2e9;
bool mbe;

int n,q;
pii a[maxn],b[maxn];
bool ans[maxn];
int lsh[maxn],len;
vector<int> upd[maxn];
vector<pii> que[maxn];
struct node{
	int l,r;
	bool operator<(const node&tmp)const{return r<tmp.l;}
};
set<node> s;
map<pii,bool> mp;
void work(){
	n=read();q=read();
	lsh[len=1]=0;
	for(int i=1;i<=n;i++)a[i]={read(),read()},lsh[++len]=a[i].fi;
	for(int i=1;i<=q;i++)b[i]={read(),read()},lsh[++len]=b[i].fi;
	sort(lsh+1,lsh+len+1),len=unique(lsh+1,lsh+len+1)-lsh-1;
	for(int i=0;i<=n;i++)a[i].fi=lower_bound(lsh+1,lsh+len+1,a[i].fi)-lsh;
	for(int i=1;i<=q;i++)b[i].fi=lower_bound(lsh+1,lsh+len+1,b[i].fi)-lsh;
	for(int i=0;i<=n;i++)upd[a[i].fi].pb(a[i].se);
	for(int i=0;i<=n;i++)mp[a[i]]=1;
	for(int i=1;i<=q;i++){
		if(mp.find(b[i])!=mp.end())ans[i]=1;
		else que[b[i].fi].pb({b[i].se,i});
	}
	s.insert({0,inf});
	auto del=[&](int p){
		auto it=s.find({p,p});
		if(it!=s.end()){
			auto[l,r]=*it;it=s.erase(it);
			if(l<p)s.insert({l,p-1});
			if(p<r)s.insert({p+1,r});
		}
	};
	for(int i=1;i<=len;i++){
		int d=lsh[i]-lsh[i-1],p=-1;
		while(d){
			auto[l,r]=*s.begin();
			s.erase(s.begin());
			int dd=min(d,r-l+1);
			d-=dd,l+=dd,p=l-1;
			if(l<=r)s.insert({l,r});
		}
		// cout<<lsh[i]<<" "<<p<<"\n";
		int mn=inf;for(int j:upd[i])mn=min(mn,j);
		if(mn>p)del(p);
		else{s.insert({p,p}),p=-1;}
		for(int j:upd[i])del(j);
		for(auto[j,id]:que[i])ans[id]=(j==p);
	}
	for(int i=1;i<=q;i++)puts(ans[i]?"LOSE":"WIN");
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