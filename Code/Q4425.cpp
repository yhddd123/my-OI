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
const int inf=1e9;
bool mbe;

int n,a[2][maxn],b[2][maxn],ans;
int to[maxn];
#define lb(x) (x&(-x))
int tree[maxn];
void upd(int x,int w){
    while(x<=n)tree[x]+=w,x+=lb(x);
}
int que(int x){
    int res=0;
    while(x)res+=tree[x],x-=lb(x);
    return res;
}
void work(){
    n=read();ans=0;
    for(int i=1;i<=n;i++)a[0][i]=read();
    for(int i=1;i<=n;i++)a[1][i]=read();
    for(int i=1;i<=n;i++)b[0][i]=read();
    for(int i=1;i<=n;i++)b[1][i]=read();
    for(int i=2;i<=n;i+=2)swap(a[0][i],a[1][i]),swap(b[0][i],b[1][i]);
    map<pii,vector<int>> mp1,mp2;
    for(int i=1;i<=n;i++)mp1[{a[0][i],a[1][i]}].pb(i);
    for(int i=1;i<=n;i++)mp2[{b[0][i],b[1][i]}].pb(i);
    for(auto[p,a]:mp1){
        vector<int> b=mp2[p];
        if(a.size()!=b.size()){puts("-1");return ;}
        while(a.size()&&b.size())to[a.back()]=b.back(),a.pop_back(),b.pop_back();
    }
    for(int i=1;i<=n;i++)tree[i]=0;
    for(int i=1;i<=n;i++){
        ans+=i-1-que(to[i]);
        upd(to[i],1);
    }
    printf("%lld\n",ans);

}

bool med;
int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen("A.out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    T=read();
    while(T--)work();
}