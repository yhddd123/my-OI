#include <algorithm>
#include<bits/stdc++.h>
#include <cstdio>
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

int n,m,ans;
vector<int> a[60];
void work(){
    n=read();m=read();ans=0;
    for(int i=0;i<60;i++)a[i].clear();
    for(int i=1;i<=n;i++)a[read()].pb(read());
    for(int i=0;i<60;i++){
        sort(a[i].begin(),a[i].end());
        if((m&(1ll<<i))&&a[i].size())ans+=a[i].back(),a[i].pop_back();
        if(i==59)break;
        while(a[i].size()>=2){
            int w=a[i].back();a[i].pop_back();
            w+=a[i].back();a[i].pop_back();
            a[i+1].pb(w);
        }
        if(a[i].size())a[i+1].pb(a[i].back());
    }
    printf("%lld\n",ans);
}

int T;
signed main(){
    freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=read();
    while(T--)work();
}