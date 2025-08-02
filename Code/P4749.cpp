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
const int inf=1e9;
bool mbe;

int n,a[maxn][7],b[maxn];
int num[7],ans;
void work(){
    n=read();
    for(int i=1;i<=n;i++){
        a[i][0]=read();
        if(a[i][0]%1111111==0){i--;n--;continue;}
        for(int j=1;j<7;j++)a[i][j]=a[i][j-1]*10%10000000+a[i][j-1]/1000000;
        pii mx={a[i][0],0};
        for(int j=1;j<7;j++)mx=max(mx,{a[i][j],j});
        b[i]=mx.se;
        // for(int j=0;j<7;j++)cout<<a[i][j]<<" ";cout<<"\n";
    }
    // for(int i=1;i<=n+1;i++)cout<<b[i]<<" ";cout<<"\n";
    for(int i=n+1;i;i--)b[i]=(b[i]+7-b[i-1])%7;
    for(int i=1;i<=n+1;i++)num[b[i]]++;
    // for(int i=1;i<=n+1;i++)cout<<b[i]<<" ";cout<<"\n";
    ans=min(num[1],num[6])+min(num[2],num[5])+min(num[3],num[4]);
    int v1=num[1]<num[6]?1:6,n1=max(num[1],num[6])-min(num[1],num[6]);
    int v2=num[2]<num[5]?2:5,n2=max(num[2],num[5])-min(num[2],num[5]);
    int v3=num[3]<num[4]?3:4,n3=max(num[3],num[4])-min(num[3],num[4]);
    // cout<<v1<<" "<<v2<<" "<<v3<<" "<<n1<<" "<<n2<<" "<<n3<<"\n";
    vector<vector<vector<int>>> dp(n1+1,vector<vector<int>>(n2+1,vector<int>(n3+1)));
    dp[0][0][0]=-1;
    for(int i=0;i<=n1;i++){
        for(int j=0;j<=n2;j++){
            for(int k=0;k<=n3;k++){
                dp[i][j][k]+=(i*v1+j*v2+k*v3)%7==0;
                if(i<n1)dp[i+1][j][k]=max(dp[i+1][j][k],dp[i][j][k]);
                if(j<n2)dp[i][j+1][k]=max(dp[i][j+1][k],dp[i][j][k]);
                if(k<n3)dp[i][j][k+1]=max(dp[i][j][k+1],dp[i][j][k]);
            }
        }
    }
    printf("%d\n",ans+n1+n2+n3-dp[n1][n2][n3]);
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