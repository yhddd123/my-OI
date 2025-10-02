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
const int maxn=5010;
const int maxm=100010;
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
int n,m,val,p[maxn],ans;
int fac[maxn];
char s[maxm];
int q[maxn*maxn],r[maxn*maxn];
void calc(int d){
	if(q[d]||r[d])return ;
	for(int i=1;i<=m;i++)r[d]=(r[d]*10+s[i]-'0')%d;
	q[d]=(val+mod-r[d])*ksm(d)%mod;
}
bool vis[maxn][maxn];
pii st[maxn*maxn];int tp;
int sum[maxn*maxn];
int rnk[maxn][maxn];
void work(){
	n=read();scanf("%s",s+1);m=strlen(s+1);
	for(int i=1;i<=m;i++)val=(val*10+s[i]-'0')%mod;
	for(int i=1;i<=n;i++)p[i]=read();
	fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++)if(!vis[i][j]){
			tp=0;int x=i,y=j;
			while(!vis[x][y]){
				st[++tp]={x,y};rnk[x][y]=tp;
				sum[tp]=sum[tp-1]+(x>y);
				vis[x][y]=1;
				x=p[x],y=p[y];
			}
			// cout<<i<<" "<<j<<" "<<tp<<"\n";
			calc(tp);
			for(int k=1;k<=tp;k++){
				auto[u,v]=st[k];
				if(u<v){
					int val=0;
					if(r[tp]){
						if(k+r[tp]-1<=tp)val+=sum[k+r[tp]-1]-sum[k-1];
						else val+=sum[tp]-sum[k-1]+sum[k+r[tp]-1-tp];
					}
					(val+=q[tp]*sum[tp])%=mod;
					// cout<<u<<" "<<v<<" "<<val<<"\n";
					(ans+=val*fac[n-u])%=mod;
				}
			}
		}
	}
	printf("%lld\n",(ans+val)%mod);
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