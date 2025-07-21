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
int m,b[maxn];
#define lb(x) (x&(-x))
int tree[maxn];
void upd(int x,int w){while(x)tree[x]+=w,x-=lb(x);}
int que(int x){int res=0;while(x<=n)res+=tree[x],x+=lb(x);return res;}
int ans[maxn],res;
void work(){
    n=read();
    for(int i=1;i<=n;i++)a[i]=read();
    m=read();
    for(int i=1;i<=m;i++)b[i]=read();
    for(int i=1;i<=n;i++){
        int l=lower_bound(b+1,b+m+1,i)-b;
        int r=que(a[i]);upd(a[i],1);
        res+=r;ans[l]--,ans[min(m+1,l+r)]++;
        // cout<<i<<" "<<l<<" "<<r<<"\n";
    }
    // for(int i=1;i<=m;i++)cout<<ans[i]<<" ";cout<<"\n";
    for(int i=2;i<=m;i++)ans[i]+=ans[i-1];
    for(int i=1;i<=m;i++)res+=ans[i],printf("%lld\n",res);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}