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

int n,f[61],ans;
vector<int> pos[61];
void work(){
	n=read();ans=0;
	for(int i=0;i<=60;i++)pos[i].clear(),f[i]=0;
	for(int i=1;i<=n;i++){
		int x=read();
		pos[__lg(x)].pb(x);
	}
	for(int i=0;i<=60;i++)if(pos[i].size()){
		for(int v:pos[i]){
			int res=0;for(int j=0;j<i;j++)if(v&(1ll<<j))res+=f[j];
			f[i]=max(f[i],res);
		}
		f[i]++;
		ans+=f[i];
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