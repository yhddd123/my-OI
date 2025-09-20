#include<bits/stdc++.h>
#define int long long
#define mod 1000000007ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
inline int read(){
    int x=0,fl=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*fl;
}
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n,m;
int head[maxn],tot=1;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int dfn[maxn],lw[maxn],idx;
int st[maxn],tp;
vector<int> id[maxn];int scct;
bool vis[maxn];
void tar(int u,int fl){
	dfn[u]=lw[u]=++idx;st[++tp]=u;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(i==(fl^1))continue;
		if(!dfn[v]){
			tar(v,i);
			lw[u]=min(lw[u],lw[v]);
		}
		else lw[u]=min(lw[u],dfn[v]);
	}
	if(lw[u]==dfn[u]){
		id[++scct].push_back(st[tp]);
		while(st[tp--]!=u){
			id[scct].push_back(st[tp]);
		}
	}
}
struct calc{
	int _mod;
	int f[1<<17],g[1<<17];
	void fwt(int *a,int w){
		if(w==-1)w=(_mod+1)/2;
	    for(int l=2;l<=(1<<17);l<<=1){
	        for(int i=0;i<(1<<17);i+=l){
	            for(int j=i,k=i+l/2;k<i+l;j++,k++){
	                int u=a[j],v=a[k];
	                a[j]=(u+v)*w%_mod,a[k]=(u+_mod-v)*w%_mod;
	            }
	        }
	    }
	}
	void mul(){
		for(int i=0;i<(1<<17);i++)f[i]=f[i]*g[i]%_mod;
	}
}f1,f2;
void work(){
    n=read();m=read();
    map<pii,int> mp;int s=0;
    for(int i=1;i<=m;i++){
        int u=read(),v=read(),w=read();
        add(u,v),add(v,u);
        mp[{u,v}]=mp[{v,u}]=w;s^=w;
    }
    tar(1,0);
    f1._mod=mod,f2._mod=998244353;
    f1.f[s]=1,f1.fwt(f1.f,1);
    f2.f[s]=1,f2.fwt(f2.f,1);
    for(int i=1;i<=scct;i++)if(id[i].size()>1){
        for(int j=0;j<(1<<17);j++)f1.g[j]=f2.g[j]=0;
        // for(int u:id[i])cout<<u<<" ";cout<<"\n";
        for(int j=0;j<id[i].size();j++){
        	// assert(mp.count({id[i][j],id[i][(j+1)%id[i].size()]}));
        	f1.g[mp[{id[i][j],id[i][(j+1)%id[i].size()]}]]++;
        	f2.g[mp[{id[i][j],id[i][(j+1)%id[i].size()]}]]++;
        }
        f1.fwt(f1.g,1),f2.fwt(f2.g,1);
        f1.mul(),f2.mul();
    }
    f1.fwt(f1.f,-1),f2.fwt(f2.f,-1);
    for(int i=0;i<(1<<17);i++)if(f1.f[i]||f2.f[i]){printf("%lld %lld\n",i,f1.f[i]);return ;}

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