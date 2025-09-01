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
const int maxn=300010;
const int inf=1e18;

int n,a,b,l,r,x[maxn],ans;
map<int,int> valk,valb;
void upd(int pl,int pr,int k,int b){
    pl=max(pl,l),pr=min(pr,r);
    if(pl>pr)return ;
    // cout<<pl<<" "<<pr<<" "<<k<<" "<<b<<"\n";
    valk[pl]+=k,valk[pr+1]-=k,valb[pl]+=b,valb[pr+1]-=b;
}
void work(){
    n=read();a=read(),b=min(a,read());
    for(int i=1;i<=n;i++)x[i]=read();
    sort(x+1,x+n+1);
    l=x[(n+1)/2]-a,r=x[(n+1)/2]+a;
    // cout<<l<<" "<<r<<"\n";
    int d=(a==b)?a-1:(a+b)/2;
    valk.clear(),valb.clear();
    for(int i=1;i<=n;i++){
        // cout<<x[i]<<" "<<max(x[i],(l/a-1)*a+(x[i]%a))<<" "<<min(x[i],(r/a+1)*a+(x[i]%a))<<"\n";
        int pp=max(x[i],(l/a-1)*a+(x[i]%a));
        while(pp<=r){
            upd(pp,pp+d,1,(pp-x[i])/a*b-pp);
            upd(pp+d+1,pp+a-1,-1,((pp-x[i])/a+1)*b+pp+a);
            pp+=a;
        }
        pp=min(x[i],(r/a+1)*a+(x[i]%a));
        while(pp>=l){
            upd(pp-d,pp,-1,(x[i]-pp)/a*b+pp);
            upd(pp-a+1,pp-d-1,1,((x[i]-pp)/a+1)*b-pp+a);
            pp-=a;
        }
    }
    vector<int> p;
    for(pii pp:valk)p.pb(pp.fi);
    int sk=0,sb=0,lst=l;
    ans=inf;for(int i=0;i<p.size()-1;i++){
        sk+=valk[p[i]],sb+=valb[p[i]];
        // cout<<p[i]<<" "<<sk<<" "<<sb<<" "<<sk*p[i]+sb<<" "<<sk*(p[i+1]-1)+sb<<"\n";
        ans=min({ans,sk*p[i]+sb,sk*(p[i+1]-1)+sb});
    }
    printf("%lld\n",ans);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen("A.out","w",stdout);
    
    T=read();
    while(T--)work();
}