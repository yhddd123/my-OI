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
const int maxn=200010;
const int inf=1e9;

int n,m,a[maxn],b[maxn];
int c[maxn],d[maxn];
int calc(int x){
    int ans=0;for(int i=1;i<=n;i++)ans+=abs(d[i]-x);
    return ans;
}
void work(){
    n=read();m=read();
    for(int i=1;i<=n;i++)a[i]=read();
    for(int i=1;i<=n;i++)b[i]=read();
    if(m==2){
        for(int i=1;i<=n;i++)if(a[i]!=b[i]){puts("-1");return ;}
        puts("0");return ;
    }
    c[1]=b[1];for(int i=2;i<=n;i++){
        if(a[i-1]<a[i]){
            if(b[i-1]<b[i])c[i]=c[i-1]+b[i]-b[i-1];
            else c[i]=c[i-1]+b[i]+m-b[i-1];
        }
        else{
            if(b[i-1]<b[i])c[i]=c[i-1]+b[i]-m-b[i-1];
            else c[i]=c[i-1]+b[i]-b[i-1];
        }
    }
    for(int i=1;i<=n;i++)d[i]=a[i]-c[i];
    sort(d+1,d+n+1);
    int v=d[n/2+1];
    printf("%lld\n",min({calc((v/m-1)*m),calc(v/m*m),calc((v/m+1)*m)}));
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}