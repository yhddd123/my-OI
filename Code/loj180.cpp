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
const int maxn=2000010;
const int inf=1e9;

int n,d,a[maxn];
vector<int> e[maxn];
mt19937 rnd(time(0));
int to[maxn<<1];
int st[maxn<<1],tp;
bool vis[maxn<<1];
int q[maxn<<1],t;
void work(){
    n=read();d=read();
    for(int i=1;i<=n;i++){
        e[i].resize(d);
        for(int j=0;j<d;j++)e[i][j]=read()+n;
    }
    for(int i=1;i<=n;i++)a[i]=i;
    shuffle(a+1,a+n+1,rnd);
    for(int i=1;i<=n;i++){
        int x=a[i],y=0;st[++tp]=x;
        while(!y||to[y]){
            while(!y||y==to[x])y=e[x][rnd()%d];
            st[++tp]=y,x=to[y],st[++tp]=x;
        }
        // for(int j=1;j<=tp;j++)cout<<st[j]<<" ";cout<<"\n";
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
        // for(int j=1;j<=t;j++)cout<<q[j]<<" ";cout<<"\n";
        while(t){
            to[q[t-1]]=q[t],to[q[t]]=q[t-1];
            t-=2;
        }
    }
    for(int i=1;i<=n;i++)printf("%d ",to[i]-n);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}