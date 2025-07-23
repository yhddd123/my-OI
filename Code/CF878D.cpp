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
const int maxn=100100;
const int maxm=13;
const int inf=1e9;

int n,m,k,q;
int a[maxm+1][maxn];
int lsh[maxn][maxm];
int val[maxn*maxm];
bitset<1<<maxm> f[maxn];
void work(){
    n=read();k=read();q=read();m=k;
    for(int i=1;i<=k;i++){
        for(int j=1;j<=n;j++)a[i][j]=read(),lsh[j][i-1]=a[i][j];
    }
    for(int i=1;i<=n;i++){
        sort(lsh[i],lsh[i]+k);
        for(int j=1;j<=k;j++){
            a[j][i]=lower_bound(lsh[i],lsh[i]+k,a[j][i])-lsh[i];
            for(int p=i*k;p<=i*k+a[j][i];p++)val[p]|=1<<j-1;
        }
    }
    for(int s=0;s<(1<<k);s++){
        for(int i=1;i<=k;i++)if(s&(1<<i-1))f[i][s]=1;
    }
    while(q--){
        int op=read(),x=read(),y=read();
        if(op==1)f[++m]=f[x]|f[y];
        if(op==2)f[++m]=f[x]&f[y];
        if(op==3){
            // for(int p=k;p<(n+1)*k;p++)cout<<f[x][val[p]]<<" ";cout<<"\n";
            for(int p=(y+1)*k-1;p>=y*k;p--)if(f[x][val[p]]){
                printf("%d\n",lsh[y][p-y*k]);
                break;
            }
        }
    }
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen("A.out","w",stdout);
    
    T=1;
    while(T--)work();
}