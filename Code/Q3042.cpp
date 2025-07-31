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
const int maxn=300010;
const int inf=1e9;
bool mbe;

int q,n,m;
int sum[maxn],lst[maxn];
#define mid (l+r>>1)
#define ls nd<<1
#define rs nd<<1|1
pii tree[maxn<<2];
pii operator*(pii u,pii v){return {u.fi*v.fi%mod,(u.fi*v.se+u.se)%mod};}
void build(int nd,int l,int r){
	tree[nd]={1,0};
	if(l==r)return ;
	build(ls,l,mid),build(rs,mid+1,r);
}
void upd(int nd,pii w){tree[nd]=w*tree[nd];}
void down(int nd){upd(ls,tree[nd]),upd(rs,tree[nd]),tree[nd]={1,0};}
void modif(int nd,int l,int r,int p,pii w){
    if(l==r){tree[nd]=w;return ;}
    down(nd);
    if(p<=mid)modif(ls,l,mid,p,w);
    else modif(rs,mid+1,r,p,w);
}
pii query(int nd,int l,int r,int p){
    if(l==r)return tree[nd];
    down(nd);
    if(p<=mid)return query(ls,l,mid,p);
    else return query(rs,mid+1,r,p);
}
void work(){
    n=q=read();
    build(1,0,n);
    modif(1,0,n,0,{1,0});
    while(q--){
        int op=read();
        if(op==1){
            int k=read();
            ++m;sum[m]=(k?sum[m-1]+k:0);lst[m]=(k?lst[m-1]:m);
            k?upd(1,{1,k}):upd(1,{2,0});
            modif(1,0,n,m,{1,0});
        }
        if(op==2){
            int p=read(),x=read();
            pii res=query(1,0,n,p);
            // cout<<res.fi<<" "<<res.se<<"\n";
            int pp=0,dd=0;
            if(p&&lst[p]==p)pp=res.fi+res.se*2,dd=res.fi*2;
            else pp=res.se,dd=res.fi;
            printf("%lld\n",pp+(x-1)*dd);
        }
        if(op==3){
            int x=read();
            int p=m,res=0;
            while(p){
                if(lst[p]==p){
                    if(x&1){res=p;break;}
                    else x>>=1,p--;
                }
                else if(sum[p]<x){
                    x-=sum[p],p=lst[p];
                }
                else{
                    int q=upper_bound(sum+lst[p],sum+p+1,sum[p]-x)-sum-1;
                    res=q+1;break;
                }
            }
            printf("%lld\n",res);
        }
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