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
const int maxn=100010;
const int inf=1e9;

int n,m,q,a[maxn];
#define lb(x) (x&(-x))
int tree[maxn];
void upd(int x,int w){
    while(x<=n)tree[x]+=w,x+=lb(x);
}
int que(int x){
    int res=0;
    while(x)res+=tree[x],x-=lb(x);
    return res;
}
int que(int l,int r){return que(r)-que(l-1);}
struct node{
    int op,u,v,k,id;
}ask[maxn<<2],tmp[maxn<<2];
int ans[maxn];
void sovle(int l,int r,int ql,int qr){
    if(ql>qr)return ;
    // cout<<l<<" "<<r<<" "<<ql<<" "<<qr<<"\n";
    if(l==r){
        for(int i=ql;i<=qr;i++)if(ask[i].op)ans[ask[i].id]=l;
        return ;
    }
    int mid=(l+r)>>1,pl=ql,pr=1,p=l-1;
    for(int i=ql;i<=qr;i++){
        if(ask[i].op){
            int val=que(ask[i].u,ask[i].v);
            if(val>=ask[i].k)ask[pl++]=ask[i];
            else ask[i].k-=val,tmp[pr++]=ask[i];
        }
        else{
            if(ask[i].v<=mid)ask[pl++]=ask[i],upd(ask[i].u,ask[i].k);
            else tmp[pr++]=ask[i];
        }
    }
    for(int i=ql;i<pl;i++)if(!ask[i].op)upd(ask[i].u,-ask[i].k);
    p=pl-1;
    for(int i=1;i<pr;i++)ask[pl++]=tmp[i];
    sovle(l,mid,ql,p),sovle(mid+1,r,p+1,qr);
}
void work(){
    n=read();q=read();
    for(int i=1;i<=n;i++)a[i]=read(),ask[++m]={0,i,a[i],1,0};
    for(int i=1;i<=q;i++){
        char ch=getchar();while(ch!='C'&&ch!='Q')ch=getchar();
        if(ch=='Q'){
            int l=read(),r=read(),k=read();
            ask[++m]={1,l,r,k,i};
        }
        else{
            int u=read(),v=read();
            ask[++m]={0,u,a[u],-1,i},ask[++m]={0,u,a[u]=v,1,i};
            ans[i]=-1;
        }
    }
    sovle(0,inf,1,m);
    for(int i=1;i<=q;i++)if(~ans[i])printf("%lld\n",ans[i]);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}