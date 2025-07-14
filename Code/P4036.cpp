// Problem: P4036 [JSOI2008] 火星人
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4036
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-07-16 08:03:05
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define ll unsigned long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=100010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,q;
char s[maxn];
mt19937 rnd(1);
ll bas,pw[maxn],val[26];
int siz[maxn],w[maxn],ls[maxn],rs[maxn],rt,idx;
ll hsh[maxn],num[maxn];
int nw(int c){
	int u=++idx;
	siz[u]=1;w[u]=rnd();
	hsh[u]=num[u]=val[c];
	return u;
}
void up(int u){
	siz[u]=siz[ls[u]]+siz[rs[u]]+1;
	hsh[u]=hsh[ls[u]]*pw[siz[rs[u]]+1]+num[u]*pw[siz[rs[u]]]+hsh[rs[u]];
}
pii split(int u,int k){
	if(!u)return {0,0};
	if(siz[ls[u]]+1<=k){
		pii t=split(rs[u],k-siz[ls[u]]-1);
		rs[u]=t.fi;up(u);
		// cout<<t.se<<" "<<siz[t.se]<<" "<<hsh[t.se]<<"\n";
		return {u,t.se};
	}
	else{
		pii t=split(ls[u],k);
		ls[u]=t.se;up(u);
		return {t.fi,u};
	}
}
int merge(int u,int v){
	if(!u||!v)return u|v;
	if(w[u]<w[v]){
		rs[u]=merge(rs[u],v);up(u);
		return u;
	}
	else{
		ls[v]=merge(u,ls[v]);up(v);
		return v;
	}
}
ll gethsh(int l,int r){
	pii x=split(rt,r),y=split(x.fi,l-1);
	ll res=hsh[y.se];
	// cout<<l<<" "<<r<<" "<<siz[y.fi]<<" "<<hsh[y.fi]<<" "<<siz[y.se]<<" "<<num[y.se]<<" "<<siz[x.se]<<" "<<hsh[x.se]<<" "<<res<<"\n";
	rt=merge(merge(y.fi,y.se),x.se);
	return res;
}
void work(){
	scanf("%s",s+1);n=strlen(s+1);q=read();
	bas=rnd();for(int i=0;i<26;i++)val[i]=rnd();
	// bas=100;for(int i=0;i<26;i++)val[i]=i+1;
	pw[0]=1;for(int i=1;i<=maxn-10;i++)pw[i]=pw[i-1]*bas;
	for(int i=1;i<=n;i++)rt=merge(rt,nw(s[i]-'a'));
	while(q--){
		char op[3];scanf("%s",op+1);
		if(op[1]=='Q'){
			int u=read(),v=read();
			if(u>v)swap(u,v);
			int l=1,r=siz[rt]-v+1,res=0;
			while(l<=r){
				int mid=l+r>>1;
				// cout<<mid<<" a\n";
				if(gethsh(u,u+mid-1)==gethsh(v,v+mid-1))l=mid+1,res=mid;
				else r=mid-1;
			}
			printf("%lld\n",res);
		}
		if(op[1]=='R'){
			int p=read();scanf("%s",s+1);
			pii x=split(rt,p),y=split(x.fi,p-1);
			hsh[y.se]=num[y.se]=val[s[1]-'a'];
			rt=merge(merge(y.fi,y.se),x.se);
		}
		if(op[1]=='I'){
			int p=read();scanf("%s",s+1);
			pii x=split(rt,p);
			rt=merge(merge(x.fi,nw(s[1]-'a')),x.se);	
		}
	}
}

// \
444

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
