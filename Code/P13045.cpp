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
const int maxn=110;
const int inf=1e9;

int n;
int a[maxn][maxn];
void upd(int u,int v){
    for(int i=1;i<=2*n;i++){
        for(int j=1;j<=2*n;j++){
            if(u==i||v==j)a[i][j]=-inf;
            else a[i][j]+=((i-u)*(j-v)<0);
        }
    }
}
pii que(){
    pair<int,pii> mx={0,{-4*n,0}};
    for(int i=1;i<=2*n;i++){
        for(int j=1;j<=2*n;j++)mx=max(mx,{a[i][j],{-i,-j}});
    }
    return {-mx.se.fi,-mx.se.se};
}
pii ask(int u,int v){
    cout<<u<<" "<<v<<endl;
    upd(u,v);
    u=read(),v=read();
    upd(u,v);
    return {u,v};
}
void work(){
    memset(a,0,sizeof(a));
    int x=10;
    pii p=ask(x,x);
    for(int i=2;i<=n;i++){
        p=que();
        p=ask(p.fi,p.se);
    }
    read();
}

int T;
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=read();n=read();read();
    while(T--)work();
}