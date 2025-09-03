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
const int maxn=3010;
const int inf=1e9;

int h,w,n,k,ans;
pii a[maxn];
int id[maxn],t[maxn],tmp[maxn];
int pre[maxn],nxt[maxn];
int f[maxn];
void work(){
    h=read(),w=read(),n=read(),k=read();
    for(int i=1;i<=n;i++){
        int u=read(),v=read();
        a[i]={u,v};
    }
    sort(a+1,a+n+1,[&](pii u,pii v){return u.fi>v.fi;});
    a[n+1]={0,w+1};
    for(int i=1;i<=h;i++){
    	for(int j=1;j<=w;j++)t[j]=0;
        for(int j=1;j<=n&&a[j].fi>=i;j++)t[a[j].se]++;
        for(int j=1;j<=w;j++)t[j]+=t[j-1];int num=t[w];id[num+1]=n+1;
        for(int j=1;j<=n&&a[j].fi>=i;j++)id[t[a[j].se]--]=j;
        for(int j=1;j<=num;j++)pre[id[j]]=id[j-1],nxt[id[j]]=id[j+1];
        pre[0]=0,nxt[0]=id[1],pre[n+1]=id[num],nxt[n+1]=n+1;
        int res=0;for(int j=1;j<=num+1;j++)f[id[j]]=(a[id[j]].se-a[id[j-1]].se)*(w-a[id[min(num+1,j+k-1)]].se+1),res+=f[id[j]];
        // cout<<i<<" "<<res<<"\n";
        // for(int j=1;j<=num+1;j++)cout<<f[id[j]]<<" ";cout<<"\n";
        ans+=res;
        for(int j=h-1,jj=1;j>=i;j--){
            while(a[jj].fi==j+1){
                nxt[pre[jj]]=nxt[jj],pre[nxt[jj]]=pre[jj];res-=f[jj];
                for(int l=0,p=pre[jj];l<=k;l++,p=nxt[p])tmp[k+l]=p;
                for(int l=0,p=pre[jj];l<=k;l++,p=pre[p])tmp[k-l]=p;
                for(int l=1;l<=k+1;l++)res-=f[tmp[l]],f[tmp[l]]=(a[tmp[l]].se-a[tmp[l-1]].se)*(w-a[tmp[l+k-1]].se+1),res+=f[tmp[l]];
                jj++;
            }
            ans+=res;
        }
    }
    printf("%lld\n",ans);
}

int T;
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}