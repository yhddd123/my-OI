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

int n,a[maxn],ans;
int t[16],f[1<<16],fl[1<<16];
void work(){
	n=read();
	for(int i=1;i<n;i++){
		int u=read()+1,v=read()+1,w=read();
		a[u]^=w,a[v]^=w;
	}
	for(int i=1;i<=n;i++)t[a[i]]++;
	ans+=t[0],t[0]=0;
	for(int i=1;i<16;i++)ans+=t[i]/2,t[i]&=1;
	int s=0;for(int i=0;i<16;i++)if(t[i])s|=1<<i;
	for(int s=0;s<(1<<16);s++){
		int v=0;for(int i=0;i<16;i++)if(s&(1<<i))v^=i;
		if(!v)fl[s]=1;
	}
	for(int s=1;s<(1<<16);s++){
		for(int t=s;t;t=(t-1)&s)if(fl[t])f[s]=max(f[s],f[s^t]+1);
	}
	printf("%lld\n",n-(ans+f[s]));
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