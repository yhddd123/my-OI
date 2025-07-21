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
const int maxn=110;
const int inf=1e9;

int n,m,a[maxn][maxn];
int b[maxn][maxn],c[maxn][maxn];
int e[maxn][maxn],w[maxn][maxn];
int id[maxn];
int to[maxn<<1];
int st[maxn*maxn],tp;
bool vis[maxn<<1];
int q[maxn*maxn],t;
mt19937 rnd(1);
void work(){
    n=read();m=read();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)a[i][j]=read();
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)e[i][j]=(a[i][j]-1)/m+1+n,w[i][j]=a[i][j];
    }
    int d=m;
    while(d){
    	for(int i=1;i<=2*n;i++)to[i]=0;
        for(int i=1;i<=n;i++)id[i]=i;
        shuffle(id+1,id+n+1,rnd);
        for(int i=1;i<=n;i++){
            int x=id[i],y=0;st[++tp]=x;
            while(!y||to[y]){
                while(!y||y==to[x])y=e[x][rnd()%d+1];
                st[++tp]=y,x=to[y],st[++tp]=x;
            }
            tp--;
            while(tp){
                if(vis[st[tp]]){
                    while(t&&q[t]!=st[tp])vis[q[t]]=0,t--;
                    vis[q[t]]=0,t--;
                }
                vis[st[tp]]=1,q[++t]=st[tp];
                tp--;
            }
            for(int j=1;j<=t;j++)vis[q[j]]=0;
            while(t){
                to[q[t-1]]=q[t],to[q[t]]=q[t-1];
                t-=2;
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=d;j++)if(e[i][j]==to[i]){
                b[i][d]=w[i][j];
                for(int k=j+1;k<=d;k++)e[i][k-1]=e[i][k],w[i][k-1]=w[i][k];
                break;
            }
        }
        // for(int i=1;i<=n;i++)cout<<to[i]<<" ";cout<<endl;
        // cout<<d<<endl;
        d--;
    }
    for(int j=1;j<=m;j++){
        vector<int> val;
        for(int i=1;i<=n;i++)val.pb(b[i][j]);
        sort(val.begin(),val.end());
        for(int i=1;i<=n;i++)c[i][j]=val[i-1];
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)printf("%d ",b[i][j]);puts("");
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)printf("%d ",c[i][j]);puts("");
    }
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}