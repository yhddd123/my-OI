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
const int maxn=1010;
const int inf=1e9;

int n;
void sovle(int n){
    if(n<=1)return ;
    sovle(n-4);
    for(int i=n-4;i;i--)printf("%d %d\n",i,n-3);
    printf("%d %d\n",n-3,n-2);
    for(int i=1;i<=n-4;i++)printf("%d %d\n",i,n-2);
    for(int i=n-4;i;i--)printf("%d %d\n",i,n-1);
    printf("%d %d\n",n-1,n);
    for(int i=1;i<=n-4;i++)printf("%d %d\n",i,n);
    printf("%d %d\n",n-2,n);printf("%d %d\n",n-3,n-1);
    printf("%d %d\n",n-3,n);printf("%d %d\n",n-2,n-1);
}
void work(){
    n=read();
    if(n%4==2||n%4==3){puts("NO");return ;}
    puts("YES");
    sovle(n);
}

int T;
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}