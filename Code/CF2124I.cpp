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

int n,a[maxn];
int lst[maxn],p[maxn],d[maxn];
void work(){
    n=read();
    for(int i=1;i<=n;i++)a[i]=read();
    for(int i=1;i<=n;i++)if(a[i]>a[i-1]+1){puts("NO");return ;}
    for(int i=1;i<=n;i++)lst[i]=0;
    for(int i=1;i<=n;i++){
        p[i]=lst[a[i]-1];
        lst[a[i]]=i;
    }
    for(int i=0;i<=n;i++)d[i]=0;
    for(int i=1;i<=n;i++)d[p[i]]++;
    if(d[0]>1){puts("NO");return ;}
    for(int i=1;i<=n;i++)if(d[i]>1&&d[p[i]]>1){puts("NO");return ;}
    puts("YES");
}

int T;
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=read();
    while(T--)work();
}