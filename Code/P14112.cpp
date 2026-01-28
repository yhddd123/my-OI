// Problem: P14112 [ZJCPC 2017] Sequence to Sequence
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P14112
// Memory Limit: 64 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2026-01-28 16:10:37
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
const int maxn=100010;
const int inf=1e9;
bool mbe;

int n,a[maxn],b[maxn];
int f[maxn][2][3];
inline void chkmx(int &u,int v){(u<v)&&(u=v);}
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();
	for(int i=1;i<=n;i++)if(!a[i]&&b[i]){puts("-1");return ;}
	for(int i=0;i<=n;i++)mems(f[i],-0x3f);
	f[0][0][1]=0;
	for(int i=1;i<=n;i++){
		for(int s=0;s<2;s++){
			for(int o=0;o<=2;o++){
				if(!b[i]){
					for(int r=0;r<2;r++){
						if(s+r<=1)chkmx(f[i][max(0ll,s+r)][o],f[i-1][s][o]+r*a[i]);
					}
				}
				else{
					for(int p=0;p<=2;p++){
						for(int q=-1;q<=1;q++)if(q==0||q+1!=o){
							if(s+q-p<=1)chkmx(f[i][max(0ll,s+q-p)][q==0?o:q+1],f[i-1][s][o]+p*(1-a[i])+q*(a[i]-b[i]));
						}
					}
				}
			}
		}
	}
	int ans=0;for(int s=0;s<2;s++){
		for(int o=0;o<=2;o++)ans=max(ans,f[n][s][o]);
	}
	printf("%lld\n",ans);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}