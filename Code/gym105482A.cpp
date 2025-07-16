#include<bits/stdc++.h>
#define int long long
#define mod 2
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
const int maxn=1000010;
const int inf=1e9;

int n,ans;
char s[maxn];
int C(int n,int m){return n>=m;}
int lucas(int n,int m){
    if(m==0)return 1;
    return C(n%mod,m%mod)&lucas(n/mod,m/mod);
}
void work(){
    scanf("%s",s+1);n=strlen(s+1);
    for(int i=1;i<=n;i++)ans^=(s[i]=='1')*lucas(n-1,i-1);
    printf("%lld\n",ans);
}

int T;
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}