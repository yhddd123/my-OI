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
const int maxn=2010;
const int inf=1e9;

int n,a[maxn][maxn];
void work(){
    n=read();
    if(n==1){puts("1");return ;}
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++)a[i][j]=read();
    }
    int l=1,r=n;
    for(int i=1;i<=n;i++)if(a[i][n]!=a[i+1][n]){l=i;break;}
    for(int i=n;i;i--)if(a[1][i]!=a[1][i-1]){r=i;break;}
    vector<int> pos;
    pos.pb(l),pos.pb(r);
    for(int i=l+1;i<r;i++){
        if(a[l][i]>a[l+1][i]){
            if(a[l][i]!=a[l][i-1])pos.pb(i);
        }
        else if(a[i][r]>a[i][r-1]){
            if(a[i][r]!=a[i+1][r])pos.pb(i);
        }
        else{
            if(a[i][r-1]==a[i+1][r-1]&&a[l+1][i]==a[l+1][i-1])pos.pb(i);
        }
    }
    sort(pos.begin(),pos.end());
    for(int u:pos)printf("%lld ",u);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}