#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
typedef vector<int> VI;
typedef vector<VI> VII;
const int maxn=66,INF=1e9;
#define all(v) v.begin(),v.end()
#define sz(v) int(v.size())
#define fi first
#define se second
#define PB push_back
#define MP make_pair
#define lson o<<1,l,mid
#define rson o<<1|1,mid+1,r
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define ROF(i,a,b) for(int i=(a);i>=(b);i--)
#define MEM(x,v) memset(x,v,sizeof(x))
inline int read(){
	int x=0;
	bool f=0;char ch=getchar();
	while(ch<'0' || ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0' && ch<='9') x=x*10+ch-'0',ch=getchar();
	return f?-x:x;
}
int n,mod,f[66][66][66][66],g[66][66][66][66],ans[66][66];
int tf[66][66][66][66],tg[66][66][66][66];
inline void add(int &x,int y){
	if((x+=y)>=mod) x-=mod;
}
void solve(){
	n=read();
	mod=read();
	f[1][0][0][0]=1;
	g[0][1][1][0]=1;
	FOR(i,1,n){
		MEM(tf,0);MEM(tg,0);
		FOR(j,max(0,2*i-n),i) FOR(k,0,i) FOR(a,0,i) FOR(b,0,i){
			if(f[j][k][a][b]){
//				printf("f[%d][%d][%d][%d][%d]=%d\n",i,j,k,a,b,f[cur][j][k][a][b]);
				if(i==n) ans[a][b]=(ans[a][b]+f[j][k][a][b])%mod;
				else{
					if(i-j<=n-i-1) add(tf[j][k][a][b],f[j][k][a][b]);
					if(j+1<=i) add(tf[j+1][k][a][b],f[j][k][a][b]);
				}
			}
			if(g[j][k][a][b] && j<=i && i-j<=n-i){
//				printf("g[%d][%d][%d][%d][%d]=%d\n",i,j,k,a,b,g[cur][j][k][a][b]);
				if(i==n) ans[a][b]=(ans[a][b]+g[j][k][a][b])%mod;
				else{
					if(i-j<=n-i-1) add(tg[j][k][a][b],g[j][k][a][b]);
					if(j+1<=i){
						if(k==1) add(tf[j+1][i-j][a][b],g[j][k][a][b]);
						else add(tg[j+1][k-1][a][b],g[j][k][a][b]);
					}
				}
			}
		}
		if(i==n) continue;
		MEM(f,0);MEM(g,0);
		FOR(j,max(0,2*i-n+1),i) FOR(k,0,i+1) FOR(a,0,i) FOR(b,0,i){
			if(tf[j][k][a][b]){
//				printf("tf[%d][%d][%d][%d][%d]=%d\n",i,j,k,a,b,tf[j][k][a][b]);
				FOR(l,0,k-1){
					add(f[j+1][l][a][b+1],tf[j][k][a][b]);
				}
				FOR(l,k,i-j){
					add(f[j+1][l][a][b],tf[j][k][a][b]);
				}
				FOR(l,1,i-j+1){
					add(g[j][l][a+1][b],tf[j][k][a][b]);
				}
			}
			if(tg[j][k][a][b] && j<=i && i-j<=n-i-1){
//				printf("tg[%d][%d][%d][%d][%d]=%d\n",i,j,k,a,b,tg[j][k][a][b]);
				FOR(l,0,i-j){
					add(f[j+1][l][a][b+1],tg[j][k][a][b]);
				}
				FOR(l,1,k){
					add(g[j][l][a+1][b+1],tg[j][k][a][b]);
				}
				FOR(l,k+1,i-j+1){
					add(g[j][l][a+1][b],tg[j][k][a][b]);
				}
			}
		}
	}
	FOR(i,0,n-1){
		FOR(j,0,n-1) printf("%d ",ans[i][j]);
		puts("");
	}
}
int main(){
	int T=1;
	while(T--) solve();
}
