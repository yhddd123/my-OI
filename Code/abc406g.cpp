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

int n,c,d;
map<int,int> mp;
int k,b;
pii pos[maxn];
int ans[maxn];
void work(){
    n=read();c=read();d=read();
    k=-c,b=0;
    mp[0]=2*c;
    for(int i=1;i<=n;i++){
        int p=read();
        mp[p]+=2*d;
        k-=d,b+=d*p;
        // cout<<i<<"\n"<<k<<" "<<b<<"\n";
        // for(auto [x,d]:mp)cout<<x<<" "<<d<<"\n";
        if(-k<=c)pos[i]={-inf,inf};
        else{
            int kk=-k;
            while(kk>c){
                auto[x,d]=*--mp.end();
                int del=min(kk-c,d);
                kk-=del,mp[x]-=del;
                if(!mp[x])mp.erase(mp.find(x));
            }
            while(k<-c){
                auto[x,d]=*mp.begin();
                int del=min(-c-k,d);
                k+=del,mp[x]-=del;b+=x*(-del);
                if(!mp[x])mp.erase(mp.find(x));
            }
            pos[i]={(*mp.begin()).fi,(*--mp.end()).fi};
            // cout<<(*mp.begin()).fi<<" "<<(*mp.rbegin()).fi<<"\n";
        }
        // cout<<i<<"\n"<<k<<" "<<b<<"\n";
        // for(auto [x,d]:mp)cout<<x<<" "<<d<<"\n";
    }
    while(k<0){
        auto[x,d]=*mp.begin();
        int del=min(-k,d);
        k+=del,b+=x*(-del);
        if(!k)ans[n]=x;
        mp.erase(mp.begin());
    }
    printf("%lld\n",b);
    for(int i=n-1;i;i--){
        if(ans[i+1]<pos[i].fi)ans[i]=pos[i].fi;
        else if(ans[i+1]>pos[i].se)ans[i]=pos[i].se;
        else ans[i]=ans[i+1];
    }
    for(int i=1;i<=n;i++)printf("%lld ",ans[i]);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}