#include<bits/stdc++.h>
#define ll long long
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
const int maxn=5000010;
const int inf=1e9;
bool mbe;

int n,op;
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
inline int grnd(int &s) {
    s ^= s << 13;
    s ^= s >> 17;
    s ^= s << 5;
    if (s < 0) s = -s;
    return s;
}
ll ans[maxn],res;
ll siz[maxn],sum,sqr;
int dfn[maxn],rnk[maxn],idx;
void dfs(int u,int fa){
	siz[u]=1;
	rnk[dfn[u]=++idx]=u;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa)continue;
		dfs(v,u);siz[u]+=siz[v];
		if(siz[v]==n/2){
			for(int j=1;j<=n;j++)ans[j]+=n/2;
			// ans[u]--,ans[v]--;
		}
	}
	(sum+=siz[u])%=mod,(sqr+=siz[u]*siz[u])%=mod;
}
#define lb(x) (x&(-x))
int t1[maxn],t2[maxn];
void dfs1(int u,int fa){
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa)continue;
		ll ss=sum,sq=sqr,su=siz[u],sv=siz[v];
		(sum+=mod-siz[u])%=mod,(sqr+=mod-siz[u]*siz[u]%mod)%=mod;
		t1[siz[u]]--,siz[u]-=siz[v],t1[siz[u]]++;
		(sum+=siz[u])%=mod,(sqr+=siz[u]*siz[u])%=mod;
		int num=0;
		if(siz[v]==n/2){
			ll val=(sum*n/2-sqr+mod)%mod;
			(ans[u]+=val)%=mod,(ans[v]+=val)%=mod;
		}
		else{
			if(siz[u]>n/2)num+=t1[siz[u]-n/2],num+=t2[siz[u]-n/2];
			else num-=t2[siz[v]-n/2];
		}
		t2[siz[v]]++;
		(sum+=mod-siz[v])%=mod,(sqr+=mod-siz[v]*siz[v]%mod)%=mod;
		t1[siz[v]]--,siz[v]+=siz[u],t1[siz[v]]++;
		(sum+=siz[v])%=mod,(sqr+=siz[v]*siz[v])%=mod;
		dfs1(v,u);
		sum=ss,sqr=sq;
		t1[siz[v]]--,siz[v]=sv,t1[siz[v]]++;
		if(siz[v]!=n/2){
			if(siz[u]>n/2)num-=t2[siz[u]-n/2];
			else num+=t2[siz[v]-n/2];
			int val=1ll*num*abs(siz[u]-n/2)%mod*min(siz[u],siz[v])%mod;
			(ans[u]+=val)%=mod,(ans[v]+=val)%=mod;
			// cout<<u<<" "<<v<<" "<<val<<" "<<t2.que(abs(siz[u]-n/2))<<" "<<num<<"\n";
		}
		t1[siz[u]]--,siz[u]=su,t1[siz[u]]++;
	}
}
void work(){
	n=read();op=read();
	if(n&1){puts("0");return ;}
	if(op==1){
		for(int i=1;i<n;i++){
			int u=read(),v=read();
			add(u,v),add(v,u);
		}
	}
	else{
		int a=read(),b=read();
	    for (int i = 1; i < n; i++) {
	    	int p=max(1, i - grnd(b) % a);
	    	add(p,i+1),add(i+1,p);
	    	// cout<<p<<" "<<i+1<<"\n";
	    }
	}
	dfs(1,0);
	for(int i=1;i<=n;i++)t1[siz[i]]++;
	dfs1(1,0);
	for(int i=1,mul=1;i<=n;i++,mul=1ll*mul*2333%mod)(res+=1ll*mul*ans[i])%=mod;
	printf("%lld\n",res);
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