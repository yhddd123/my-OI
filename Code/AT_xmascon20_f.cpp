// Problem: AT_xmascon20_f Famous in Russia
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_xmascon20_f
// Memory Limit: 1024 MB
// Time Limit: 5000 ms
// Written by yhm.
// Start codeing:2025-10-22 08:48:29
// 
// Powered by CP Editor (https://cpeditor.org)

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
const int maxn=32;
const int maxm=22;
const int inf=1e9;
bool mbe;

int n,v,b[maxn];
int f[2][maxn][maxm][maxm][maxn*maxm*2],cur;
int pw[maxn],ans[maxn];
void work(){
	n=read();v=read();
	for(int i=1;i<=n;i++)b[i]=read();
	sort(b+1,b+n+1);b[n+1]=b[n]+n*v+1;
	pw[0]=1;for(int i=1;i<=n;i++)pw[i]=pw[i-1]*v%mod;
	f[0][0][0][v+1][0]=1;
	for(int i=1;i<=n+1;i++,cur^=1){
		for(int j=0;j<i;j++){
			for(int l=0;l<=v;l++){
				for(int r=l;r<=v+1;r++){
					for(int s=0;s<b[n+1];s++)if(f[cur][j][l][r][s]){
						// cout<<i<<" "<<j<<" "<<l<<" "<<r<<" "<<s<<" "<<f[cur][j][l][r][s]<<endl;
						if(b[i-1]<s&&s<=b[i])(ans[j]+=f[cur][j][l][r][s]%mod*pw[n-i+1]%mod*s)%=mod;
						if(i==n+1)continue;
						int ll,rr,ss;
						if(s<=b[i])ll=0,rr=(r==v+1?r:r-(b[i]-s)),ss=b[i];
						else ll=min(l,s-b[i]),rr=r,ss=s;
						if(ll>rr||rr<=0)continue;
						// cout<<ll<<" "<<rr<<" "<<ss<<"\n";
						for(int a=1;a<=v;a++){
							if(a>=ll)(f[i&1][j][ll][min(rr,a)][ss]+=f[cur][j][l][r][s])%=mod;
							if(a<rr)(f[i&1][j+1][max(ll,a)][rr][ss+a]+=f[cur][j][l][r][s])%=mod;
						}
						f[cur][j][l][r][s]=0;
					}
				}
			}
		}
	}
	for(int i=1;i<=n;i++)printf("%lld ",ans[i]);
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