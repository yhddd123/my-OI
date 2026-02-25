// Problem: AT_agc018_e [AGC018E] Sightseeing Plan
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_agc018_e
// Memory Limit: 256 MB
// Time Limit: 8000 ms
// Written by yhm.
// Start codeing:2026-02-25 18:20:24
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
// #define int long long
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
const int maxn=1000010;
const int inf=1e9;
bool mbe;

inline int ksm(int a,int b=mod-2){
    int ans=1;
    while(b){
        if(b&1)ans=1ll*ans*a%mod;
        a=1ll*a*a%mod;
        b>>=1;
    }
    return ans;
}
int fac[maxn<<1],inv[maxn<<1];
int C(int m,int n){
    if(n<0||m<0||m<n)return 0;
    return 1ll*fac[m]*inv[n]%mod*inv[m-n]%mod;}
void init(int n){
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=1ll*fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
#define y1 yy1
int ans;
int x1,x2,x3,x4,x5,x6;
int y1,y2,y3,y4,y5,y6;
pii a[8];
int calc(pii u,pii v){return C(v.fi-u.fi+v.se-u.se,v.fi-u.fi);}
int calc(pii a,pii b,pii c,pii d){
	int ans=0;
	for(int i=b.fi,j=b.se;i<=c.fi;i++){
		inc(ans,mod-1ll*calc(a,{i,j-1})*calc({i,j},d)%mod*(i+j)%mod);
	}
	for(int j=b.se,i=b.fi;j<=c.se;j++){
		inc(ans,mod-1ll*calc(a,{i-1,j})*calc({i,j},d)%mod*(i+j)%mod);
	}
	for(int i=b.fi,j=c.se;i<=c.fi;i++){
		inc(ans,1ll*calc(a,{i,j})*calc({i,j+1},d)%mod*(i+j+1)%mod);
	}
	for(int j=b.se,i=c.fi;j<=c.se;j++){
		inc(ans,1ll*calc(a,{i,j})*calc({i+1,j},d)%mod*(i+j+1)%mod);
	}
	// for(int i=b.fi;i<=c.fi;i++){
		// for(int j=b.se;j<=c.se;j++)inc(ans,1ll*calc(a,{i,j})*calc({i,j},d)%mod);	
	// }
	// cout<<ans<<"\n";
	return ans;	
}
void work(){
	cin>>x1>>x2>>x3>>x4>>x5>>x6>>y1>>y2>>y3>>y4>>y5>>y6;init(2*maxn-10);
	a[0]={x1-1,y1-1};a[1]={x1-1,y2},a[2]={x2,y2},a[3]={x2,y1-1};
	a[4]={x6+1,y6+1};a[5]={x6+1,y5},a[6]={x5,y5},a[7]={x5,y6+1};
	for(int i=0;i<4;i++){
		for(int j=4;j<8;j++){
			int o=(i+j)&1;
			if(o)inc(ans,mod-calc(a[i],{x3,y3},{x4,y4},a[j]));
			else inc(ans,calc(a[i],{x3,y3},{x4,y4},a[j]));
		}
	}
	printf("%lld\n",ans);
}

bool med;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	int T=1;
	while(T--)work();
}