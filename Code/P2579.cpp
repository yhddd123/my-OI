// Problem: P2579 [ZJOI2005] 沼泽鳄鱼
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P2579
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 10000
#define pii pair<int,int>
using namespace std;
const int maxn=55;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,s,t,k,q;
struct mat{
	int e[maxn][maxn];
	mat(){memset(e,0,sizeof(e));}
	mat operator*(const mat&tmp)const{
		mat res;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				for(int k=1;k<=n;k++)res.e[i][j]+=e[i][k]*tmp.e[k][j];
				res.e[i][j]%=mod;
			}
		}
		return res;
	}
}a[13],ans;
mat one(){
	mat res;
	for(int i=1;i<=n;i++)res.e[i][i]=1;
	return res;
}
mat ksm(mat a,int b){
	mat ans=one();
	while(b){
		if(b&1)ans=ans*a;
		a=a*a;
		b>>=1;
	}
	return ans;
}
void work(){
	n=read();m=read();s=read()+1;t=read()+1;k=read();
	for(int i=1;i<=m;i++){
		int u=read()+1,v=read()+1;
		for(int j=1;j<=12;j++)a[j].e[u][v]=a[j].e[v][u]=1;
	}
	q=read();
	while(q--){
		int t=read();
		for(int i=0;i<t;i++){
			int x=read()+1;
			for(int j=i;j<=12;j+=t){
				for(int k=1;k<=n;k++)a[j].e[k][x]=0;
			}
		}
	}
	a[0]=one();for(int i=1;i<=12;i++)a[0]=a[0]*a[i];
	// for(int i=0;i<=12;i++){
		// for(int j=1;j<=n;j++){
			// for(int k=1;k<=n;k++)cout<<a[i].e[j][k]<<" ";
			// cout<<"\n";
		// }
		// cout<<"\n";
	// }
	ans=ksm(a[0],k/12);
	for(int i=1;i<=k%12;i++)ans=ans*a[i];
	printf("%lld\n",ans.e[s][t]);
}

// \
444

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
