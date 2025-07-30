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
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n,a[maxn];
vector<pii> ans;
int m,b[maxn],p[maxn],t[maxn];
void work(){
    n=read();ans.clear();
    for(int i=1;i<=n;i++)a[i]=read();
    if(a[1]==a[n]){
        int p=n;while(a[p]==a[1])p--;
        if(!p){puts("0");return ;}
        n=p;
        for(int i=p+1;i<=n;i++)ans.pb({p,i});
    }
    for(int i=1;i<n;i++)if(a[i]!=a[i+1])ans.pb({i,i+1});
    m=0;for(int l=1,r;l<=n;l=r){
        r=l;while(a[l]==a[r])r++;r--;
        if(r==n){
            for(int i=l;i<=r;i++)ans.pb({p[m],i});
            ++m;b[m]=a[l],p[m]=r;
        }
        else{
            for(int i=l;i<=r;i++)ans.pb({i,r+1});
            ++m;b[m]=a[l],p[m]=l;
        }
    }
    for(int i=1;i<=n;i++)t[i]=0;
    for(int i=1;i<=m;i++)t[b[i]]++;
    int num=0;for(int i=1;i<=n;i++)num+=(t[i]>0);
    if(num==2){
        for(int i=4;i<=m;i+=2)ans.pb({p[1],p[i]});
    }
    else{
        ans.pb({p[1],p[m]});
        for(int i=2,j=1;i<m;i++)if(b[i]!=b[j]&&b[i]!=b[m]){
            for(int k=j;k<i;k++)t[b[k]]--;
            if(!t[b[j]]){
                for(int k=i;k<=n;k++)ans.pb({p[j],p[k]});
                for(int k=j+1;k<i;k++)ans.pb({p[j],p[k]});
                break;
            }
            else{
                for(int k=j;k<i;k++)ans.pb({p[k],p[i]});
                ans.pb({p[n],p[i]});
                i=j;
            }
        }
    }
    printf("%d\n",ans.size());
    for(auto[u,v]:ans)printf("%d %d\n",u,v);
}

bool med;
int T;
signed main(){
    freopen("A.in","r",stdin);
    freopen("A.out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    T=read();
    while(T--)work();
}