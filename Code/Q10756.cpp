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
const int maxn=25;
const int inf=1e9;

int n,ans;
int a[maxn],b[maxn];
vector<int> e[maxn];
bool vis[maxn];
int id[maxn];
int fac[maxn];
void work(){
    n=read();
    for(int i=1;i<=n;i++)a[i]=read();
    for(int i=1;i<=n;i++)b[i]=read();
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            int v=read();
            if(v!=a[i]&&v!=b[j]){printf("0\n");return;}
            if(a[i]!=b[j]){
                if(v==b[j])e[i].pb(j);
            }
        }
    }
    for(int s=0;s<(1<<n);s++){
        for(int i=0;i<n;i++)if(s&(1<<i))e[i+1].pb(i+1);
        for(int i=1;i<=n;i++)vis[i]=0,id[i]=i;
        sort(id+1,id+n+1,[&](int x,int y){return e[x].size()<e[y].size();});
        bool fl=1;for(int i=1;i<=n;i++){
            for(int j:e[id[i]])vis[j]=0;
            for(int j=1;j<=n;j++)if(vis[j]){fl=0;break;}
            for(int j:e[id[i]])vis[j]=1;
        }
        // cout<<s<<" "<<fl<<" s\n";
        if(fl){
            int res=1;for(int i=1,num=0;i<=n+1;i++){
                if(i<=n&&e[id[i]].size()==e[id[i-1]].size())num++;
                else res=res*fac[num]%mod,num=1;
            }
            for(int i=1;i<=n;i++)res=res*fac[e[id[i]].size()-e[id[i-1]].size()]%mod;res=res*fac[n-e[id[n]].size()]%mod;
            (ans+=res)%=mod;
            // cout<<s<<" "<<res<<"\n";
            // for(int i=1;i<=n;i++)cout<<e[i].size()<<" "; cout<<"\n";
        }
        for(int i=0;i<n;i++)if(s&(1<<i))e[i+1].pop_back();
    }
    printf("%lld\n",ans);
}

int T;
signed main(){
    freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}