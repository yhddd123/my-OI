#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
#define db double
using namespace std;
const int maxn=100010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,k;
int a[maxn];
int pos[maxn];
int lsh[maxn],len;
int f[maxn];
int sum;
void work(){
	n=read();m=read();k=read();sum=0;
	for(int i=1;i<=n;i++)a[i]=read();
	len=0;
	for(int i=1;i<=k;i++){
		int u=a[read()],t=read();
		int p=((m-(t-u))%m+m)%m;
		if(!p)p=m;
		pos[i]=p,lsh[++len]=p;
		sum+=p;
		// cout<<p<<" "<<(t-u+p)%m<<"\n";
	}
	// for(int i=1;i<=k;i++)cout<<pos[i]<<" ";cout<<"\n";
	sort(lsh+1,lsh+len+1);len=unique(lsh+1,lsh+len+1)-lsh-1;
	for(int i=1;i<=k;i++)pos[i]=lower_bound(lsh+1,lsh+len+1,pos[i])-lsh;
	for(int i=1;i<=len;i++)f[i]=0;
	for(int i=1;i<=k;i++){
		f[1]+=lsh[pos[i]],f[pos[i]+1]+=m;
	}
	for(int i=1;i<=len;i++)f[i]+=f[i-1];
	pii ans={sum,m};
	for(int i=1;i<=len;i++)ans=min(ans,{-lsh[i]*k+f[i],lsh[i]});
	// cout<<ans.fi<<" "<<ans.se<<"\n";
	printf("%lld\n",ans.fi);
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
