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
const int maxn=300010;
const int inf=1e9;
bool mbe;

int n,m,k,a[maxn],ans=1;
int lsh[maxn],len;
int st[maxn],tp;
void work(){
    n=read();m=read();k=read();
    for(int i=0;i<n;i++)a[i]=read();
    n=min(n,m+k-1);
    for(int i=0;i<n;i++)lsh[++len]=a[i];
    sort(lsh+1,lsh+len+1),len=unique(lsh+1,lsh+len+1)-lsh-1;
    for(int i=0;i<n;i++)a[i]=lower_bound(lsh+1,lsh+len+1,a[i])-lsh;
    // for(int i=0;i<n;i++)cout<<a[i]<<" ";cout<<"\n";
    for(int i=1,j=k%n;i<m;i++,j=(j+1)%n)if(a[j]!=n-m+i+1){puts("0");return ;}
    for(int j=(k%n-(k-(n-m+1))%(n-m+1)+n)%n;tp<n-m+1;j=(j+1)%n)if(a[j]<n-m+2)st[++tp]=a[j];
    // for(int i=1;i<=tp;i++)cout<<st[i]<<" ";cout<<"\n";
    for(int i=1,mx=0;i<=tp;i++)if(st[i]>mx)mx=st[i],ans=ans*m%mod;
    for(int i=1;i<m;i++)ans=ans*i%mod;
    printf("%lld\n",ans);
}

bool med;
int T;
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    T=1;
    while(T--)work();
}