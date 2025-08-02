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
const int maxn=30;
const int inf=1e9;
bool mbe;

int n,m;
inline int ksm(int a,int b=mod-2){
    int ans=1;
    while(b){
        if(b&1)ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}
int inv2=(mod+1)/2,inv4=ksm(4);
vector<pii> e[maxn];
unordered_map<int,int> f;
int dfs(int s){
    if(!s)return 1;
    if(f.find(s)!=f.end())return f[s];
    int res=0;
    for(auto[ss,p]:e[__lg(s&(-s))]){
        if((s&ss)==ss)(res+=dfs(s^ss)*p)%=mod;
    }
    return f[s]=res;
}
void work(){
    n=read();m=read();
    for(int i=1;i<=m;i++){
        int op=read();
        if(op==0){
            int u=read()-1,v=read()-1+n;
            e[u].pb({(1<<u)|(1<<v),inv2});
        }
        if(op==1){
            int u=read()-1,v=read()-1+n,x=read()-1,y=read()-1+n;
            e[u].pb({(1<<u)|(1<<v),inv2});
            e[x].pb({(1<<x)|(1<<y),inv2});
            if(u!=x&&v!=y){
                e[u].pb({(1<<u)|(1<<v)|(1<<x)|(1<<y),inv4});
                e[x].pb({(1<<u)|(1<<v)|(1<<x)|(1<<y),inv4});
            }
        }
        if(op==2){
            int u=read()-1,v=read()-1+n,x=read()-1,y=read()-1+n;
            e[u].pb({(1<<u)|(1<<v),inv2});
            e[x].pb({(1<<x)|(1<<y),inv2});
            if(u!=x&&v!=y){
                e[u].pb({(1<<u)|(1<<v)|(1<<x)|(1<<y),mod-inv4});
                e[x].pb({(1<<u)|(1<<v)|(1<<x)|(1<<y),mod-inv4});
            }
        }
    }
    int ans=dfs((1<<2*n)-1);
    printf("%lld\n",ans*ksm(2,n)%mod);
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