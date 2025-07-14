// Problem: P8522 [IOI2021] 地牢游戏
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P8522
// Memory Limit: 1 MB
// Time Limit: 4000 ms
// Written by yhm.
// Start codeing:2024-05-30 20:05:26
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
// #include "dungeons.h"
#define ll long long
using namespace std;
const int maxn=400010;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,s[maxn],p[maxn],w[maxn],l[maxn],lgw,lgn;
int to[22][19][maxn],val[22][19][maxn],lim[22][19][maxn];
int num[22][maxn];
ll ans[maxn];
void init(int N,vector<int> S,vector<int> P,vector<int> W,vector<int> L){
	n=N;for(int i=1;i<=n;i++)s[i]=S[i-1],p[i]=P[i-1],w[i]=W[i-1]+1,l[i]=L[i-1]+1;
	for(int i=n;i;i--)ans[i]=ans[w[i]]+s[i];
	lgw=21;lgn=18;
	for(int t=0;t<=lgw;t++){
		for(int i=1;i<=n;i++){
			if(s[i]<(1<<t+2))to[t][0][i]=w[i],val[t][0][i]=s[i],lim[t][0][i]=(1<<t+3)-1;
			else to[t][0][i]=l[i],val[t][0][i]=p[i],lim[t][0][i]=s[i]-1;
		}
		for(int j=1;j<=lgn;j++){
			for(int i=1;i<=n;i++)if(!num[t][i]){
				to[t][j][i]=to[t][j-1][to[t][j-1][i]];
				val[t][j][i]=val[t][j-1][i]+val[t][j-1][to[t][j-1][i]];
				lim[t][j][i]=min(lim[t][j-1][i],lim[t][j-1][to[t][j-1][i]]-val[t][j-1][i]);
				if(lim[t][j][i]<(1<<t+1))num[t][i]=j-1;
			}
		}
	}
	for(int t=0;t<=lgw;t++)for(int i=1;i<=n;i++)if(!num[t][i])num[t][i]=18;
}
ll simulate(int x,int Z){
	x++;ll z=Z;
	while((int)log2(z)<2&&x!=n+1){
		if(z>=s[x])z+=s[x],x=w[x];
		else z+=p[x],x=l[x];
	}
	while(x!=n+1&&(int)log2(z)-2<=lgw){
		int t=log2(z)-2;
		// cout<<t<<" "<<x<<" "<<z<<" "<<num[t][x]<<"\n";
		// for(int i=lgn;~i;i--)cout<<i<<" "<<lim[t][i][x]<<" "<<val[t][i][x]<<" "<<to[t][i][x]<<"\n";
		for(int i=num[t][x];~i;i--)if(z<=lim[t][i][x]){
			z+=val[t][i][x];
			x=to[t][i][x];
		}
		if(x==n+1)break;
		if(z>=s[x])z+=s[x],x=w[x];
		else z+=p[x],x=l[x];
		// cout<<t<<" "<<x<<" "<<z<<"\n";
	}
	// cout<<x<<" "<<z<<" "<<(int)log2(z)<<"\n";
	if(x!=n+1)z+=ans[x];
	return z;
}

// bool Med;
// int N,Q;
// signed main(){
	// cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	// N=read(),Q=read();
	// vector<int> S(N),P(N),W(N),L(N);
	// for(int i=0;i<N;i++)S[i]=read();
	// for(int i=0;i<N;i++)P[i]=read();
	// for(int i=0;i<N;i++)W[i]=read();
	// for(int i=0;i<N;i++)L[i]=read();
	// init(N,S,P,W,L);
	// for(int i=1;i<=Q;i++){
		// int x=read(),z=read();
		// printf("%lld\n",simulate(x,z));
	// }
// }