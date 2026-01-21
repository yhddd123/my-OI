// Problem: AT_agc061_e [AGC061E] Increment or XOR
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_agc061_e
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2026-01-21 19:34:54
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
const int maxn=8;
const int maxm=40;
const int inf=1e18;
bool mbe;

int n,x,y,c;
int a[maxn],b[maxn],val[1<<maxn];
int f[maxm+1][1<<maxn][2][2];
int dis[1<<maxn];
bool vis[1<<maxn];
inline void chkmn(int &u,int v){(u>v)&&(u=v);}
void work(){
	n=read();x=read();y=read();c=read();
	for(int i=0;i<n;i++)a[i]=read(),b[i]=read();
	for(int s=1;s<(1<<n);s++){
		int k=__lg(s);
		val[s]=val[s^(1<<k)]^a[k];
	}
	mems(f,0x3f);
	for(int s=0;s<(1<<n);s++){
		int sum=0;for(int i=0;i<n;i++)if(s&(1<<i))sum+=b[i];
		for(int o=0;o<2;o++)f[0][s][o][0]=sum,f[0][s][o][1]=c+sum;
	}
	for(int i=0;i<40;i++){
		int op1[2]={(x>>i)&1,0},op2[2]={(y>>i)&1,1};
		// for(int s=0;s<(1<<n);s++){
			// for(int o1:{0,1})for(int o2:{0,1}){
				// cout<<i<<" "<<s<<" "<<o1<<" "<<o2<<" "<<f[i][s][o1][o2]<<"\n";
			// }
		// }
		for(int s=0;s<(1<<n);s++){
			for(int o1:{0,1})for(int o2:{0,1}){
				if(op1[o1]^((val[s]>>i)&1)==op2[o2])chkmn(f[i+1][s][o1][o2],f[i][s][o1][o2]);
			}
		}
		for(int o=0;o<2;o++){
			for(int s=0;s<(1<<n);s++)dis[s]=inf,vis[s]=0;
			for(int s=0;s<(1<<n);s++)if(((val[s]>>i)&1)==op1[o])dis[s]=f[i][s][o][1];
			while(1){
				int u=-1;for(int s=0;s<(1<<n);s++)if(!vis[s]&&(u==-1||dis[s]<dis[u]))u=s;
				if(u==-1||dis[u]>=inf)break;
				vis[u]=1;
				for(int v=0;v<(1<<n);v++)if(((val[v]>>i)&1)==1)chkmn(dis[u^v],dis[u]+f[i][v][1][1]);
				for(int v=0;v<(1<<n);v++){
					for(int o2:{0,1})if(((val[v]>>i)&1)^1==op2[o2])chkmn(f[i+1][u^v][o][o2],dis[u]+f[i][v][1][o2]);
				}
			}
			// for(int s=0;s<(1<<n);s++)cout<<s<<" "<<dis[s]<<"\n";
		}
	}
	int ans=inf;for(int s=0;s<(1<<n);s++)chkmn(ans,f[40][s][0][0]);
	if(ans>=inf)ans=-1;
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