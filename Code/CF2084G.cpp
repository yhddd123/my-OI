#include<bits/stdc++.h>
#define int long long
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
const int maxn=500010;
const int inf=1e18;

int n,p[maxn],ans;
#define ls lc[u]
#define rs rc[u]
struct Vec{
    int a[3];
    Vec(int _a=0,int _b=0,int _c=0){a[0]=_a,a[1]=_b,a[2]=_c;}
}tree[maxn];
int lc[maxn],rc[maxn],rt,idx;
int w[maxn],siz[maxn];
struct Tag{
    int a[3][3];
    Tag(int _a=1,int _b=0,int _c=0,int _d=0,int _e=1,int _f=0,int _g=0,int _h=0,int _i=1){
        a[0][0]=_a,a[0][1]=_b,a[0][2]=_c,a[1][0]=_d,a[1][1]=_e,a[1][2]=_f,a[2][0]=_g,a[2][1]=_h,a[2][2]=_i;
    }
}tag[maxn];
Vec operator*(const Vec &u,const Tag &v){
    Vec res;
    for(int i=0;i<3;i++){
        res.a[i]=0;
        for(int j=0;j<3;j++){
            res.a[i]+=u.a[j]*v.a[j][i];
        }
    }
    return res;
}
Tag operator*(const Tag &u,const Tag &v){
    Tag res;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            res.a[i][j]=0;
            for(int k=0;k<3;k++)res.a[i][j]+=u.a[i][k]*v.a[k][j];
        }
    }
    return res;
}
mt19937 rnd(1);
int newnode(int g,int j){
    int u=++idx;
    ls=rs=0;w[u]=rnd();siz[u]=1;
    tree[u]=Vec(g,j,1);tag[u]=Tag();
    return idx;
}
void upd(int u,Tag w){tree[u]=tree[u]*w,tag[u]=tag[u]*w;}
void down(int u){upd(ls,tag[u]),upd(rs,tag[u]),tag[u]=Tag();}
void up(int u){siz[u]=siz[ls]+siz[rs]+1;}
int merge(int u,int v){
    if(!u||!v)return u|v;
    down(u),down(v);
    if(w[u]<w[v]){
        rs=merge(rs,v);
        up(u);return u;
    }
    else{
        lc[v]=merge(u,lc[v]);
        up(v);return v;
    }
}
pii split(int u){
    if(!u)return {0,0};
    down(u);
    if(tree[u].a[0]<0){
        pii t=split(rs);
        rs=t.fi;up(u);
        return {u,t.se};
    }
    else{
        pii t=split(ls);
        ls=t.se;up(u);
        return {t.fi,u};
    }
}
int st[maxn],tp;
void dfs(int u){
    if(!u)return ;
    down(u);
    dfs(ls),st[++tp]=tree[u].a[0],dfs(rs);
}
void work(){
    n=read();
    for(int i=1;i<=n;i++)p[i]=-1;
    for(int i=1;i<=n;i++)p[read()]=i&1;
    idx=rt=0;
    int l=0,r=0,x=0;
    if(p[1]==1)l=r=1;
    else if(p[1]==-1){
        r=1;
        rt=newnode(0,1);
    }
    for(int i=1;i<n;i++){
        x+=2*l*l-(2*i+(n&1))*l+i*((n+1)/2);
        // cout<<i<<" "<<x<<" "<<-(2*i+(n&1))-2<<"\n";
        upd(rt,Tag(1,0,0,4,1,0,-(2*i+(n&1))-2,0,1));
        // tp=0;dfs(rt);
        // st[0]=x;for(int j=1;j<=tp;j++)st[j]+=st[j-1];
        // for(int j=0;j<=tp;j++)cout<<st[j]<<" ";cout<<"\n";
        if(p[i+1]==1){
            upd(rt,Tag(1,0,0,0,1,0,0,1,1));
            l++,r++;
        }
        else if(p[i+1]==-1){
            auto[u,v]=split(rt);
            upd(v,Tag(1,0,0,0,1,0,0,1,1));
            int w=newnode(0,l+siz[u]+1);
            rt=merge(u,merge(w,v));
            r++;
        }
    }
    tp=0;dfs(rt);
    st[0]=x;for(int i=1;i<=tp;i++)st[i]+=st[i-1];
    // cout<<l<<" "<<r<<"\n";
    // for(int i=0;i<=tp;i++)cout<<st[i]<<" ";cout<<"\n";
    ans=-st[(n+1)/2-l];for(int i=1;i<=n;i++)ans+=i*i;
    printf("%lld\n",ans);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=read();
    while(T--)work();
}