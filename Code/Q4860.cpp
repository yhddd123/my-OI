#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
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

int n,m,p,x,a,b,c,ans;
void get(){x=(a*x%p*x+b*x+c)%p;}
void work(){
	cin>>n>>m>>p>>x>>a>>b>>c;ans=0;
	map<int,int> mp;
	for(int i=1;i<=n;i++){
		get();
		if(!mp[x])mp[x]=i;
	}
	for(int i=1;i<=m;i++){
		get();
		if(mp.find(x)!=mp.end())ans=max(ans,min(m-i+1,n-mp[x]+1));
	}
	printf("%lld\n",ans);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}