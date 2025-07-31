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
const int maxn=300010;
const int inf=2e9;
bool mbe;

int n,x,y;
pii a[maxn];
set<pii> s1,s2,s3;
void work(){
    n=read();x=1,y=1;
    for(int i=1;i<=n;i++){
        int u=read(),v=read();a[i]={u,v};
        if(u<=x)s1.insert({v,i});
        else if(v<=y)s2.insert({u,i});
        else s3.insert({u+v,i});
    }
    vector<int> ans;
    for(int i=1;i<=n;i++){
        int mn=inf,v1=inf,v2=inf,v3=inf;
        if(s1.size())v1=(*s1.begin()).fi-y;
        if(s2.size())v2=(*s2.begin()).fi-x;
        if(s3.size())v3=(*s3.begin()).fi-x-y;
        mn=min({v1,v2,v3});
        // cout<<v1<<" "<<v2<<" "<<v3<<" "<<mn<<endl;
        if(mn==v1){
            ans.pb((*s1.begin()).se);
            y=max(y,a[ans.back()].se);
            s1.erase(s1.begin());
        }
        else if(mn==v2){
            ans.pb((*s2.begin()).se);
            x=max(x,a[ans.back()].fi);
            s2.erase(s2.begin());
        }
        else{
            ans.pb((*s3.begin()).se);
            x=max(x,a[ans.back()].fi),y=max(y,a[ans.back()].se);
            s3.erase(s3.begin());
        }
        while(s3.size()){
            int id=(*s3.begin()).se;auto[u,v]=a[id];
            if(u<=x)s1.insert({v,id}),s3.erase(s3.begin());
            else if(v<=y)s2.insert({u,id}),s3.erase(s3.begin());
            else break;
        }
    }
    for(int u:ans)printf("%d ",u);
}

bool med;
int T;
signed main(){
    freopen("A.in","r",stdin);
    freopen("A.out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    T=1;
    while(T--)work();
}