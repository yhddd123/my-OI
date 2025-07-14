#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=500010;
inline ll read(){
	ll x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3ll)+(x<<1ll)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

ll n,a[maxn],ans;
map<ll,ll> t;
int tree[maxn<<5][2],idx=1;
ll sum[maxn<<5],mul[maxn<<5];
void clr(){
	for(int i=1;i<=idx;i++)tree[i][0]=tree[i][1]=sum[i]=mul[i]=0;
	idx=1;
}
void work(){
	n=read();ll ans=n*(n-1)*(n-2)/6;
	clr();t.clear();
	for(int i=1;i<=n;i++){
		a[i]=read();t[a[i]]++;ll val=t[a[i]]-1;
		ll ressum=0,resmul=0,nd=1;
		for(int j=0;j<60;j++){
			int c=(a[i]>>j)&1ll;
			sum[nd]++;mul[nd]+=val;
			if(!tree[nd][c])tree[nd][c]=++idx;
			nd=tree[nd][c];
		}
		sum[nd]++;mul[nd]+=val;
		nd=1;
		for(int j=0;j<60;j++){
			int c=(a[i]>>j)&1ll;
			if(!(j&1))ressum+=sum[tree[nd][c^1]];
			if(!(j&1))resmul+=mul[tree[nd][c^1]];
			nd=tree[nd][c];
		}
		ans-=(t[a[i]]-1)*ressum;;
		ans-=resmul;
	}
	for(int i=1;i<=n;i++)ans-=t[a[i]]*(t[a[i]]-1)*(t[a[i]]-2)/6,t[a[i]]=0;
	printf("%lld\n",ans);
}

// \
444

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=read();
	while(T--)work();
}
