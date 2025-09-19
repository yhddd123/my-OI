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
const int maxn=5010;
const int inf=1e9;
bool mbe;

int n,k;
int dp[maxn][maxn*3];
char s[maxn],t[maxn*3];
void work(){
    n=read();k=read();
    scanf("%s%s",s+1,t+k+1);
    for(int i=1;i<=k;i++)t[i]='0';
    for(int i=n+k+1;i<=n+2*k;i++)t[i]='0';
    dp[0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=i;j<=2*k+i;j++){
            dp[i][j]=0;
            if(s[i]=='0'||s[i]=='?'){
                if(t[j]=='0'||t[j]=='?')(dp[i][j]+=dp[i-1][j-1])%=mod;
            }
            if(s[i]=='1'||s[i]=='?'){
                if(t[j]=='1'||t[j]=='?')(dp[i][j]+=dp[i-1][j-1])%=mod;
                if(j>=3){
                    if((t[j]=='0'||t[j]=='?')&&(t[j-1]=='0'||t[j-1]=='?')&&(t[j-2]=='0'||t[j-2]=='?'))(dp[i][j]+=dp[i-1][j-3])%=mod;
                }
            }
        }
    }
    printf("%lld\n",dp[n][n+2*k]);
}

bool med;
int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    T=read();
    while(T--)work();
}