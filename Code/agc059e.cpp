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

int n,m;
char s[maxn<<2];
int a[maxn],b[maxn],c[maxn],d[maxn];
int va[maxn],vb[maxn],vc[maxn],vd[maxn];
void work(){
    n=read();scanf("%s",s+1);m=0;
    for(int i=1;i<=n;i++)a[i]=s[++m]-'1';
    b[1]=a[n];for(int i=2;i<=n;i++)b[i]=s[++m]-'1';
    c[n]=b[n];for(int i=n-1;i;i--)c[i]=s[++m]-'1';
    d[n]=c[1];for(int i=n-1;i>1;i--)d[i]=s[++m]-'1';d[1]=a[1];
    va[1]=a[1];for(int i=2;i<=n;i++)va[i]=va[i-1]+(a[i]==(a[i-1]+1)%3)*2-1;
    vb[1]=va[n];for(int i=2;i<=n;i++)vb[i]=vb[i-1]+(b[i]==(b[i-1]+1)%3)*2-1;
    vc[n]=vb[n];for(int i=n-1;i;i--)vc[i]=vc[i+1]+(c[i]==(c[i+1]+1)%3)*2-1;
    vd[n]=vc[1];for(int i=n-1;i;i--)vd[i]=vd[i+1]+(d[i]==(d[i+1]+1)%3)*2-1;
    if(va[1]!=vd[1]){puts("NO");return ;}
    // for(int i=1;i<=n;i++)cout<<va[i]<<" ";cout<<"\n";
    // for(int i=1;i<=n;i++)cout<<vb[i]<<" ";cout<<"\n";
    // for(int i=1;i<=n;i++)cout<<vc[i]<<" ";cout<<"\n";
    // for(int i=1;i<=n;i++)cout<<vd[i]<<" ";cout<<"\n";
    for(int i=1;i<=n;i++)if(abs(va[i]-vc[i])>n-1){puts("NO");return ;}
    for(int i=1;i<=n;i++)if(abs(vb[i]-vd[i])>n-1){puts("NO");return ;}
    puts("YES");
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=read();
    while(T--)work();
}