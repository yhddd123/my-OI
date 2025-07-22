#include<bits/stdc++.h>
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
const int maxn=300010;
const int inf=1e9;

int n,q,a[maxn],ans;
map<int,set<int>> mp;
int pre[maxn];
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
int mn[maxn<<2],mx[maxn<<2],gg[maxn<<2],pl[maxn<<2];
void build(int nd,int l,int r){
    if(l==r){
        mn[nd]=mx[nd]=a[l],gg[nd]=abs(a[l]-a[l-1]);pl[nd]=pre[l];
        return ;
    }
    build(ls,l,mid),build(rs,mid+1,r);
    mn[nd]=min(mn[ls],mn[rs]),mx[nd]=max(mx[ls],mx[rs]),gg[nd]=__gcd(gg[ls],gg[rs]),pl[nd]=max(pl[ls],pl[rs]);
}
void modif(int nd,int l,int r,int p){
    if(l==r){
        mn[nd]=mx[nd]=a[l],gg[nd]=abs(a[l]-a[l-1]);pl[nd]=pre[l];
        return ;
    }
    if(p<=mid)modif(ls,l,mid,p);
    else modif(rs,mid+1,r,p);
    mn[nd]=min(mn[ls],mn[rs]),mx[nd]=max(mx[ls],mx[rs]),gg[nd]=__gcd(gg[ls],gg[rs]),pl[nd]=max(pl[ls],pl[rs]);
}
int quemn(int nd,int l,int r,int ql,int qr){
    if(l>=ql&&r<=qr)return mn[nd];
    if(qr<=mid)return quemn(ls,l,mid,ql,qr);
    if(ql>mid)return quemn(rs,mid+1,r,ql,qr);
    return min(quemn(ls,l,mid,ql,qr),quemn(rs,mid+1,r,ql,qr));
}
int quemx(int nd,int l,int r,int ql,int qr){
    if(l>=ql&&r<=qr)return mx[nd];
    if(qr<=mid)return quemx(ls,l,mid,ql,qr);
    if(ql>mid)return quemx(rs,mid+1,r,ql,qr);
    return max(quemx(ls,l,mid,ql,qr),quemx(rs,mid+1,r,ql,qr));
}
int quegg(int nd,int l,int r,int ql,int qr){
    if(l>=ql&&r<=qr)return gg[nd];
    if(qr<=mid)return quegg(ls,l,mid,ql,qr);
    if(ql>mid)return quegg(rs,mid+1,r,ql,qr);
    return __gcd(quegg(ls,l,mid,ql,qr),quegg(rs,mid+1,r,ql,qr));
}
int quepl(int nd,int l,int r,int ql,int qr){
    if(l>=ql&&r<=qr)return pl[nd];
    if(qr<=mid)return quepl(ls,l,mid,ql,qr);
    if(ql>mid)return quepl(rs,mid+1,r,ql,qr);
    return max(quepl(ls,l,mid,ql,qr),quepl(rs,mid+1,r,ql,qr));
}
void work(){
    n=read();q=read();
    for(int i=1;i<=n;i++)a[i]=read(),mp[a[i]].insert(i);
    for(int i=1;i<=n;i++){
        auto it=mp[a[i]].lower_bound(i);
        if(it==mp[a[i]].begin())pre[i]=0;
        else pre[i]=(*--it);
    }
    build(1,1,n);
    int qq=0;
    while(q--){
        int op=read();
        if(op==1){
            int x=read()^ans,y=read()^ans;
            auto it=mp[a[x]].lower_bound(x);
            it=mp[a[x]].erase(it);
            if(it!=mp[a[x]].end())pre[*it]=pre[x],modif(1,1,n,(*it));
            a[x]=y;mp[a[x]].insert(x);
            it=mp[a[x]].lower_bound(x);
            if(it!=mp[a[x]].begin())pre[x]=(*--it),it++;
            else pre[x]=0;
            modif(1,1,n,x);
            if(it!=--mp[a[x]].end())it++,pre[(*it)]=x,modif(1,1,n,(*it));
            if(x<=n)modif(1,1,n,x+1);
        }
        if(op==2){
            int l=read()^ans,r=read()^ans,k=read()^ans;
            if(l==r)puts("Yes"),++ans;
            else if(quemx(1,1,n,l,r)-quemn(1,1,n,l,r)==(r-l)*k){
                if(!k)puts("Yes"),++ans;
                else if(quegg(1,1,n,l+1,r)==k&&quepl(1,1,n,l,r)<l)puts("Yes"),++ans;
                else puts("No");
            }
            else puts("No");
        }
    }
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen("A.out","w",stdout);
    
    T=1;
    while(T--)work();
}