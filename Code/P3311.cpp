#include<bits/stdc++.h>
#define int long long
#define mod 1000000007ll
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
const int maxn=1500;
const int inf=1e9;
bool mbe;

int n,m,ans;
int to[maxn][10],fail[maxn],ed[maxn],idx;
queue<int> q;
char s[maxn];
int dp[maxn][maxn];
char ss[maxn];
void work(){
	scanf("%s",ss+1);n=strlen(ss+1);m=read();
    for(int i=1;i<=m;i++){
        scanf("%s",s+1);int l=strlen(s+1),nd=0;
        for(int j=1;j<=l;j++){
            int c=s[j]-'0';
            if(!to[nd][c])to[nd][c]=++idx;
            nd=to[nd][c];
        }
        ed[nd]=1;
    }
    for(int i=0;i<10;i++)if(to[0][i])q.push(to[0][i]);
    while(!q.empty()){
        int u=q.front();q.pop();
        ed[u]|=ed[fail[u]];
        // cout<<u<<" "<<ed[u]<<"\n";
        for(int i=0;i<10;i++){
            if(to[u][i]){
                fail[to[u][i]]=to[fail[u]][i];
                q.push(to[u][i]);
            }
            else to[u][i]=to[fail[u]][i];
        }
    }
    for(int j=0;j<=idx;j++)if(!ed[j])dp[0][j]=1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=idx;j++)if(!ed[j]){
            for(int c=0;c<10;c++)if(!ed[to[j][c]])(dp[i][j]+=dp[i-1][to[j][c]])%=mod;
        }
    }
    for(int i=1;i<n;i++){
    	for(int c=1;c<10;c++)(ans+=dp[n-i-1][to[0][c]])%=mod;
    }
    for(int i=1,nd=0;i<=n;i++){
    	int c=ss[i]-'0';
    	for(int j=(i==1?1:0);j<c;j++){
    		(ans+=dp[n-i][to[nd][j]])%=mod;
    		// cout<<i<<" "<<j<<" "<<to[nd][j]<<" "<<ans<<"\n";
    	}
    	nd=to[nd][c];
    	if(ed[nd])break;
    	if(i==n)ans++;
    }
    printf("%d\n",ans);
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