#include<bits/stdc++.h>
// #define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
const int maxn=2010;
const int maxm=32010;
const int inf=1e9;

int n,m,ans;
char sl[maxn],sr[maxn];
int dp[maxn][maxm],sum[maxm][maxn];
bool vis[maxn][maxm];
int to[maxm][10],fail[maxm],idx=1;
queue<int> q;
void dfs(int u,int d,bool dw,bool up){
    // cout<<u<<" "<<d<<" "<<dw<<" "<<up<<"\n";
    if((!dw&&!up)||d==m+1){sum[u][m-d+1]++;return ;}
    for(int i=(dw?sl[d]-'0':0);i<=(up?sr[d]-'0':9);i++){
        if(u==1&&!i)dfs(1,d+1,dw&(i==sl[d]-'0'),up&(i==sr[d]-'0'));
        else{
            if(!to[u][i])to[u][i]=++idx;
            dfs(to[u][i],d+1,dw&(i==sl[d]-'0'),up&(i==sr[d]-'0'));
        }
    }
}
void work(){
    scanf("%s%s%d",sl+1,sr+1,&n);m=strlen(sr+1);
    int l=strlen(sl+1);for(int i=m,j=l;j;i--,j--)sl[i]=sl[j];
    for(int i=1;i<=m-l;i++)sl[i]='0';
    dfs(1,1,1,1);
    for(int i=1;i<=idx;i++){
        for(int j=1;j<=n;j++)sum[i][j]+=sum[i][j-1];
    }
	for(int i=0;i<10;i++)to[0][i]=1;q.push(1);
    while(!q.empty()){
        int u=q.front();q.pop();
        for(int i=0;i<10;i++){
            if(to[u][i]){
                fail[to[u][i]]=to[fail[u]][i];q.push(to[u][i]);
                for(int j=0;j<=n;j++)sum[to[u][i]][j]+=sum[to[fail[u]][i]][j];
            }
            else to[u][i]=to[fail[u]][i];
        }
    }
    memset(dp,-0x3f,sizeof(dp));
    dp[0][1]=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=idx;j++)if(dp[i-1][j]>=0){
            for(int c=0;c<10;c++){
                dp[i][to[j][c]]=max(dp[i][to[j][c]],dp[i-1][j]+sum[to[j][c]][n-i]);
            }
        }
    }
    for(int j=1;j<=idx;j++)ans=max(ans,dp[n][j]);
    printf("%d\n",ans);
    for(int j=1;j<=idx;j++)if(dp[n][j]==ans)vis[n][j]=1;
    for(int i=n;~i;i--){
        for(int j=1;j<=idx;j++){
            for(int c=0;c<10;c++)if(vis[i][to[j][c]]&&dp[i][to[j][c]]==dp[i-1][j]+sum[to[j][c]][n-i])vis[i-1][j]=1;
        }
    }
    for(int i=1,j=1;i<=n;i++){
        assert(vis[i-1][j]);
        for(int c=0;c<10;c++)if(vis[i][to[j][c]]&&dp[i][to[j][c]]==dp[i-1][j]+sum[to[j][c]][n-i]){
            putchar(c+'0');
            j=to[j][c];
            break;
        }
    }
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}