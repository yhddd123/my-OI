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

int n,m,ans;
vector<int> pos[maxn];
int lsh[maxn<<1],len;
int vk[maxn<<1],vb[maxn<<1];
void upd(int l,int r,int k,int b){
    if(l>r)return ;
    l=lower_bound(lsh+1,lsh+len+1,l)-lsh,r=lower_bound(lsh+1,lsh+len+1,r+1)-lsh;
    vk[l]+=k,vk[r]-=k,vb[l]+=b,vb[r]-=b;
}
void work(){
    n=read();m=read();ans=inf;
    for(int i=1;i<=m;i++)pos[i].clear();
    for(int i=1;i<=n;i++){
        int x=read(),k=read();
        for(int j=1;j<=k;j++)pos[read()].pb(x);
    }
    for(int i=1;i<=m;i++)sort(pos[i].begin(),pos[i].end());
    len=0;lsh[++len]=1,lsh[++len]=1000000000;
    for(int i=1;i<=m;i++){
        for(int j=0;j<pos[i].size();j++)lsh[++len]=pos[i][j]+1;
        for(int j=0;j+1<pos[i].size();j++)lsh[++len]=(pos[i][j]+pos[i][j+1])/2+1;
    }
    sort(lsh+1,lsh+len+1),len=unique(lsh+1,lsh+len+1)-lsh-1;
    for(int i=1;i<=len;i++)vk[i]=vb[i]=0;
    for(int i=1;i<=m;i++){
        upd(1,pos[i].front(),-1,pos[i].front());
        for(int j=0;j+1<pos[i].size();j++){
            upd(pos[i][j]+1,(pos[i][j]+pos[i][j+1])/2,1,-pos[i][j]);
            upd((pos[i][j]+pos[i][j+1])/2+1,pos[i][j+1],-1,pos[i][j+1]);
        }
        upd(pos[i].back()+1,inf,1,-pos[i].back());
    }
    for(int i=1,k=0,b=0;i<len;i++){
        k+=vk[i],b+=vb[i];
        ans=min({ans,k*lsh[i]+b,k*(lsh[i+1]-1)+b});
    }
    printf("%lld\n",ans);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=read();
    while(T--)work();
}