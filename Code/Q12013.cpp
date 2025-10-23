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
const int maxn=1055;
const int maxm=55;
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
int n,m,p[maxm*2],ans;
pii f[maxn][maxm],g[maxn][maxm],w[maxm*2];
pii operator+(pii u,pii v){return {(u.fi+v.fi)%mod,(u.se+v.se)%mod};}
pii operator*(pii u,pii v){return {u.fi*v.fi%mod,(u.fi*v.se+u.se*v.fi)%mod};}
void work(){
	n=read();m=read();
	for(int i=-m;i<=m;i++)p[i+m]=read()*ksm(100000000)%mod;
	for(int i=0;i<n;i++){
		for(int j=-m;j<=m;j++)w[j+m]={0,0};
		for(int j=-m;j<=m;j++)(w[max(-i,j)+m].fi+=p[j+m])%=mod,(w[max(-i,j)+m].se+=p[j+m])%=mod;
		for(int j=max(-m,-i);j<0;j++){
			for(int k=1;k<=m;k++)w[j+k+m]=w[j+k+m]+w[j+m]*f[i+j][k];
		}
		int ni=ksm(1+mod-w[m].fi);
		for(int j=1;j<=m;j++){
			f[i][j].fi=w[j+m].fi*ni%mod;
			f[i][j].se=(w[j+m].se+w[m].se*f[i][j].fi%mod)*ni%mod;
			// cout<<i<<" "<<j<<" "<<f[i][j].fi<<" "<<f[i][j].se<<"\n";
		}
	}
	g[0][0]={1,0};
	for(int i=0;i<n;i++){
		for(int j=min(i,m);~j;j--){
			// cout<<i<<" "<<j<<" "<<g[i][j].fi<<" "<<g[i][j].se<<"\n";
			for(int k=1;k<=m;k++){
				if(k>j)g[i-j+k][k-j]=g[i-j+k][k-j]+g[i][j]*f[i-j][k];
				else g[i][j-k]=g[i][j-k]+g[i][j]*f[i-j][k];
			}
		}
	}
	for(int i=n;i<=n+m;i++){
		for(int j=0;j<=m;j++)(ans+=g[i][j].se)%=mod;
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