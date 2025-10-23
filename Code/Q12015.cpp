#include<bits/stdc++.h>
// #define int long long
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
const int maxn=20;
const int inf=1e9;
bool mbe;

int n;
db f[1<<maxn],p[1<<maxn],ans=1.0;
void work(){
	scanf("%d",&n);
	for(int s=0;s<(1<<n);s++)scanf("%Lf",&f[s]);
	for(int i=0;i<n;i++){
		for(int s=0;s<(1<<n);s++)if(s&(1<<i))p[1<<i]+=f[s];
	}
	for(int i=0;i<n;i++){
		for(int s=0;s<(1<<n);s++)if(s&(1<<i))f[s]+=f[s^(1<<i)];
	}
	// for(int i=0;i<n;i++)p[1<<i]=1-f[(1<<n)-1-(1<<i)];
	for(int s=1;s<(1<<n);s++){
		p[s]=p[s^(s&(-s))]+p[s&(-s)];
		// db res=1;
		// for(int t=0;t<(1<<n);t++)if(!(s&t))res-=f[t];
		ans=min(ans,(1-f[(1<<n)-1-s])/p[s]);
	}
	printf("%.10Lf\n",ans);
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