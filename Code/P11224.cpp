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
const int maxn=510;
const int maxm=maxn*maxn*2;
const int inf=1e9;
bool mbe;

int n,m;
char S[maxn];
bool a[maxn][maxn];
bool pl[maxn][maxn],pr[maxn][maxn],pu[maxn][maxn],pd[maxn][maxn];
int p1[maxn][maxn],p2[maxn][maxn];
map<tuple<int,int,int>,int> id;int idx1,idx2;
tuple<int,int,int> rnk[maxm];
int head[maxm],tot=1;
struct nd{
    int nxt,to,w;
}e[maxm];
void add(int u,int v,int w){
	// cout<<u<<" "<<v<<"\n";
    e[++tot]={head[u],v,w};head[u]=tot;
    e[++tot]={head[v],u,0};head[v]=tot;
}
int s,t,flow;
int dep[maxm],rad[maxm];
queue<int> q;
bool bfs(){
    for(int i=1;i<=t;i++)dep[i]=0,rad[i]=head[i];
    dep[s]=1;q.push(s);
    while(!q.empty()){
        int u=q.front();q.pop();
        for(int i=head[u];i;i=e[i].nxt){
            int v=e[i].to;
            if(e[i].w&&!dep[v]){
                dep[v]=dep[u]+1;
                q.push(v);
            }
        }
    }
    return dep[t];
}
int dfs(int u,int res){
    if(u==t)return res;
    int cnt=0;
    for(int i=rad[u];i;i=e[i].nxt){
        int v=e[i].to;rad[u]=i;
        if(e[i].w&&dep[v]==dep[u]+1){
            int out=dfs(v,min(e[i].w,res));
            cnt+=out,res-=out;
            e[i].w-=out,e[i^1].w+=out;
            if(!res)break;
        }
    }
    return cnt;
}
bool vis[maxm];
void dfs(int u){
    vis[u]=1;
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;if(v==s||v==t||vis[v])continue;
        if(e[i].w)dfs(v);
    }
}
int bk[maxn][maxn];
int ans[maxn][maxn],res;
void col(int u,int v){
	if(ans[u][v])return ;ans[u][v]=res;
    if(a[u][v-1]&&!pd[u][v])col(u,v-1);
    if(a[u][v+1]&&!pd[u][v+1])col(u,v+1);
    if(a[u-1][v]&&!pr[u][v])col(u-1,v);
    if(a[u+1][v]&&!pr[u+1][v])col(u+1,v);
}
void work(){
    n=read();m=read();
    for(int i=1;i<=n;i++){
        scanf("%s",S+1);
        for(int j=1;j<=m;j++)a[i][j]=S[j]=='C';
    }
    n++,m++;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(a[i][j]!=a[i][j-1])pu[i+1][j]=pd[i][j]=1;
            if(a[i][j]!=a[i-1][j])pr[i][j]=pl[i][j+1]=1;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(a[i][j]&&pu[i][j]&&!pd[i][j]&&pl[i][j]&&!pr[i][j])bk[i][j]=1;
            if(a[i][j-1]&&pu[i][j]&&!pd[i][j]&&!pl[i][j]&&pr[i][j])bk[i][j]=2;
            if(a[i-1][j]&&!pu[i][j]&&pd[i][j]&&pl[i][j]&&!pr[i][j])bk[i][j]=3;
            if(a[i-1][j-1]&&!pu[i][j]&&pd[i][j]&&!pl[i][j]&&pr[i][j])bk[i][j]=4;
            // if(bk[i][j])cout<<i<<" "<<j<<" "<<bk[i][j]<<"\n";
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)if(bk[i][j]==1||bk[i][j]==3){
        	int k=j+1;
        	while(k<=m){
        		if(bk[i][k]==2||bk[i][k]==4){
	            	// cout<<i<<" "<<j<<" "<<k<<" a\n";
	                rnk[id[{i,j,k}]=++idx1]={i,j,k};
	                for(int l=j;l<=k;l++)p1[i][l]=idx1;
	                break;
                }
        		if(!pr[i][k]&&!a[i][k])break;
        		k++;
            }
            j=k;
        }
    }
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++)if(bk[j][i]==1||bk[j][i]==2){
        	int k=j+1;
        	while(k<=n){
        		if(bk[k][i]==3||bk[k][i]==4){
	            	// cout<<i<<" "<<j<<" "<<k<<" b\n";
	                rnk[id[{i,j,k}]=idx1+(++idx2)]={i,j,k};
	                for(int l=j;l<=k;l++)p2[l][i]=idx1+idx2;
	                j=k;
	                break;
	            }
        		if(!pd[k][i]&&!a[k][i])break;
        		k++;
        	}
            j=k;
        }
    }
    s=idx1+idx2+1,t=idx1+idx2+2;
    // cout<<idx1<<" "<<idx2<<" "<<s<<" "<<t<<"\n";
    for(int i=1;i<=idx1;i++)add(s,i,1);
    for(int i=1;i<=idx2;i++)add(i+idx1,t,1);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)if(p1[i][j]&&p2[i][j]){
        	// cout<<p1[i][j]<<" "<<p2[i][j]<<"\n";
            add(p1[i][j],p2[i][j],1);
        }
    }
    while(bfs())flow+=dfs(s,inf);
    // cout<<flow<<"\n";
    dfs(s);
    // for(int i=1;i<=t;i++)cout<<vis[i]<<" ";cout<<"\n";
    int num=0;
    for(int i=1;i<=idx1;i++)if(vis[i]){
    	++num;
        auto[p,l,r]=rnk[i];
    	// cout<<i<<" "<<p<<" "<<l<<" "<<r<<" a\n";
        for(int j=l;j<r;j++)pr[p][j]=pl[p][j+1]=1;
        bk[p][l]=bk[p][r]=0;
    }
    for(int i=idx1+1;i<=idx1+idx2;i++)if(!vis[i]){
    	++num;
        auto[p,l,r]=rnk[i];
    	// cout<<i<<" "<<p<<" "<<l<<" "<<r<<" b\n";
        for(int j=l;j<r;j++)pd[j][p]=pu[j+1][p]=1;
        bk[l][p]=bk[r][p]=0;
    }
    // cout<<idx1+idx2-flow<<" "<<num<<"\n";
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)if(bk[i][j]){
        	// cout<<i<<" "<<j<<" "<<bk[i][j]<<"\n";
            if(bk[i][j]&1){
                for(int k=j;!(pd[i][k]&&pu[i][k])&&k<=m;k++)pr[i][k]=pl[i][k+1]=1;
            }
            else{
                for(int k=j;!(pd[i][k]&&pu[i][k])&&k;k--)pl[i][k]=pr[i][k-1]=1;
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)if(a[i][j]&&!ans[i][j])++res,col(i,j);
    }
    for(int i=1;i<n;i++){
        for(int j=1;j<m;j++)printf("%d ",ans[i][j]);puts("");
    }
    // for(int i=1;i<n;i++){
        // for(int j=1;j<m;j++)cout<<setw(3)<<ans[i][j];cout<<"\n";
    // }
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