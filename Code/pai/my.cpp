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
const int maxn=100010;
const int inf=1e9;
bool mbe;

int n,q,ed[maxn];
int a[maxn],op[maxn];
vector<int> e[maxn];
int fa[maxn],siz[maxn],son[maxn],dep[maxn];
void dfs(int u){
	siz[u]=1,son[u]=0;dep[u]=dep[fa[u]]+1;
    for(int v:e[u])if(v!=fa[u]){
    	fa[v]=u,dfs(v);siz[u]+=siz[v];
        if(siz[v]>siz[son[u]])son[u]=v;
    }
}
int dfn[maxn],rnk[maxn],tim,tp[maxn],st[17][maxn];
void dfs(int u,int lst){
	rnk[dfn[u]=++tim]=u,st[0][tim]=fa[u];tp[u]=lst;
	if(!son[u])return ;dfs(son[u],lst);
	for(int v:e[u])if(v!=fa[u]&&v!=son[u])dfs(v,v);
}
int mmax(int u,int v){return dfn[u]<dfn[v]?u:v;}
int lca(int u,int v){
	if(u==v)return u;
	u=dfn[u],v=dfn[v];
	if(u>v)swap(u,v);u++;
	int k=__lg(v-u+1);
	return mmax(st[k][u],st[k][v-(1<<k)+1]);
}
#define mid ((l+r)>>1)
#define ls lc[nd]
#define rs rc[nd]
bool tree[maxn<<6];
int rt[maxn],lc[maxn<<6],rc[maxn<<6],idx;
void updata(int &nd,int l,int r,int ql,int qr){
	if(!nd)nd=++idx;
	if(tree[nd])return ;
	if(l>=ql&&r<=qr){tree[nd]=1;return ;}
	if(ql<=mid)updata(ls,l,mid,ql,qr);
	if(qr>mid)updata(rs,mid+1,r,ql,qr);
	tree[nd]=tree[ls]&tree[rs];
}
bool query(int nd,int l,int r,int p){
	if(!nd)return 0;
	if(tree[nd])return 1;
	if(l==r)return tree[nd];
	if(p<=mid)return query(ls,l,mid,p);
	else return query(rs,mid+1,r,p);
}
int merge(int u,int v,int l,int r){
    if(!u||!v)return u|v;
    if(l==r){tree[u]|=tree[v];return u;}
    if(tree[u])return u;
    if(tree[v])return v;
    lc[u]=merge(lc[u],lc[v],l,mid),rc[u]=merge(rc[u],rc[v],mid+1,r);
    tree[u]=tree[lc[u]]&tree[rc[u]];
    return u;
}
void upd(int &rt,int u,int v){
	while(tp[u]!=tp[v]){
		if(dep[tp[u]]<dep[tp[v]])swap(u,v);
		updata(rt,1,n,dfn[tp[u]],dfn[u]);
		u=fa[tp[u]];
	}
	if(dep[u]<dep[v])swap(u,v);
	updata(rt,1,n,dfn[v],dfn[u]);
}
int pos[maxn];
void merge(int u,int v){
	rt[u]=merge(rt[u],rt[v],1,n);
	// cout<<u<<" "<<v<<" "<<pos[u]<<" "<<pos[v]<<" "<<lca(pos[u],pos[v])<<"\n";
	upd(rt[u],pos[u],pos[v]);
	pos[u]=lca(pos[u],pos[v]);
}
bool chk(int rt,int p){return query(rt,1,n,dfn[p]);}
int f[maxn];
int fd(int x){
	if(f[x]==x)return x;
	return f[x]=fd(f[x]);
}
bool in(int u,int v){return dfn[u]<=dfn[v]&&dfn[v]<dfn[u]+siz[u];}
bool chk1(int u,int v,int x){
	while(tp[u]!=tp[v]){
		if(dep[tp[u]]<dep[tp[v]])swap(u,v);
		if(dfn[tp[u]]<=dfn[x]&&dfn[x]<=dfn[u])return 1;
		u=fa[tp[u]];
	}
	if(dep[u]<dep[v])swap(u,v);
	if(dfn[u]<=dfn[x]&&dfn[x]<=dfn[v])return 1;
	return 0;
}
bool chk(int u,int v,int x){
	// if(chk1(pos[u],pos[v],x))return 1;
	if((in(x,pos[u])||in(x,pos[v]))&&in(lca(pos[u],pos[v]),x))return 1;
	if(chk(rt[u],x)||chk(rt[v],x))return 1;
	return 0;
}
void work(){
	n=read();
    for(int i=1;i<n;i++){
        int u=read(),v=read();
        e[u].pb(v),e[v].pb(u);
    }
    dfs(1),dfs(1,1);
    for(int j=1;j<=16;j++){
    	for(int i=1;i+(1<<j)-1<=n;i++)st[j][i]=mmax(st[j-1][i],st[j-1][i+(1<<j-1)]);
    }
    q=read();
    for(int i=1;i<=q;i++){
        char ch=getchar();
        while(ch!='b'&&ch!='s')ch=getchar();
        if(ch=='s')op[i]=1;
        else op[i]=0;
        a[i]=read();
    }
    for(int i=1;i<=q+1;i++)f[i]=i;
    for(int i=q;i;i--){
        if(op[i]){
            upd(rt[i],a[i],a[i]);pos[i]=a[i];
            int &p=ed[i]=i;
            while(p<q){
                if(ed[p+1]!=p){
                	merge(i,p+1);
                    rt[i]=merge(rt[i],rt[p+1],1,n);
                    p=ed[p+1];
                }
                else{
                    if(chk(rt[i],a[p+1]))p++;
                    else{
                    	int pp=fd(p+1);
                    	if(pp==q+1)break;
                    	bool fl=1;for(int j=p+1;j<pp;j++){
                    		if(!chk(i,pp,a[j])){
                    			fl=0;break;
                    		}
                    	}
                    	if(!fl)break;
                    	else p=pp-1;
                    }
                }
            }
        }
        else{
            if(chk(rt[i+1],a[i])){
                ed[i]=ed[i+1];
                rt[i]=rt[i+1],pos[i]=pos[i+1];
            }
            else ed[i]=i-1,f[i]=fd(i+1);
        }
    }
    for(int i=1;i<=q;i++)printf("%d\n",ed[i]-i+1);
}

bool med;
signed main(){
	// freopen("excite.in","r",stdin);
	// freopen("excite.out","w",stdout);
	
	cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	int T=1;
	while(T--)work();
}