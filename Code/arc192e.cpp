// Problem: AT_arc192_e [ARC192E] Snuke's Kyoto Trip
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_arc192_e
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2026-02-25 18:20:11
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
// #define int long long
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
int n,m,x1,y1,x2,y2;
int ans;
int calc(pii u,pii v){return C(v.fi-u.fi+v.se-u.se,v.fi-u.fi);}
int calc(pii a,pii b,pii c,pii d){
	int ans=0;
	for(int i=b.fi,j=b.se;i<=c.fi;i++){
		inc(ans,1ll*calc(a,{i,j-1})*calc({i,j},d)%mod);
	}
	for(int j=b.se,i=b.fi;j<=c.se;j++){
		inc(ans,1ll*calc(a,{i-1,j})*calc({i,j},d)%mod);
	}
	return ans;	
}
pii p[8];
int calcall(pii a,pii b){
	int n=b.fi-a.fi+1,m=b.se-a.se+1;
	return (C(n+m+2,n+1)-1ll*(n+1)*(m+1)%mod-1+mod)%mod;
}
int calc(pii a,pii b,pii c,pii d,pii e,pii f){
	p[0]={a.fi-1,a.se-1},p[1]={a.fi-1,b.se},p[2]={b.fi,b.se},p[3]={b.fi,a.se-1};
	p[4]={f.fi+1,f.se+1},p[5]={f.fi+1,e.se},p[6]={e.fi,e.se},p[7]={e.fi,f.se+1};
	int ans=0;
	for(int i=0;i<4;i++){
		for(int j=4;j<8;j++){
			int o=(i+j)&1;
			if(!o)inc(ans,calc(p[i],c,d,p[j]));
			else inc(ans,mod-calc(p[i],c,d,p[j]));
		}
	}
	return ans;
}
void work(){
	cin>>n>>m>>x1>>x2>>y1>>y2;init(2*maxn-10);
	n++,m++,x1++,y1++,x2++,y2++;
	inc(ans,calcall({1,1},{x1-1,m}));
	inc(ans,calcall({1,1},{n,y1-1}));
	inc(ans,calcall({x2+1,1},{n,m}));
	inc(ans,calcall({1,y2+1},{n,m}));
	inc(ans,mod-calcall({1,1},{x1-1,y1-1}));
	inc(ans,mod-calcall({1,y2+1},{x1-1,m}));
	inc(ans,mod-calcall({x2+1,1},{n,y1-1}));
	inc(ans,mod-calcall({x2+1,y2+1},{n,m}));
	inc(ans,calc({1,1},{x1-1,y2},{1,y2+1},{x1-1,m},{x1,y2+1},{n,m}));
	inc(ans,calc({1,1},{x2,y1-1},{x2+1,1},{n,y1-1},{x2+1,y1},{n,m}));
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