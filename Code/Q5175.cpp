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
const int maxk=8;
const int inf=1e9;
bool mbe;

int n,m,k,p[maxk];
vector<tuple<int,int,int>> e[maxn];
int dp[1<<maxk][maxn][maxn];
bool vis[maxn];
void work(){
    n=read();m=read();k=read();
    for(int i=0;i<k;i++)p[i]=read();
    for(int i=1;i<=m;i++){
        int u=read(),v=read(),a=read(),b=read();
        e[v].pb({u,a,b});
    }
    memset(dp,0x3f,sizeof(dp));
    for(int i=0;i<k;i++)dp[1<<i][0][p[i]]=0;
    for(int i=1;i<=n;i++)dp[0][0][i]=0;
    for(int s=0;s<(1<<k);s++){
	    for(int i=0;i<=m;i++){
            // for(int j=0;j<=i;j++){
                // for(int t=(s-1)&s;t;t=(t-1)&s){
                    // for(int u=1;u<=n;u++)dp[s][i][u]=min(dp[s][i][u],max(dp[t][j][u],dp[s^t][i-j][u]));
                // }
            // }
            if(i){
	        	for(int u=1;u<=n;u++)dp[s][i][u]=min(dp[s][i][u],dp[s][i-1][u]);
                for(int v=1;v<=n;v++){
                    for(auto[u,a,b]:e[v])dp[s][i][u]=min(dp[s][i][u],dp[s][i-1][v]+b);
                }
            }
            priority_queue<pii> q;
            for(int v=1;v<=n;v++)q.push({-dp[s][i][v],v}),vis[v]=0;
            while(!q.empty()){
                int v=q.top().se;q.pop();
                if(vis[v])continue;vis[v]=1;
                for(auto[u,a,b]:e[v]){
                    if(dp[s][i][u]>dp[s][i][v]+a){
                        dp[s][i][u]=dp[s][i][v]+a;
                        q.push({-dp[s][i][u],u});
                    }
                }
            }
            // cout<<i<<" "<<s<<"\n";
            // for(int u=1;u<=n;u++){
            	// if(dp[s][i][u]>inf)cout<<"inf ";
            	// else cout<<dp[s][i][u]<<" ";
        	// }cout<<"\n";
        }
        int T=s^((1<<k)-1);
        for(int t=T;t;t=(t-1)&T)if(t<=s){
        	for(int u=1;u<=n;u++){
	        	for(int i=0,j=0;i<=m;i++){
	        		while(j<=m&&dp[t][j][u]>dp[s][i][u])j++;
	        		if(i+j<=m)dp[s|t][i+j][u]=min(dp[s|t][i+j][u],dp[s][i][u]);
	        	}
	        	for(int i=0,j=0;i<=m;i++){
	        		while(j<=m&&dp[s][j][u]>dp[t][i][u])j++;
	        		if(i+j<=m)dp[s|t][i+j][u]=min(dp[s|t][i+j][u],dp[t][i][u]);
	        	}
        	}
        }
    }
    for(int i=0;i<=m;i++)printf("%lld ",dp[(1<<k)-1][i][1]);
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