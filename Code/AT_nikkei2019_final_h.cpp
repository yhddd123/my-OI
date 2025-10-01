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
const int maxn=200010;
const int inf=1e15;
bool mbe;

int n,ans,op[maxn];
tuple<int,int,int> a[maxn];
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
struct nd{
    int v,p1,p2;
};
bool operator<(nd u,nd v){return u.v<v.v;}
nd operator+(nd u,nd v){return {u.v+v.v,u.p1,v.p2};}
struct node{
    int mn,tag,p;
    nd a,b,ra,lb,mx,ab,ba;
}tree[maxn<<2];
node operator+(node u,node v){
    node res;
    res.mn=min(u.mn,v.mn),res.tag=0;
    res.a=max(u.a,v.a);
    res.b=max(u.b,v.b);
    res.ba=max({u.ba,v.ba,v.a+u.b});
    res.mx=max({u.mx,v.mx,u.a+v.b});
    if(u.mn<v.mn){
        res.ab=max({u.ab,v.ab,v.mx,u.ra+v.b});
        res.ra=max(u.ra,v.a),res.lb=u.lb;
        res.p=u.p;
    }
    else if(u.mn>v.mn){
        res.ab=max({u.ab,u.mx,v.ab,u.a+v.lb});
        res.ra=v.ra,res.lb=max(u.b,v.lb);
        res.p=v.p;
    }
    else{
        res.ab=max({u.ab,v.ab,u.ra+v.lb});
        res.lb=u.lb,res.ra=v.ra;
        res.p=v.p;
    }
    return res;
}
void init(int o,int p){
    nd va={-inf,0,0},vb={-inf,0,0};
    if(p<=n){
        if(!op[p])va={get<1>(a[p]),p,0};
        else if(op[p]==1)vb={get<2>(a[p])-get<1>(a[p]),0,p};
    }
    tree[o].ra=tree[o].a=va,tree[o].lb=tree[o].b=vb,tree[o].mx=tree[o].ab=tree[o].ba={-inf,0,0};
}
void build(int nd,int l,int r){
	tree[nd].p=l;
    if(l==r)return init(nd,l);
    build(ls,l,mid),build(rs,mid+1,r);
    tree[nd]=tree[ls]+tree[rs];
}
void upd(int nd,int w){tree[nd].mn+=w,tree[nd].tag+=w;}
void down(int nd){upd(ls,tree[nd].tag),upd(rs,tree[nd].tag),tree[nd].tag=0;}
void updata(int nd,int l,int r,int ql,int qr,int w){
    if(ql>qr)return ;
    if(l>=ql&&r<=qr)return upd(nd,w);
    if(tree[nd].tag)down(nd);
    if(ql<=mid)updata(ls,l,mid,ql,qr,w);
    if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
    tree[nd]=tree[ls]+tree[rs];
}
void modif(int nd,int l,int r,int p){
    if(l==r)return init(nd,l);
    if(tree[nd].tag)down(nd);
    if(p<=mid)modif(ls,l,mid,p);
    else modif(rs,mid+1,r,p);
    tree[nd]=tree[ls]+tree[rs];
}
node query(int nd,int l,int r,int ql,int qr){
    if(l>=ql&&r<=qr)return tree[nd];
    if(tree[nd].tag)down(nd);
    if(qr<=mid)return query(ls,l,mid,ql,qr);
    if(ql>mid)return query(rs,mid+1,r,ql,qr);
    return query(ls,l,mid,ql,qr)+query(rs,mid+1,r,ql,qr);
}
void work(){
    n=read();
    for(int i=1;i<=n;i++)a[i]={read(),read(),read()};
    sort(a+1,a+n+1);
    priority_queue<pii> q;
    for(int i=1;i<=n;i++)q.push({(get<2>(a[i])),i});
    build(1,1,n+1);
    for(int i=1,j=1;i<=n;i++){
        while(j<=n&&get<0>(a[j])<i)j++;
        // for(int k=1;k<=n;k++)cout<<query(1,1,n+1,k,k).mn<<" ";cout<<"\n";
        nd res=max({tree[1].ab,tree[1].ba});
        res=max(res,query(1,1,n+1,j,n+1).a);
        if(j>1){
        	node val=query(1,1,n+1,1,j-1);
        	int p=val.mn==0?val.p:0;
        	if(p<=n+1)res=max(res,query(1,1,n+1,p,n+1).a);
        	// cout<<p<<" "<<j<<"\n";
        }
        while(!q.empty()&&op[q.top().se])q.pop();
        if(!q.empty())res=max(res,{q.top().fi,n+1,0});
        ans+=res.v;
        // cout<<res.v<<" "<<res.p1<<" "<<res.p2<<"\n";
        if(!res.p2){
        	// if(res.p1==n+1)cout<<q.top().se<<"\n";
            if(res.p1==n+1)op[q.top().se]=2,modif(1,1,n+1,q.top().se);
            else op[res.p1]=1,modif(1,1,n+1,res.p1);
            if(res.p1<=j)updata(1,1,n+1,res.p1,j-1,-1);
            else updata(1,1,n+1,j,res.p1-1,1);
        }
        else{
            op[res.p1]=1,op[res.p2]=2;modif(1,1,n+1,res.p1),modif(1,1,n+1,res.p2);
            if(res.p1<=res.p2)updata(1,1,n+1,res.p1,res.p2-1,-1);
            else updata(1,1,n+1,res.p2,res.p1-1,1);
        }
        printf("%lld\n",ans);
    }
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