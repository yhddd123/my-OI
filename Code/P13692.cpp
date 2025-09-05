#include<bits/stdc++.h>
#include "lawn.h"
#define ll long long
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;

const int maxn=200010;
const ll inf=1e18;


int n;ll m,t;
ll a[maxn],v[maxn];
ll mn[maxn],val[maxn],tag[maxn];
int pos[maxn],laz[maxn];
int w[maxn],ls[maxn],rs[maxn],idx,rt;
mt19937 rnd(1);
void up(int u){mn[u]=min({val[u],mn[ls[u]],mn[rs[u]]});}
void upd(int u,ll w1,int w2){if(!u)return ;mn[u]+=w1,val[u]+=w1,tag[u]+=w1;pos[u]+=w2,laz[u]+=w2;}
void down(int u){upd(ls[u],tag[u],laz[u]),upd(rs[u],tag[u],laz[u]),tag[u]=laz[u]=0;}
int merge(int u,int v){
	if(!u||!v)return u|v;
	down(u),down(v);
	if(w[u]<w[v]){
		rs[u]=merge(rs[u],v);up(u);
		return u;
	}
	else{
		ls[v]=merge(u,ls[v]);up(v);
		return v;
	}
}
pii split(int u,int k){
	if(!u)return {0,0};
	down(u);
	if(pos[u]>k){
		pii t=split(ls[u],k);
		ls[u]=t.se;
		up(u);
		return {t.fi,u};
	}
	else{
		pii t=split(rs[u],k);
		rs[u]=t.fi;
		up(u);
		return {u,t.se};
	}
}
int newnode(int j,ll v){
	w[++idx]=rnd();pos[idx]=j,mn[idx]=val[idx]=v;
	return idx;
}
// void dfs(int u){
	// if(!u)return ;
	// down(u);
	// dfs(ls[u]);
	// cout<<pos[u]<<" "<<val[u]<<"\n";
	// dfs(rs[u]);
// }
ll mow(int N, int C, int B, std::vector<int> &A, std::vector<int> &V) {
    n=N,m=C,t=B;
    for(int i=1;i<=n;i++)a[i]=A[i-1],v[i]=V[i-1];
    mn[0]=inf;
    rt=newnode(0,0);
    for(int i=1;i<=n;i++){
    	int x,y,z;
    	if(v[i]%m==0){
    		pii p=split(rt,0);x=p.fi,y=p.se;
    		ll vv=mn[y]+1ll*(v[i]/m+1)*(a[i]+t);
	    	upd(x,1ll*(v[i]/m)*(a[i]+t),0);
	    	upd(y,1ll*(v[i]/m)*(a[i]+t)+a[i],0);
	    	mn[x]=val[x]=min(mn[x],vv);
	    	rt=merge(x,y);
    	}
    	else{
	    	pii p=split(rt,m-v[i]%m-1);x=p.fi,y=p.se;
	    	p=split(y,m-v[i]%m);y=p.fi,z=p.se;
	    	// cout<<x<<" "<<y<<" "<<z<<"\n";
	    	ll vv=min(mn[x]+1ll*(v[i]/m+1)*(a[i]+t),mn[z]+1ll*(v[i]/m+2)*(a[i]+t));
	    	upd(x,1ll*(v[i]/m)*(a[i]+t)+a[i],v[i]%m);
	    	upd(y,1ll*(v[i]/m+1)*(a[i]+t),v[i]%m-m);
	    	upd(z,1ll*(v[i]/m+1)*(a[i]+t)+a[i],v[i]%m-m);
	    	if(y)mn[y]=val[y]=min(mn[y],vv);
	    	else y=newnode(0,vv);
	    	rt=merge(merge(y,z),x);
    	}
    	// cout<<i<<"\n";
    	// dfs(rt);
    }
    pii p=split(rt,0);
    return mn[p.fi];
}

int main() {
int n, c, b;
std::cin >> n >> c >> b;
std::vector<int> a(n);
std::vector<int> v(n);
for (int i = 0; i < n; i++)std::cin >> a[i];
for (int i = 0; i < n; i++)std::cin >> v[i];
std::cout << mow(n, c, b, a, v) << std::endl;
return 0;
}