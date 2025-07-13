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
const int maxn=500010;
const int inf=1e9;

int n,m;
int head[2][maxn],tot[2];
struct nd{
    int nxt,to;
}e[2][maxn<<2];
int d[2][maxn];
void add(int u,int v,int op){e[op][++tot[op]]={head[op][u],v},head[op][u]=tot[op];d[op][v]++;}
int s,t;
int dis[2][maxn],rnk[2][maxn];
void bfs(int op){
    queue<int> q;
    if(!op)q.push(s);
    else q.push(t);
    for(int ii=1;ii<=t;ii++){
        int u=q.front();q.pop();rnk[op][ii]=u;
        for(int i=head[op][u];i;i=e[op][i].nxt){
            int v=e[op][i].to;
            if((--d[op][v])==0)q.push(v);
        }
    }
    for(int ii=t;ii;ii--){
        int u=rnk[op][ii];
        for(int i=head[op][u];i;i=e[op][i].nxt){
            int v=e[op][i].to;
            dis[op^1][u]=max(dis[op^1][u],dis[op^1][v]+1);
        }
    }
}
priority_queue<int> q1,q2;
void add(int w){q1.push(w);}
void del(int w){q2.push(w);}
int que(){
    while(q1.size()&&q2.size()&&q1.top()==q2.top())q1.pop(),q2.pop();
    if(!q1.size())return inf;
    return q1.top();
}
void work(){
    n=read();m=read();
    for(int i=1;i<=m;i++){
        int u=read(),v=read();
        add(u,v,0),add(v,u,1);
    }
    s=n+1,t=n+2;
    for(int i=1;i<=n;i++)add(s,i,0),add(i,s,1),add(i,t,0),add(t,i,1);
    bfs(0),bfs(1);
    // for(int i=1;i<=t;i++)cout<<rnk[0][i]<<" ";cout<<"\n";
    // for(int i=1;i<=n;i++)cout<<dis[0][i]<<" "<<dis[1][i]<<"\n";
    pii mn={inf,0};
    for(int ii=2;ii<t;ii++){
        int u=rnk[0][ii-1];
        for(int i=head[0][u];i;i=e[0][i].nxt){
            int v=e[0][i].to;
            // cout<<u<<" "<<v<<" "<<dis[0][u]+dis[1][v]+1<<"\n";
            add(dis[0][u]+dis[1][v]+1);
        }
        u=rnk[0][ii];
        for(int i=head[1][u];i;i=e[1][i].nxt){
            int v=e[1][i].to;
            del(dis[0][v]+dis[1][u]+1);
        }
        // cout<<ii<<" "<<que()<<" "<<u<<"\n";
        mn=min(mn,{que(),u});
    }
    printf("%d %d",mn.se,mn.fi-2);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}