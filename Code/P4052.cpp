#include<bits/stdc++.h>
// #define int long long
#define mod 10007
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
const int maxn=6010;
const int maxm=110;
const int inf=1e9;
bool mbe;

int n,m,ans;
int to[maxn][26],fail[maxn],ed[maxn],idx;
queue<int> q;
char s[maxn];
int dp[maxm][maxn];
void work(){
    n=read();m=read();
    for(int i=1;i<=n;i++){
        scanf("%s",s+1);int l=strlen(s+1),nd=0;
        for(int j=1;j<=l;j++){
            int c=s[j]-'A';
            if(!to[nd][c])to[nd][c]=++idx;
            nd=to[nd][c];
        }
        ed[nd]=1;
    }
    for(int i=0;i<26;i++)if(to[0][i])q.push(to[0][i]);
    while(!q.empty()){
        int u=q.front();q.pop();
        ed[u]|=ed[fail[u]];
        // cout<<u<<" "<<ed[u]<<"\n";
        for(int i=0;i<26;i++){
            if(to[u][i]){
                fail[to[u][i]]=to[fail[u]][i];
                q.push(to[u][i]);
            }
            else to[u][i]=to[fail[u]][i];
        }
    }
    ans=1;for(int i=1;i<=m;i++)ans=ans*26%mod;
    dp[0][0]=1;
    for(int i=1;i<=m;i++){
        for(int j=0;j<=idx;j++)if(dp[i-1][j]){
            for(int c=0;c<26;c++)if(!ed[to[j][c]])(dp[i][to[j][c]]+=dp[i-1][j])%=mod;
        }
    }
    for(int j=0;j<=idx;j++)(ans+=mod-dp[m][j])%=mod;
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