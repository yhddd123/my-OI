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
const int maxn=15;
const int inf=1e9;
bool mbe;

inline int ksm(int a,int b=mod-2){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
int n,m,res,mul=1;
int e[maxn],num[1<<maxn];
int f[1<<maxn],g[1<<maxn],coef[1<<maxn];
int pw[maxn*maxn];
int fa[maxn],id[maxn],vis[maxn];
int fd(int x){
	if(fa[x]==x)return x;
	return fa[x]=fd(fa[x]);
}
tuple<int,int,int> edge[maxn*maxn];
int ans[1<<maxn];
int bel[1<<maxn],sum[1<<maxn];
int cross(int s,int t){return (num[s|t]-num[s]-num[t])/2;}
void work(){
	n=read();m=read();mul=1;
	for(int i=1;i<=m;i++){
		int u=read()-1,v=read()-1,w=read();
		edge[i]={w,u,v};
	}
	for(int s=0;s<(1<<n);s++)ans[s]=0;
	for(int i=0;i<n;i++)ans[1<<i]=1;
	sort(edge+1,edge+m+1);
	for(int i=0;i<n;i++)fa[i]=i,id[i]=1<<i;
	for(int l=1,r=1;l<=m;l=r+1){
		while(r+1<=m&&get<0>(edge[l])==get<0>(edge[r+1]))r++;
		bool fl=0;
		for(int i=l;i<=r;i++){
			auto[w,u,v]=edge[i];
			if(fd(u)!=fd(v))fl=1;
			else mul=mul*4%mod;
		}
		if(!fl)continue;
		for(int i=0;i<n;i++)e[i]=0;
		for(int s=0;s<(1<<n);s++)num[s]=0;
		for(int i=l;i<=r;i++){
			auto[w,u,v]=edge[i];
			if(fd(u)!=fd(v)){
				e[u]|=1<<v,e[v]|=1<<u;
				num[(1<<u)|(1<<v)]+=2;
			}
		}
		for(int i=0;i<n;i++){
			for(int s=0;s<(1<<n);s++)if(s&(1<<i))num[s]+=num[s^(1<<i)];
		}
		for(int s=0;s<(1<<n);s++)sum[s]=0;
		for(int i=0;i<n;i++)if(fa[i]==i){
			for(int s=id[i];s;s=(s-1)&id[i])bel[s]=id[i],(sum[id[i]]+=ans[s])%=mod;
		}
		sum[0]=coef[0]=1;
		for(int s=1;s<(1<<n);s++){
			int u=__lg(s);
			bel[s]=bel[1<<u]|bel[s^(1<<u)];
			if((s&bel[1<<u])==bel[1<<u])sum[s]=sum[s^bel[1<<u]]*sum[bel[1<<u]]%mod;
			else sum[s]=0;
			coef[s]=coef[s^(s&bel[1<<u])]*ans[s&(bel[1<<u])]%mod;
		}
		for(int i=0;i<n;i++)vis[i]=0;
		for(int i=l;i<=r;i++){
			auto[w,u,v]=edge[i];
			u=fd(u),v=fd(v);
			if(u!=v)fa[u]=v,vis[v]=1,id[v]|=id[u],id[u]=0;
		}
		for(int i=0;i<n;i++)if(fa[i]==i&&vis[i]){
			vector<int> ids;
			for(int s=id[i];s;s=(s-1)&id[i])ids.pb(s);
			reverse(ids.begin(),ids.end());
			f[0]=1,g[0]=mod-1;
			for(int s:ids){
				g[s]=0;for(int t=(s-1)&s;t;t=(t-1)&s)if(!(bel[t]&bel[s^t])&&__lg(s)==__lg(t)){
					int cnt=cross(t,bel[s^t]^(s^t))+cross(s^t,bel[t]^t)+num[bel[s]^s]-num[bel[t]^t]-num[bel[s^t]^(s^t)];
					// cout<<s<<" "<<t<<" "<<f[t]<<" "<<g[s^t]<<" "<<cnt<<" g\n";
					(g[s]+=mod-f[t]*g[s^t]%mod*pw[cnt]%mod)%=mod;
				}
				f[s]=coef[s]*pw[num[bel[s]]]%mod;
				for(int t=s;t;t=(t-1)&s)if(!(bel[t]&bel[s^t])){
					int cnt=cross(t,bel[s^t])+num[bel[s]^t]-num[bel[t]^t];
					(f[s]+=mod-g[t]*coef[s^t]%mod*pw[cnt]%mod)%=mod;
					// cout<<s<<" "<<t<<" "<<f[s]<<" "<<g[t]<<" "<<coef[s^t]<<" "<<cnt<<"\n";
				}
				(g[s]+=f[s])%=mod;
				// cout<<f[s]<<" "<<g[s]<<"\n";
			}
			for(int s:ids)ans[s]=0;
			for(int s:ids){
				for(int t=s;t;t=(t-1)&s)if(!(bel[t]&bel[s^t])){
					int cnt=cross(t,id[i]^bel[t]^(s^t))+cross(s^t,id[i]^t^bel[s^t])+num[id[i]^s]-num[bel[t]^t]-num[bel[s^t]^(s^t)];
					(ans[t]+=mod-f[t]*g[s^t]%mod*pw[cnt]%mod*sum[id[i]^bel[s]]%mod)%=mod;
					// if(t==5)cout<<s<<" "<<t<<" "<<cnt<<" "<<sum[id[i]^bel[s]]<<" "<<f[t]<<" "<<g[s^t]<<" "<<cnt<<"\n";
				}
			}
		}
	// for(int s=0;s<(1<<n);s++)cout<<f[s]*mul%mod<<" ";cout<<"\n";
	// for(int s=0;s<(1<<n);s++)cout<<g[s]*mul%mod<<" ";cout<<"\n";
	// for(int s=0;s<(1<<n);s++)cout<<ans[s]*mul%mod<<" ";cout<<"\n";
	}
	res=0;for(int s=0;s<(1<<n);s++)(res+=ans[s])%=mod;
	// cout<<res<<"\n";
	printf("%lld\n",res*mul%mod*ksm(ksm(4,m))%mod);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	pw[0]=1;for(int i=1;i<maxn*maxn;i++)pw[i]=pw[i-1]*2%mod;
	
	read();T=read();
	while(T--)work();
}