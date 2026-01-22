// Problem: AT_arc177_f [ARC177F] Two Airlines
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_arc177_f
// Memory Limit: 2048 MB
// Time Limit: 5000 ms
// Written by yhm.
// Start codeing:2026-01-22 16:43:42
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
const int maxn=60010;
const int maxm=22;
const int inf=1e9;
bool mbe;

int n,m;
int a[maxn],t[maxn][2];
char s[maxn];
int f[maxn][maxm][maxm][2],g[maxn][maxm][maxm][2];
inline void chkmn(int &u,int v){(u>v)&&(u=v);}
void work(){
	n=read();m=read();scanf("%s",s+1);
	for(int i=1;i<=n;i++)a[i]=s[i]=='1';
	for(int i=1;i<=m;i++){
		int p=read();char ch=getchar();
		while(ch!='A'&&ch!='J')ch=getchar();
		t[p][ch=='A']++;
	}
	mems(f,0x3f);
	f[0][0][0][0]=f[0][0][0][1]=0;
	for(int i=0;i<n;i++){
		for(int j=0;j<=20;j++){
			for(int k=0;k<=20;k++){
				for(int o=0;o<2;o++){
					int jj=max(0ll,j-t[i][0]),kk=max(0ll,k-t[i][1]);
					chkmn(g[i][jj][kk][o],f[i][j][k][o]);
				}
			}
		}
		for(int j=0;j<=20;j++){
			for(int k=0;k<=20;k++){
				for(int o=0;o<2;o++){
					chkmn(f[i+1][j][k][o],g[i][j][k][o]+(a[i+1]?j:k)+(a[i+1]!=o));
					chkmn(f[i+1][j][k][o^1],g[i][j][k][o]+(a[i+1]?j:k)+(a[i+1]==o));
				}
			}
		}
	}
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