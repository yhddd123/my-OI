#include<bits/stdc++.h>
// #define int long long
#define mod 998244353ll
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
const int maxn=5010;
const int maxm=maxn*40;
const int inf=1e9;
bool mbe;

int n;
pii a[maxn];
int head[maxm],tot=1;
struct nd{
    int nxt,to,w;
}e[maxm<<2];
void add(int u,int v,int w=1){
	// cout<<u<<" "<<v<<"\n";
    e[++tot]={head[u],v,w};head[u]=tot;
    e[++tot]={head[v],u,0};head[v]=tot;
}
int s,t,flow,idx;
int dep[maxm],rad[maxm];
queue<int> q;
bool bfs(){
    for(int i=1;i<=idx;i++)dep[i]=0,rad[i]=head[i];
    dep[s]=1;q.push(s);
    while(!q.empty()){
        int u=q.front();q.pop();
        for(int i=head[u];i;i=e[i].nxt){
            int v=e[i].to;
            if(e[i].w&&!dep[v]){
                dep[v]=dep[u]+1;
                q.push(v);
            }
        }
    }
    return dep[t];
}
int dfs(int u,int res){
    if(u==t)return res;
    int cnt=0;
    for(int i=rad[u];i;i=e[i].nxt){
        int v=e[i].to;rad[u]=i;
        if(e[i].w&&dep[v]==dep[u]+1){
            int out=dfs(v,min(e[i].w,res));
            cnt+=out,res-=out;
            e[i].w-=out,e[i^1].w+=out;
            if(!res)break;
        }
    }
    return cnt;
}
#define mid (l+r>>1)
#define ls lc[nd]
#define rs rc[nd]
int rt,lc[maxm],rc[maxm];
void updata(int &nd,int l,int r,int p){
	int lst=nd;nd=++idx;ls=lc[lst],rs=rc[lst];
	if(l==r){add(nd,p);return ;}
	if(p<=mid)updata(ls,l,mid,p);
	else updata(rs,mid+1,r,p);
	if(rs)add(nd,rs,inf);
	if(ls)add(nd,ls,inf);
}
void query(int nd,int l,int r,int ql,int qr,int w){
	if(!nd||ql>qr)return ;
	if(l>=ql&&r<=qr){add(w,nd);return ;}
	if(ql<=mid)query(ls,l,mid,ql,qr,w);
	if(qr>mid)query(rs,mid+1,r,ql,qr,w);
}
int id[maxn<<1];
void work(){
    n=read();
    for(int i=1;i<=n;i++)a[i]={read(),read()},id[a[i].fi]=i;
    idx=2*n;s=++idx,t=++idx;
    for(int i=1;i<=n;i++)add(s,a[i].fi,1),add(a[i].se,t,1);
    for(int i=1;i<=2*n;i++)if(id[i]){
    	query(rt,1,2*n,i,a[id[i]].se,i);
    	updata(rt,1,2*n,a[id[i]].se);
    }
    while(bfs())flow+=dfs(s,inf);
    printf("%d\n",2*n-flow);
}

bool med;
int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen("A.out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    T=1;
    while(T--)work();
}