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
bool mbe;

int k,n;
vector<pii> ans;
void work(){
    k=read();
    if(!k){puts("2 0");return ;}
    vector<int> a;
    while(k){
        int v1=k/(-2),v2=k+2*v1;
        if(v2<0)v1++,v2=1;
        a.pb(v2);
        // cerr<<v1<<" "<<v2<<" "<<k<<"\n";
        k=v1;
    }
    for(int v:a)cerr<<v<<" ";cerr<<"\n";
    ans.pb({1,2}),ans.pb({1,3}),ans.pb({1,4}),ans.pb({1,5});n=5;
    for(int i=1;i<a.size();i++){
        for(int j:{n-3,n-2,n-1}){
            for(int k:{n+1,n+2,n+3,n+4})ans.pb({j,k});
        }
        n+=4;
    }
    ++n;
    // ans.pb({n-1,n});
    for(int i=0;i<a.size();i++)if(a[i])ans.pb({(i+1)*4,n}),ans.pb({(i+1)*4+1,n});
    printf("%lld %lld\n",n,ans.size());
    for(auto[u,v]:ans)printf("%lld %lld\n",u,v);
}

bool med;
int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen("A.out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    T=1;
    while(T--)work();
}