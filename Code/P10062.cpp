#include<bits/stdc++.h>
#define int short
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
const int maxn=510;

int n,p,q,a[maxn][maxn];
int t[maxn];
mt19937 rnd(1);
int id[maxn];
int st[maxn*maxn],tp;
int to[maxn<<1];
bool vis[maxn<<1];
int que[maxn*maxn],tl;
vector<vector<int>> color(vector<vector<int>> e){
    vector<vector<int>> ans;
    int n=e.size()-1,d=e[1].size();
    for(int i=1;i<=n;i++)id[i]=i;
    for(int i=1;i<=n;i++){
        for(int j=0;j<d;j++)e[i][j]+=n;
    }
    while(d){
        vector<int> res;
        shuffle(id+1,id+n+1,rnd);
        for(int i=1;i<=2*n;i++)to[i]=0;
        for(int i=1;i<=n;i++){
            int x=id[i],y=0;st[++tp]=x;
            while(!y||to[y]){
                while(!y||y==to[x])y=e[x][rnd()%d];
                st[++tp]=y,x=to[y],st[++tp]=x;
            }
            tp--;
            while(tp){
                if(vis[st[tp]]){
                    while(tl&&que[tl]!=st[tp])vis[que[tl]]=0,tl--;
                    vis[que[tl]]=0,tl--;
                }
                vis[st[tp]]=1,que[++tl]=st[tp];
                tp--;
            }
            for(int j=1;j<=tl;j++)vis[que[j]]=0;
            // for(int j=1;j<=t;j++)cout<<q[j]<<" ";cout<<"\n";
            while(tl){
                to[que[tl-1]]=que[tl],to[que[tl]]=que[tl-1];
                tl-=2;
            }
        }
        for(int i=1;i<=n;i++){
        	res.pb(to[i]-n);
        	for(int j=0;j<d;j++)if(e[i][j]==to[i]){swap(e[i][j],e[i][d-1]);break;}
        }
    	ans.pb(res);
        d--;
    }
    return ans;
}
void work(){
    n=read();p=read();q=read();
    for(int i=1;i<=n;i++)t[i]=0;
    for(int i=1;i<=p;i++){
        for(int j=1;j<=q;j++)a[i][j]=read(),t[a[i][j]]++;
    }
    for(int i=1;i<=n;i++)if(t[i]+2*n-p-q<n){puts("No");return ;}
    puts("Yes");
    if(q<n){
        vector<vector<int>> e(n+1);
        for(int i=1;i<=p;i++){
            for(int j=1;j<=n;j++)t[j]=0;
            for(int j=1;j<=q;j++)t[a[i][j]]=1;
            for(int j=1;j<=n;j++)if(!t[j])e[i].pb(j);
        }
        for(int j=1;j<=n;j++)t[j]=n-q;
        for(int i=1;i<=p;i++){
            for(int j:e[i])t[j]--;
        }
        for(int j=1;j<=n;j++)id[j]=j;
        for(int i=p+1;i<=n;i++){
            sort(id+1,id+n+1,[&](int u,int v){return t[u]>t[v];});
            for(int j=1;j<=n-q;j++)t[id[j]]--,e[i].pb(id[j]);
        }
        auto ans=color(e);
        for(int i=0;i<n-q;i++){
            for(int j=1;j<=p;j++)a[j][n-i]=ans[i][j-1];
        }
    }
    if(p<n){
        vector<vector<int>> e(n+1);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++)t[j]=0;
            for(int j=1;j<=p;j++)t[a[j][i]]=1;
            for(int j=1;j<=n;j++)if(!t[j])e[i].pb(j);
        }
        auto ans=color(e);
        for(int i=0;i<n-p;i++){
            for(int j=1;j<=n;j++)a[n-i][j]=ans[i][j-1];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)printf("%d ",a[i][j]);puts("");
    }
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen("A.out","w",stdout);
    
    T=read();
    while(T--)work();
}