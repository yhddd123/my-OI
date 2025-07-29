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

int n,m,ans;
pii a[maxn],b[maxn];
pii operator-(pii u,pii v){return {u.fi-v.fi,u.se-v.se};}
bool operator<(pii u,pii v){return u.fi*v.se<v.fi*u.se;}
void work(){
    n=read();m=read();
    for(int i=1;i<=n;i++)a[i]={read(),i};
    for(int i=1;i<=m;i++)b[i]={read(),i};
    vector<pii> id1,id2;
    id1.pb(a[1]);for(int i=2;i<=n;i++){
        while(id1.size()>1&&(a[i]-id1[id1.size()-2])<(id1[id1.size()-1]-id1[id1.size()-2]))id1.pop_back();
        id1.pb(a[i]);
    }
    id2.pb(b[1]);for(int i=2;i<=m;i++){
        while(id2.size()>1&&(b[i]-id2[id2.size()-2])<(id2[id2.size()-1]-id2[id2.size()-2]))id2.pop_back();
        id2.pb(b[i]);
    }
    int p=0,q=0;
    while(p+1<id1.size()&&q+1<id2.size()){
        if((id1[p+1]-id1[p])<(id2[q+1]-id2[q]))ans+=(id1[p+1].se-id1[p].se)*id2[q].fi,p++;
        else ans+=(id2[q+1].se-id2[q].se)*id1[p].fi,q++;
        // cout<<ans<<" "<<p<<" "<<q<<"\n";
    }
    while(p+1<id1.size())ans+=(id1[p+1].se-id1[p].se)*id2[q].fi,p++;
    while(q+1<id2.size())ans+=(id2[q+1].se-id2[q].se)*id1[p].fi,q++;
    printf("%lld\n",ans);
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