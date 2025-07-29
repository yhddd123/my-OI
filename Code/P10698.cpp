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
const int maxn=100010;
const int maxk=50;
const int inf=1e9;
bool mbe;

int n,m,k,ans[maxn];
vector<int> e[maxn];
mt19937 rnd(time(0));
int d[maxn];
vector<int> a[maxn];
queue<int> q;
inline int ksm(int a,int b=mod-2){
    int ans=1;
    while(b){
        if(b&1)ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}
struct bas{
    int cnt;
    vector<int> b[maxk];
    void insert(vector<int> x){
        for(int i=0;i<k;i++)if(x[i]){
            if(!b[i].size()){cnt++;b[i]=x;break;}
            int d=x[i]*ksm(b[i][i])%mod;
            for(int j=0;j<k;j++)(x[j]+=mod-b[i][j]*d%mod)%=mod;
        }
    }
}b[maxn];
void work(){
    n=read();m=read();k=read();
    for(int i=1;i<=m;i++){
        int u=read(),v=read();
        e[u].pb(v);d[v]++;
    }
    for(int i=1;i<=k;i++)e[0].pb(1),d[1]++;
    for(int i=0;i<k;i++){
        vector<int> x(k);x[i]=1;
        b[0].insert(x);
    }
    for(int i=0;i<=n;i++)if(!d[i])q.push(i);
    while(!q.empty()){
        int u=q.front();q.pop();
        // cout<<u<<" "<<b[u].cnt<<endl;
        for(int v:e[u]){
            vector<int> x(k);
            for(int i=0;i<k;i++)if(b[u].b[i].size()){
                int w=rnd()%(mod-1)+1;
                for(int j=i;j<k;j++)(x[j]+=b[u].b[i][j]*w)%=mod;
            }
            b[v].insert(x);
            // cout<<u<<" "<<v<<" "<<b[v].cnt<<"\n";
            d[v]--;
            if(!d[v])q.push(v);
        }
    }
    for(int i=2;i<=n;i++)printf("%lld ",b[i].cnt);
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