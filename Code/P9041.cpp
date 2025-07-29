#include <algorithm>
#include<bits/stdc++.h>
#include <ctime>
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
const int maxk=50;
const int inf=1e9;
bool mbe;

int n,m,k,ans[maxk+1];
vector<pii> e[maxn];
mt19937 rnd(time(0));
int d[maxn];
vector<int> a[maxn];
queue<int> q;
vector<int> b[maxk];int tim[maxk];
inline int ksm(int a,int b=mod-2){
    int ans=1;
    while(b){
        if(b&1)ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}
void insert(vector<int> x,int t){
    for(int i=0;i<k;i++)if(x[i]){
        if(!tim[i]){b[i]=x,tim[i]=t;break;}
        if(t>tim[i])swap(x,b[i]),swap(t,tim[i]);
        int d=x[i]*ksm(b[i][i])%mod;
        for(int j=0;j<k;j++)(x[j]+=mod-b[i][j]*d%mod)%=mod;
    }
}
void work(){
    n=read();m=read();k=read();
    for(int i=1;i<=m;i++){
        int u=read(),v=read();
        e[u].pb({v,rnd()%(mod-1)+1});
        d[v]++;
    }
    for(int i=1;i<=n;i++)a[i].resize(k);
    for(int i=1;i<=k;i++)a[i][i-1]=1;
    for(int i=1;i<=n;i++)if(!d[i])q.push(i);
    while(!q.empty()){
        int u=q.front();q.pop();
        for(auto[v,w]:e[u]){
            for(int i=0;i<k;i++)(a[v][i]+=a[u][i]*w)%=mod;
            d[v]--;
            if(!d[v])q.push(v);
        }
    }
    for(int i=k+1;i<=n;i++){
        insert(a[i],i);
        vector<int> t;
        t.pb(k);
        for(int j=0;j<k;j++)if(tim[j])t.pb(tim[j]);
        t.pb(i);
        sort(t.begin(),t.end());reverse(t.begin(),t.end());
        for(int j=0;j+1<t.size();j++)ans[j]+=t[j]-t[j+1];
    }
    for(int i=0;i<=k;i++)printf("%lld\n",ans[i]);
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