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
const int maxn=200010;
const int inf=1e9;

int n,k,a[maxn],ans=inf;
vector<int> pos[maxn];
int lu[maxn][18],ld[maxn][18],ru[maxn][18],rd[maxn][18];
int getlu(int p,int lim){
    int ans=0;for(int i=17;~i;i--)if(lu[p][i]>=lim)p=lu[p][i],ans|=1<<i;
    return ans;
}
int getld(int p,int lim){
    int ans=0;for(int i=17;~i;i--)if(ld[p][i]>=lim)p=ld[p][i],ans|=1<<i;
    return ans;
}
int getru(int p,int lim){
    int ans=0;for(int i=17;~i;i--)if(ru[p][i]<=lim)p=ru[p][i],ans|=1<<i;
    return ans;
}
int getrd(int p,int lim){
    int ans=0;for(int i=17;~i;i--)if(rd[p][i]<=lim)p=rd[p][i],ans|=1<<i;
    return ans;
}
int calcl(int u,int v){
    if(getld(u,1)+getlu(v,1)<k)return -inf;
    int l=1,r=min(u,v),res=l;
    while(l<=r){
        int mid=l+r>>1;
        if(getld(u,mid)+getlu(v,mid)<k)r=mid-1;
        else l=mid+1,res=mid;
    }
    return res;
}
int calcr(int u,int v){
    if(getrd(u,n)+getru(v,n)<k)return inf;
    int l=max(u,v),r=n,res=r;
    while(l<=r){
        int mid=l+r>>1;
        if(getrd(u,mid)+getru(v,mid)<k)l=mid+1;
        else res=mid,r=mid-1;
    }
    return res;
}
void work(){
    n=read();k=read();
    for(int i=1;i<=n;i++)a[i]=read();
    if(k&1){puts("-1");return ;}
    for(int i=0;i<=n+1;i++)pos[i].pb(0);
    for(int i=1;i<=n;i++)pos[a[i]].pb(i);
    for(int i=0;i<=n+1;i++)pos[i].pb(n+1);
    for(int j=0;j<18;j++)ru[n+1][j]=rd[n+1][j]=n+1;
    for(int i=1;i<=n;i++){
        lu[i][0]=*--upper_bound(pos[a[i]+1].begin(),pos[a[i]+1].end(),i);
        ld[i][0]=*--upper_bound(pos[a[i]-1].begin(),pos[a[i]-1].end(),i);
        ru[i][0]=*lower_bound(pos[a[i]+1].begin(),pos[a[i]+1].end(),i);
        rd[i][0]=*lower_bound(pos[a[i]-1].begin(),pos[a[i]-1].end(),i);
    }
    for(int j=1;j<18;j++){
        for(int i=1;i<=n;i++){
            lu[i][j]=lu[lu[i][j-1]][j-1];
            ld[i][j]=ld[ld[i][j-1]][j-1];
            ru[i][j]=ru[ru[i][j-1]][j-1];
            rd[i][j]=rd[rd[i][j-1]][j-1];
        }
    }
    k=k/2-1;
    for(int i=1;i<=n;i++){
        for(int j=1;j+2<pos[i].size();j++){
            int u=pos[i][j],v=pos[i][j+1];
            int pl=calcl(u,u),pr=calcr(v,v);
            ans=min({ans,calcr(v,u)-pl,pr-calcl(v,u),calcr(u,v)-pl,pr-calcl(u,v)});
        }
    }
    if(ans>n)ans=-1;
    printf("%d\n",ans);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}