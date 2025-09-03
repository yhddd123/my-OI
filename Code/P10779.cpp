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
const int maxn=50010;
const int inf=1e9;

int n,m;
struct node{
    int v[2][2];
    node(int a=0,int b=0,int c=0,int d=-maxn){v[0][0]=a,v[0][1]=b,v[1][0]=c,v[1][1]=d;}
};
node operator+(node u,node v){return node(u.v[0][0]+v.v[0][0],u.v[0][1]+v.v[0][1],u.v[1][0]+v.v[1][0],u.v[1][1]+v.v[1][1]);}
map<int,node> f[maxn];
int g[maxn][2];
int d[maxn];
void add(int u,int v,node w){
    if(f[u].find(v)==f[u].end())f[u][v]=f[v][u]=node(),d[u]++,d[v]++;
    f[u][v]=f[u][v]+w;
    swap(w.v[0][1],w.v[1][0]);
    f[v][u]=f[v][u]+w;
}
queue<int> q;
void work(){
    n=read();m=read();
    for(int i=1;i<=n;i++)g[i][0]=0,g[i][1]=1;
    for(int i=1;i<=m;i++){
        int u=read(),v=read();
        add(u,v,node());
    }
    for(int i=1;i<=n;i++)if(d[i]<=2)q.push(i);
    int rt=0;
    while(!q.empty()){
        int u=q.front();q.pop();
        if(!d[u])continue;
        else if(d[u]==1){
            int v=(*f[u].begin()).fi;
            for(int i=0;i<2;i++){
                int mx=0;for(int j=0;j<2;j++)mx=max(mx,g[u][j]+f[u][v].v[j][i]);
                g[v][i]+=mx;
            }
            d[u]--,d[v]--,f[u].erase(v),f[v].erase(u);
            // cout<<v<<" "<<u<<" "<<g[v][0]<<" "<<g[v][1]<<"\n";
            if(d[v]<=2)q.push(v);
            rt=v;
        }
        else if(d[u]==2){
            int v1=(*f[u].begin()).fi,v2=(*--f[u].end()).fi;
            node w=node(0,0,0,0);
            for(int i=0;i<2;i++){
                for(int j=0;j<2;j++){
                    int mx=0;for(int k=0;k<2;k++)mx=max(mx,f[u][v1].v[k][i]+f[u][v2].v[k][j]+g[u][k]);
                    w.v[i][j]=mx;
                }
            }
            add(v1,v2,w);
            d[u]-=2,d[v1]--,d[v2]--;f[u].erase(v1),f[u].erase(v2),f[v1].erase(u),f[v2].erase(u);
            if(d[v1]<=2)q.push(v1);
            if(d[v2]<=2)q.push(v2);
            // cout<<u<<" "<<v1<<" "<<v2<<" "<<f[v1][v2].v[0][0]<<" "<<f[v1][v2].v[0][1]<<" "<<f[v1][v2].v[1][0]<<" "<<f[v1][v2].v[1][1]<<"\n";
        }
    }
    // cout<<rt<<"\n";
    printf("%d\n",max(g[rt][0],g[rt][1]));
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}