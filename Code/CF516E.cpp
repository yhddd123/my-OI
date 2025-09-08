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

int n,m,p,q,d,ans;
void exgcd(int a,int b,int &x,int &y){
	if(!b){x=1,y=0;return ;}
	exgcd(b,a%b,y,x);
	y-=(a/b)*x;
}
vector<int> a[maxn],b[maxn];
pii st[maxn<<1];int tp;
int calc(int n,int m,int k,vector<int> &a,vector<int> &b){
	if(a.size()==n)return -1;
	tp=0;for(int p:a)st[++tp]={p*k%n,p};
	for(int p:b)st[++tp]={p*k%n,p};
	sort(st+1,st+tp+1);
	for(int i=1;i<=tp;i++)st[i+tp]={st[i].fi+n,st[i].se};
	for(int i=2;i<=2*tp;i++)st[i].se=min(st[i].se,st[i-1].se+(st[i].fi-st[i-1].fi)*m);
	int ans=0;for(int i=1;i<=tp;i++)ans=max(ans,st[i].se);
	for(int i=1;i<=tp;i++)if(st[i].fi<st[i+1].fi)ans=max(ans,st[i].se+(st[i+1].fi-st[i].fi-1)*m);
	return ans;
}
void work(){
    n=read();m=read();d=__gcd(n,m);
    p=read();for(int i=1;i<=p;i++){int x=read();a[x%d].pb(x/d);}
    q=read();for(int i=1;i<=q;i++){int x=read();b[x%d].pb(x/d);}
    if(d>p+q){puts("-1");return ;}
    n/=d,m/=d;
    int k1,k2;exgcd(m,n,k1,k2);
    ((k1%=n)+=n)%=n,((k2%=m)+=m)%=m;
    // cout<<k1*m%n<<" "<<k2*n%m<<" "<<k1*m+k2*n<<"\n";
    for(int i=0;i<d;i++){
        if(!a[i].size()&&!b[i].size()){puts("-1");return ;}
        ans=max(ans,calc(n,m,k1,a[i],b[i])*d+i);
        ans=max(ans,calc(m,n,k2,b[i],a[i])*d+i);
    }
    printf("%lld\n",ans);
}

bool med;
int T;
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    T=1;
    while(T--)work();
}