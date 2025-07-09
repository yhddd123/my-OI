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

int n,a[maxn];
#define lb(x) (x&(-x))
int tree[maxn];
void upd(int x,int w){
    while(x<=n)tree[x]=max(tree[x],w),x+=lb(x);
}
int que(int x){
    int res=0;
    while(x)res=max(res,tree[x]),x-=lb(x);
    return res;
}
void clr(){
    for(int i=1;i<=n;i++)tree[i]=0;
}
int f[maxn],g[maxn],mx;
int cnt[maxn];
void work(){
    n=read();mx=0;
    for(int i=1;i<=n;i++)a[i]=read();
    clr();for(int i=1;i<=n;i++){
        f[i]=que(a[i]-1)+1;
        upd(a[i],f[i]);
        mx=max(mx,f[i]);
    }
    if(!(mx&1)){
        puts("YES");
        // for(int i=1;i<=n;i++){
        //     if(f[i]<=mx/2)putchar('0');
        //     else putchar('1');
        // }
        // puts("");
    }
    else{
        clr();for(int i=n;i;i--){
            g[i]=que(n-a[i])+1;
            upd(n-a[i]+1,g[i]);
        }
        for(int i=1;i<=n;i++)cnt[i]=0;
        for(int i=1;i<=n;i++)if(f[i]+g[i]-1==mx)++cnt[f[i]];
        // cout<<mx<<"\n";
        // for(int i=1;i<=n;i++)cout<<f[i]<<" "<<g[i]<<"\n";
        int id=0,p=0;for(int i=1;i<=n;i++)if(f[i]+g[i]-1>=(mx+1)/2&&(f[i]+g[i]-1!=mx||cnt[f[i]]>1))id=f[i],p=i;
        if(!id)puts("NO");
        else{
            puts("YES");
            // int l=id-min(id,(mx+1)/2)+1,r=l+(mx+1)/2-1;
            // for(int i=1;i<=n;i++){
            //     if(f[i]<l||f[i]>r||(f[i]==id&&i!=p))putchar('0');
            //     else putchar('1');
            // }
            // puts("");
        }
    }
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=read();
    while(T--)work();
}