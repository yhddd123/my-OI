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
const int maxn=5010;
const int maxm=510;
const int inf=1e9;
bool mbe;

int n,m,k;
vector<tuple<int,int,int,int>> ans;
bitset<maxm*maxn> f[maxm];
bool sovle(set<pii> &s){
	int n=s.size(),m=0;
	for(auto[v,id]:s)m+=v;m/=k;
	while(m&&m>=n){
		m--;
		auto[v,i]=*--s.end();s.erase(--s.end());
		ans.pb({i,k,0,0});
		v-=k;
		if(v)s.insert({v,i});
		else n--;
	}
	while(m&&m==n-1){
		m--;
		auto[v1,i1]=*s.begin();s.erase(s.begin());
		auto[v2,i2]=*--s.end();s.erase(--s.end());
		ans.pb({i1,v1,i2,k-v1});n--;
		v2-=k-v1;s.insert({v2,i2});
	}
	if(m==n-2){
		vector<pii> a;
		for(pii p:s)a.pb(p);
		for(int i=0;i<=n;i++)f[i].reset();
		f[0][0]=1;
		for(int i=1;i<=n;i++){
			int v=k-a[i-1].fi;
			if(v>0)f[i]=f[i-1]|(f[i-1]<<v);
			else f[i]=f[i-1]|(f[i-1]>>-v);
		}
		if(!f[n][k])return 0;
		set<pii> s1,s2;
		for(int i=n-1,j=k;~i;i--){
			if(f[i][j])s2.insert(a[i]);
			else s1.insert(a[i]),j-=k-a[i].fi;
		}
		return sovle(s1)|sovle(s2);
	}
	return 1;
}
void work(){
	n=read();m=read();k=read();
	set<pii> a;
	for(int i=1;i<=n;i++)a.insert({read(),i});
	ans.clear();
	if(!sovle(a)){puts("-1");return ;}
	for(auto[i,x,j,y]:ans){
		if(!j)printf("%d %d\n",i,x);
		else printf("%d %d %d %d\n",i,x,j,y);
	}
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