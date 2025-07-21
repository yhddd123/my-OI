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

int n;
pii a[maxn];
void work(){
    n=read();
    for(int i=1;i<=n;i++)a[i]={read(),read()};
    while(1){
        bool fl[2]={0,0};
        for(int i=1;i<=n;i++)fl[(a[i].fi+a[i].se)&1]=1;
        if(fl[0]&&fl[1])break;
        if(fl[1])for(int i=1;i<=n;i++)a[i].fi--;
        for(int i=1;i<=n;i++)a[i]={(a[i].fi+a[i].se)/2,(a[i].fi-a[i].se)/2};
    }
    vector<int> id;
    for(int i=1;i<=n;i++)if((a[i].fi+a[i].se)&1)id.pb(i);
    printf("%d\n",id.size());
    for(int u:id)printf("%d ",u);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}