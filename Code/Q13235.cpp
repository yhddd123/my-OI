#include<bits/stdc++.h>
#define int long long
#define mod 1000000007ll
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
const int maxn=17;
const int inf=1e9;
bool mbe;

int n,m,ans;
int e[maxn],num[1<<maxn];
int f[1<<maxn],g[1<<maxn];
int pw[maxn*maxn];
int st[maxn],tp;
int val[1<<maxn],id[1<<maxn];
void sovle(int *f,int rt){
	f[1<<rt]=1;
	for(int s=0;s<(1<<n);s++)if(f[s]){
		int T=0;
		for(int i=0;i<n;i++)if(s&(1<<i))T|=e[i];
		T&=s^((1<<n)-1);
		tp=0;for(int i=0;i<n;i++)if(T&(1<<i))st[tp++]=i;
		val[0]=1;
		for(int t=1;t<(1<<tp);t++){
			int i=__lg(t);
			id[t]=id[t^(1<<i)]+(1<<st[i]);
			val[t]=val[t^(1<<i)]*(pw[__builtin_popcount(e[st[i]]&s)]-1)%mod;
			(f[s|id[t]]+=(((__builtin_popcount(t)+1)&1)?mod-1:1)*f[s]%mod*val[t]%mod*pw[num[id[t]]])%=mod;
		}
	}
}
void work(){
	n=read();m=read();read();
	for(int i=1;i<=m;i++){
		int u=read()-1,v=read()-1;
		e[u]|=1<<v,e[v]|=1<<u;
		num[(1<<u)|(1<<v)]++;
	}
	for(int i=0;i<n;i++){
		for(int s=0;s<(1<<n);s++)if(s&(1<<i))num[s]+=num[s^(1<<i)];
	}
	pw[0]=1;for(int i=1;i<n*n;i++)pw[i]=pw[i-1]*2%mod;
	sovle(f,0),sovle(g,1);
	// for(int s=0;s<(1<<n);s++)if(f[s])cout<<s<<" "<<f[s]<<" a\n";
	// for(int s=0;s<(1<<n);s++)if(g[s])cout<<s<<" "<<g[s]<<" b\n";
	for(int s=0;s<(1<<n);s++)if(s&3){
		for(int t=(s-1)&s;t;t=(t-1)&s)if((t&1)&&((s^t)&2)){
			bool fl=0;for(int tt=t,i;tt;tt-=1<<i){
				i=__lg(tt&(-tt));
				fl|=(e[i]&(s^t));
				if(fl)break;
			}
			if(fl)continue;
			// cout<<t<<" "<<(s^t)<<" "<<f[t]<<" "<<g[s^t]<<" "<<pw[num[((1<<n)-1)^s]]<<"\n";
			(ans+=f[t]*g[s^t]%mod*pw[num[((1<<n)-1)^s]])%=mod;
		}
	}
	// cout<<ans<<"\n";
	ans=(pw[m]+mod-ans)%mod;
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