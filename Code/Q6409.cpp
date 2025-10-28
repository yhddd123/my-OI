#include<bits/stdc++.h>
#define ll long long
#define mod (1<<30)-1
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
const int maxn=2000010;
const int inf=1e9;
bool mbe;

int q,lst,m,ans;
mt19937_64 rnd(time(0));
ll w[maxn];int ls[maxn],rs[maxn],idx,rt;
int pos[maxn];
int s1[maxn],v1[maxn],s2[maxn],v2[maxn];
inline int newnode(int p,ll w1,ll w2){
	w1%=mod+1,w1+=mod+1,w2%=mod+1,w2+=mod+1;w1%=mod+1,w2%=mod+1;
	int u=++idx;w[u]=rnd();pos[u]=p;
	s1[u]=v1[u]=w1,s2[u]=v2[u]=w2;
	return u;
}
inline void up(int u){
	s1[u]=(s1[ls[u]]+s1[rs[u]]+v1[u])&mod;
	s2[u]=(s2[ls[u]]+s2[rs[u]]+v2[u])&mod;
}
inline void upd(int u,ll w1,ll w2){
	if(!u)return ;
	w1%=mod+1,w1+=mod+1,w2%=mod+1,w2+=mod+1;w1%=mod+1,w2%=mod+1;
	(s1[u]+=w1)&=mod,(v1[u]+=w1)&=mod;
	(s2[u]+=w2)&=mod,(v2[u]+=w2)&=mod;
}
int merge(int u,int v){
	if(!u||!v)return u|v;
	// cout<<u<<" "<<v<<" "<<mxd[u]<<" "<<mxd[v]<<"\n";
	if(w[u]<w[v]){
		rs[u]=merge(rs[u],v);
		up(u);
		return u;
	}
	else{
		ls[v]=merge(u,ls[v]);
		up(v);
		return v;
	}
}
pii split(int u,int k){
	if(!u)return {0,0};
	if(pos[u]<=k){
		pii t=split(rs[u],k);
		rs[u]=t.fi;
		up(u);
		return {u,t.se};
	}
	else{
		pii t=split(ls[u],k);
		ls[u]=t.se;
		up(u);
		return {t.fi,u};
	}
}
void work(){
	q=read();m=(1<<read())-1;
	for(int i=1;i<=q;i++){
		int l=read(),r=read();
		l=(l+lst)&m,r=(r+lst)&m;
		if(l>r)swap(l,r);
		int x,y,z;
		
		pii t=split(rt,l-1);
		x=t.fi,y=t.se;
		t=split(y,l);
		y=t.fi,z=t.se;
		if(!y)y=newnode(l,i,i*l);
		else upd(y,i,i*l);
		rt=merge(merge(x,y),z);
		// cout<<s1[rt]<<" "<<s2[rt]<<"\n";
		
		t=split(rt,r);
		x=t.fi,y=t.se;
		t=split(y,r+1);
		y=t.fi,z=t.se;
		if(!y)y=newnode(r,-i,-1ll*i*(r+1));
		else upd(y,-i,-1ll*i*(r+1));
		rt=merge(merge(x,y),z);
		
		
		t=split(rt,l-1);
		x=t.fi,y=t.se;
		t=split(y,r);
		y=t.fi,z=t.se;
		// cout<<x<<" "<<y<<" "<<z<<" "<<s1[x]<<" "<<s1[y]<<" "<<s2[y]<<"\n";
		ll val=1ll*s1[x]*(r-l+1)+1ll*s1[y]*(r+1)-s2[y];val%=mod+1,val+=mod+1,val%=mod+1;
		// cout<<l<<" "<<r<<" "<<val<<"\n";
		(lst+=val)&=m;(ans+=val)&=mod;
		rt=merge(merge(x,y),z);
	}
	// cout<<idx<<"\n";
	printf("%lld\n",ans);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen("1.out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}