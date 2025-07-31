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
const int maxn=2000010;
const int inf=1e18;
bool mbe;

int n,k;
pii a[maxn],val[maxn];
int id[maxn],p[22];
int calc(int i,int j){return (a[i].fi-a[j].fi)*(a[i].fi-a[j].fi)+(a[i].se-a[j].se)*(a[i].se-a[j].se);}
void work(){
    n=read();k=read();
    for(int i=1;i<=n;i++)a[i]={read(),read()};
    for(int i=1;i<=n;i++)id[i]=0,val[i]={inf,0};
    id[1]=1,p[1]=1;
    for(int j=2;j<=k;j++){
        pii mx={0,0};
        for(int i=1;i<=n;i++)if(!id[i]){
            val[i]=min(val[i],{calc(i,p[j-1]),j-1});
            mx=max(mx,{val[i].fi,i});
        }
        id[mx.se]=j,p[j]=mx.se;
    }
    for(int i=1;i<=n;i++)if(!id[i]){
        val[i]=min(val[i],{calc(i,p[k]),k});
        id[i]=val[i].se;
    }
    for(int i=1;i<=n;i++)printf("%lld ",id[i]);puts("");
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