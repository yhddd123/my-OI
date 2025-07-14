// Problem: P5188 [COCI2009-2010#4] PALACINKE
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5188
// Memory Limit: 31 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-09-02 14:45:16
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 5557ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=410;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,t,ans;
struct mat{
	int e[maxn][maxn];
	mat(){
		for(int i=0;i<=m;i++){
			for(int j=0;j<=m;j++)e[i][j]=0;
		}
	}
	mat operator*(const mat&tmp)const{
		mat res;
		for(int i=0;i<=m;i++){
			for(int k=0;k<=m;k++){
				for(int j=0;j<=m;j++){
					(res.e[i][j]+=e[i][k]*tmp.e[k][j])%=mod;
				}
			}
		}
		return res;
	}
};
mat one(){
	mat res;
	for(int i=0;i<=m;i++)res.e[i][i]=1;
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
int e[25][25],to[maxn];
char op[6];
void work(){
	n=read();m=read();
	to[(int)'B']=0,to[(int)'J']=1,to[(int)'M']=2,to[(int)'P']=3;
	for(int i=1;i<=m;i++){
		int u=read()-1,v=read()-1;scanf("%s",op+1);
		for(int j=1;j<=strlen(op+1);j++)e[u][v]|=(1<<to[op[j]]);
		// cout<<u<<" "<<v<<" "<<e[u][v]<<"\n";
	}
	t=read();
	for(int s=0;s<16;s++){
		mat bas,mul;
		mul.e[0][0]=1;
		for(int i=0;i<n;i++){
			bas.e[i+n][i]++;
			for(int j=0;j<n;j++)if(e[i][j]){
				bas.e[i][j]++;
				if(!(e[i][j]&s))bas.e[i][j+n]++;
			}
		}
		m=n<<1;
		bas.e[0][m]++,bas.e[m][m]++;
		mul=mul*ksm(bas,t+1);
		ans+=mul.e[0][m]*((__builtin_popcount(s)&1)?-1:1);
		// cout<<s<<" "<<mul.e[0][m]<<" "<<ans<<"\n";
	}
	ans%=mod,ans+=mod,ans%=mod;
	printf("%lld\n",ans);
}

// \
444

bool Med;
int T;
signed main(){
	// freopen("cyb.in","r",stdin);
	// freopen("cyb.out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
