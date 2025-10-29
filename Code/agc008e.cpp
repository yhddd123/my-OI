// Problem: AT_agc008_e [AGC008E] Next or Nextnext
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_agc008_e
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-10-29 16:08:19
// 
// Powered by CP Editor (https://cpeditor.org)

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
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n,a[maxn],ans=1;
int vis[maxn];bool cir[maxn];
int d[maxn],t[maxn],len[maxn];
int f[maxn];
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read(),d[a[i]]++;
	for(int i=1;i<=n;i++)if(!vis[i]){
		int x=i;while(!vis[x])vis[x]=i,x=a[x];
		if(vis[x]==i){
			while(!cir[x])cir[x]=1,x=a[x];
		}
	}
	for(int i=1;i<=n;i++)if((cir[i]&&d[i]>2)||(!cir[i]&&d[i]>1)){puts("0");return ;}
	for(int i=1;i<=n;i++)if(!d[i]&&!cir[i]){
		int x=i,l=0;while(!cir[x])l++,x=a[x];
		len[x]=l;
	}
	for(int i=1;i<=n;i++)if(cir[i]){
		// cout<<i<<endl;
		int x=a[i],fl=!len[i];while(x!=i)fl&=!len[x],x=a[x];
		if(fl){
			int l=0;while(cir[x])l++,cir[x]=0,x=a[x];
			t[l]++;
		}
		else{
			int fr=-1,ed=-1,l=0,fl=0;
			x=i;while(cir[x]){
				if(len[x]){
					if(fr==-1)fr=ed=l,fl=len[x];
					else{
						ans=ans*((len[x]<l-ed)+(len[x]<=l-ed))%mod;
						ed=l;
					}
				}
				l++,cir[x]=0,x=a[x];
			}
			// cout<<ans<<" "<<fl<<" "<<fr<<" "<<ed<<" "<<l<<"\n";
			ans=ans*((fl<fr+l-ed)+(fl<=fr+l-ed))%mod;
		}
	}
	for(int i=1;i<=n;i++)if(t[i]){
		f[0]=1;for(int j=1;j<=t[i];j++){
			f[j]=f[j-1];
			if(i>1&&(i&1))(f[j]+=f[j-1])%=mod;
			if(j>1)(f[j]+=f[j-2]*i*(j-1))%=mod;
			// cout<<f[j]<<" ";cout<<"\n";
		}
		// cout<<i<<" "<<t[i]<<" "<<f[t[i]]<<"\n";
		ans=ans*f[t[i]]%mod;
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