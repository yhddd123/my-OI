#include<bits/stdc++.h>
#define ll long long
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
const int B=100;
const int maxm=maxn/B+10;
const int inf=1e9;

int n,q,a[maxn];ll ans;
stack<pii> b[maxn],c[maxm];
int pl[maxm],pr[maxm],bel[maxn],num;
pii id[maxn];
ll sum[maxm],suf[maxn];
void rebuild(int i){
    for(int j=pl[i];j<=pr[i];j++)id[j]=b[j].top();
    sort(id+pl[i],id+pr[i]+1);
    suf[pr[i]]=id[pr[i]].se;
    for(int j=pr[i]-1;j>=pl[i];j--)suf[j]=suf[j+1]+id[j].se;
}
int ask(int p){
    return b[p].top().fi>=c[bel[p]].top().fi?b[p].top().se:c[bel[p]].top().se;
}
void upd(int l,int r,int w,int x){
    if(bel[l]==bel[r]){
        for(int i=l;i<=r;i++)sum[bel[l]]-=ask(i),b[i].push({x,w});
        sum[bel[l]]+=1ll*(r-l+1)*w;
        rebuild(bel[l]);
        return ;
    }
    upd(l,pr[bel[l]],w,x),upd(pl[bel[r]],r,w,x);
    for(int i=bel[l]+1;i<bel[r];i++)sum[i]=1ll*(pr[i]-pl[i]+1)*w,c[i].push({x,w});
}
ll que(int l,int r){
    ll res=0;
    if(bel[l]==bel[r]){
        for(int i=l;i<=r;i++)res+=ask(i);
        return res;
    }
    res+=que(l,pr[bel[l]])+que(pl[bel[r]],r);
    for(int i=bel[l]+1;i<bel[r];i++)res+=sum[i];
    return res;
}
int ql[maxn],qr[maxn],cnt;
bool vis[maxn];
void del(int l,int r){
    if(bel[l]==bel[r]){
        for(int i=l;i<=r;i++){
            sum[bel[l]]-=ask(i);
            while(vis[b[i].top().fi])b[i].pop();
            sum[bel[l]]+=ask(i);
        }
        rebuild(bel[l]);
        return ;
    }
    del(l,pr[bel[l]]),del(pl[bel[r]],r);
    for(int i=bel[l]+1;i<bel[r];i++){
        while(vis[c[i].top().fi])c[i].pop();
        int p=lower_bound(id+pl[i],id+pr[i]+1,make_pair(c[i].top().fi,0))-id;
        sum[i]=(p<=pr[i]?suf[p]:0)+1ll*(p-pl[i])*c[i].top().se;
    }
}
void work(){
    n=read();q=read();
    for(int i=1;i<=n;i++)a[i]=read();
    for(int l=1,r;l<=n;l=r+1){
        r=min(l+B-1,n);pl[++num]=l,pr[num]=r;
        for(int i=l;i<=r;i++)bel[i]=num,sum[num]+=a[i],b[i].push({0,a[i]});
    	c[num].push({0,0});
        rebuild(num);
    }
    while(q--){
        int op=read();
        if(op==1){
            int l=read()^ans,r=read()^ans,w=read();
            ql[++cnt]=l,qr[cnt]=r;upd(l,r,w,cnt);
        }
        if(op==2){
            int l=read()^ans,r=read()^ans;
            printf("%lld\n",ans=que(l,r));
        }
        if(op==3){
            int x=read()^ans;
            vis[x]=1;del(ql[x],qr[x]);
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