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
const int maxn=200010;
const int inf=2e9+1;
bool mbe;

int n;
int x[maxn],y[maxn],op[maxn];
bool vis[maxn];
struct nd{
    int t,i,j;
    bool operator<(const nd&tmp)const{return t>tmp.t;}
};
struct node{
	pii p;
    priority_queue<nd> q;
    void clr(){
        while(q.size()){
            auto[t,u,v]=q.top();
            if(vis[u]||vis[v])q.pop();
            else break;
        }
    }
    bool empty(){clr();return q.empty();}
    void push(nd u){if(vis[u.i]||vis[u.j])return ;q.push(u);}
    nd top(){clr();return q.top();}
    void pop(){clr();q.pop();}
    pii val[maxn];
    int id[maxn],m,rnk[maxn];
    int pre[maxn],nxt[maxn];
    void ins(int _id,pii p){val[_id]=p;id[++m]=_id;}
    void upd(int u,int v){
        if(!u||v>m)return ;
        u=id[u],v=id[v];
        if(op[u]!=p.fi||op[v]!=p.se)return ;
        q.push({abs(x[u]-x[v])+abs(y[u]-y[v]),u,v});
    }
    void init(){
        sort(id+1,id+m+1,[&](int u,int v){return val[u]<val[v];});
        for(int i=1;i<=m;i++)rnk[id[i]]=i;nxt[m+1]=m+1;
        for(int i=1,j=1;i<=m;i=j+1){
            j=i;while(j<=m&&val[id[j+1]].fi==val[id[i]].fi)j++;
            pre[i]=0,nxt[j]=m+1;
            for(int k=i;k<j;k++)nxt[k]=k+1,pre[k+1]=k;
        }
        for(int i=1;i<=m;i++)upd(i,nxt[i]);
    }
    void del(int u){
        u=rnk[u];
        nxt[pre[u]]=nxt[u],pre[nxt[u]]=pre[u];
        upd(pre[u],nxt[u]);
    }
}a[6];
void work(){
    n=read();
    for(int i=1;i<=n;i++){
        x[i]=read(),y[i]=read();
        char c[3];scanf("%s",c);
        if(c[0]=='N'){
            op[i]=0;
            a[0].ins(i,{x[i],y[i]});
            a[2].ins(i,{x[i]-y[i],x[i]});
            a[3].ins(i,{x[i]+y[i],x[i]});
        }
        if(c[0]=='S'){
            op[i]=1;
            a[0].ins(i,{x[i],y[i]});
            a[4].ins(i,{x[i]-y[i],x[i]});
            a[5].ins(i,{x[i]+y[i],x[i]});
        }
        if(c[0]=='E'){
            op[i]=2;
            a[1].ins(i,{y[i],x[i]});
            a[2].ins(i,{x[i]-y[i],x[i]});
            a[5].ins(i,{x[i]+y[i],x[i]});
        }
        if(c[0]=='W'){
            op[i]=3;
            a[1].ins(i,{y[i],x[i]});
            a[3].ins(i,{x[i]+y[i],x[i]});
            a[4].ins(i,{x[i]-y[i],x[i]});
        }
    }
    a[0].p={1,0},a[1].p={2,3},a[2].p={2,0},a[3].p={0,3},a[4].p={1,3},a[5].p={2,1};
    for(int i=0;i<6;i++)a[i].init();
    while(1){
        int mn=inf;for(int i=0;i<6;i++)if(!a[i].empty())mn=min(mn,a[i].top().t);
        if(mn==inf)break;
        vector<int> id;
        for(int i=0;i<6;i++){
            while(!a[i].empty()){
                auto[t,u,v]=a[i].top();
                if(t!=mn)break;
                id.pb(u),id.pb(v),a[i].pop();
            }
        }
        sort(id.begin(),id.end());id.erase(unique(id.begin(),id.end()),id.end());
        // cout<<mn<<"\n";
        // for(int u:id)cout<<u<<" ";cout<<"\n";
        for(int i:id)vis[i]=1;
        for(int i:id){
            if(op[i]==0)a[0].del(i),a[2].del(i),a[3].del(i);
            if(op[i]==1)a[0].del(i),a[4].del(i),a[5].del(i);
            if(op[i]==2)a[1].del(i),a[2].del(i),a[5].del(i);
            if(op[i]==3)a[1].del(i),a[3].del(i),a[4].del(i);
        }
    }
    vector<int> ans;
    for(int i=1;i<=n;i++)if(!vis[i])ans.pb(i);
    // printf("%d\n",ans.size());
    for(int u:ans)printf("%d\n",u);
}

bool med;
int T;
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    T=1;
    while(T--)work();
}