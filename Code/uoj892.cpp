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
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n,q,a[maxn];
long long ans[maxn];
void updans(int l,int r,long long w){ans[l]+=w,ans[r+1]-=w;}
vector<pii> mdf[maxn];
int lsh1[maxn<<1],len1,lsh2[maxn<<1],len2;
vector<tuple<int,int,int>> ask[maxn*2];
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
struct Tag{
    int ta,tb;
    long long x,y,z,w;
    operator bool(){return ta||tb||x||y||z||w;}
}tag[maxn<<3];
Tag operator+(Tag u,Tag v){
    return {u.ta+v.ta,u.tb+v.tb,u.x+v.x,u.y+v.y+v.x*u.tb,u.z+v.z+v.x*u.ta,u.w+v.w+v.x*u.ta*u.tb+v.y*u.ta+v.z*u.tb};
}
struct node{
    int mxa,sea,mxb,seb;long long his;
}tree[maxn<<3];
node operator+(node u,Tag v){
    return {u.mxa+v.ta,u.sea,u.mxb+v.tb,u.seb,u.his+v.x*u.mxa*u.mxb+v.y*u.mxa+v.z*u.mxb+v.w};
}
node operator+(node u,node v){
    node res;
    res.mxa=max(u.mxa,v.mxa),res.sea=max(res.mxa==u.mxa?u.sea:u.mxa,res.mxa==v.mxa?v.sea:v.mxa);
    res.mxb=max(u.mxb,v.mxb),res.seb=max(res.mxb==u.mxb?u.seb:u.mxb,res.mxb==v.mxb?v.seb:v.mxb);
    res.his=u.his+v.his;
    return res;
}
void build(int nd,int l,int r,int va,int vb){
    tag[nd]={0,0,0,0,0,0};
    if(l==r){
        tree[nd]={va,-1,vb,-1,0};
        return ;
    }
    build(ls,l,mid,va,vb),build(rs,mid+1,r,va,vb);
    tree[nd]=tree[ls]+tree[rs];
}
void upd(int nd,Tag w){tree[nd]=tree[nd]+w,tag[nd]=tag[nd]+w;}
void down(int nd){
	int mxa=max(tree[ls].mxa,tree[rs].mxa),mxb=max(tree[ls].mxb,tree[rs].mxb);
	if(tree[ls].mxa==mxa&&tree[ls].mxb==mxb)upd(ls,tag[nd]);
	else if(tree[ls].mxa==mxa)upd(ls,{tag[nd].ta,0,tag[nd].x,0,tag[nd].z,0});
	else if(tree[ls].mxb==mxb)upd(ls,{0,tag[nd].tb,tag[nd].x,tag[nd].y,0,0});
	else upd(ls,{0,0,tag[nd].x,0,0,0});
	if(tree[rs].mxa==mxa&&tree[rs].mxb==mxb)upd(rs,tag[nd]);
	else if(tree[rs].mxa==mxa)upd(rs,{tag[nd].ta,0,tag[nd].x,0,tag[nd].z,0});
	else if(tree[rs].mxb==mxb)upd(rs,{0,tag[nd].tb,tag[nd].x,tag[nd].y,0,0});
	else upd(rs,{0,0,tag[nd].x,0,0,0});
	tag[nd]={0,0,0,0,0,0};}
void chkmna(int nd,int l,int r,int ql,int qr,int w){
    if(w>tree[nd].mxa)return ;
    if(w>tree[nd].sea&&l>=ql&&r<=qr)return upd(nd,{w-tree[nd].mxa,0,0,0,0,0});
    if(tag[nd])down(nd);
    if(ql<=mid)chkmna(ls,l,mid,ql,qr,w);
    if(qr>mid)chkmna(rs,mid+1,r,ql,qr,w);
    tree[nd]=tree[ls]+tree[rs];
}
void chkmnb(int nd,int l,int r,int ql,int qr,int w){
    if(w>tree[nd].mxb)return ;
    if(w>tree[nd].seb&&l>=ql&&r<=qr)return upd(nd,{0,w-tree[nd].mxb,0,0,0,0});
    if(tag[nd])down(nd);
    if(ql<=mid)chkmnb(ls,l,mid,ql,qr,w);
    if(qr>mid)chkmnb(rs,mid+1,r,ql,qr,w);
    tree[nd]=tree[ls]+tree[rs];
}
void dfs(int nd,int l,int r){
    if(l==r){
        updans(lsh2[l],lsh2[l+1]-1,tree[nd].his);
        return ;
    }
    if(tag[nd])down(nd);
    dfs(ls,l,mid),dfs(rs,mid+1,r);
}
void sovle(int ll,int rr){
    if(ll==rr){
        int lst=1,v=a[ll];
        for(auto[t,w]:mdf[ll]){
            if(lst<t)updans(lst,t-1,v);
            lst=t;v=w;
        }
        return ;
    }
    int mm=ll+rr>>1;
    sovle(ll,mm),sovle(mm+1,rr);
    len1=0,len2=0;lsh2[++len2]=q+1;
    for(int i=ll;i<=rr;i++){
        for(auto[t,w]:mdf[i])if(t<=q){
            lsh1[++len1]=w,lsh2[++len2]=t;
        }
    }
    sort(lsh1+1,lsh1+len1+1),len1=unique(lsh1+1,lsh1+len1+1)-lsh1-1;
    sort(lsh2+1,lsh2+len2+1),len2=unique(lsh2+1,lsh2+len2+1)-lsh2-1;
    for(int i=1;i<=len1;i++)ask[i].clear();
    for(int i=ll;i<=rr;i++){
        int lst=1,v=a[i];
        for(auto[t,w]:mdf[i]){
            if(lst<t)ask[lower_bound(lsh1+1,lsh1+len1+1,v)-lsh1].pb({lower_bound(lsh2+1,lsh2+len2+1,lst)-lsh2,lower_bound(lsh2+1,lsh2+len2+1,t)-lsh2-1,i});
            lst=t,v=w;
        }
    }
    // cout<<ll<<" "<<rr<<" "<<len1<<" "<<len2<<"\n";
    build(1,1,len2-1,mm-ll+1,rr-mm);
    for(int i=1;i<=len1;i++){
        upd(1,{0,0,lsh1[i]-lsh1[i-1],0,0,0});
        // cout<<i<<" "<<lsh1[i]<<" "<<tree[1].his<<" "<<tree[1].mxa<<" "<<tree[1].mxb<<"\n";
        for(auto[pl,pr,p]:ask[i]){
        	// cout<<i<<" "<<pl<<" "<<pr<<" "<<p<<"\n";
            if(p<=mm)chkmna(1,1,len2-1,pl,pr,mm-p);
            else chkmnb(1,1,len2-1,pl,pr,p-mm-1);
        }
    }
    dfs(1,1,len2-1);
}
void work(){
    n=read();q=read();
    for(int i=1;i<=n;i++)a[i]=read(),mdf[i].pb({1,a[i]});
    for(int i=1;i<=q;i++){
        int x=read(),w=read();
        mdf[x].pb({i,w});
    }
    for(int i=1;i<=n;i++)mdf[i].pb({q+1,0});
    sovle(1,n);
    for(int i=1;i<=q;i++)ans[i]+=ans[i-1];
    for(int i=1;i<=q;i++)printf("%lld\n",ans[i]);
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