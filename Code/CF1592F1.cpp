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
const int maxn=510;
const int inf=1e9;
bool mbe;

int n,m;
char c[maxn];
int a[maxn][maxn];
void work(){
    n=read();m=read();
    for(int i=1;i<=n;i++){
        scanf("%s",c+1);
        for(int j=1;j<=m;j++)a[i][j]=c[j]=='B';
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)a[i][j]^=a[i][j+1]^a[i+1][j]^a[i+1][j+1];
    }
    int num=0;for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)num+=a[i][j];
    }
    bool fl=0;
    for(int i=1;i<n;i++){
        for(int j=1;j<m;j++)if(a[i][j]&&a[i][m]&&a[n][j]&&a[n][m]){num--,fl=1;break;}
        if(fl)break;
    }
    printf("%lld\n",num);
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