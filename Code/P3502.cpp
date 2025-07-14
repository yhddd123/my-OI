// Problem: P3502 [POI2010] CHO-Hamsters
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3502
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
using namespace std;
const int maxn=210;
const int maxm=100010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m;
char c[maxm];
int a[maxn][maxm],len[maxn];
struct mat{
	int e[maxn][maxn];
	mat(){memset(e,0x3f,sizeof(e));}
	mat operator*(const mat&tmp)const{
		mat res;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				for(int k=1;k<=n;k++)res.e[i][j]=min(res.e[i][j],e[i][k]+tmp.e[k][j]);
			}
		}
		return res;
	}
}ans;
mat one(){
	mat res;
	for(int i=1;i<=n;i++)res.e[i][i]=len[i];
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
int val[26],bas,pw[maxm];
int calc(int id,int l,int r){return (a[id][r]-a[id][l-1]*pw[r-l+1]%mod+mod)%mod;}
void work(){
	n=read();m=read();
	srand(time(0));bas=rand()*rand()%mod;
	for(int i=0;i<26;i++)val[i]=rand()*rand()%bas;
	pw[0]=1;for(int i=1;i<maxm;i++)pw[i]=pw[i-1]*bas%mod;
	for(int i=1;i<=n;i++){
		scanf("%s",c+1);len[i]=strlen(c+1);
		for(int j=1;j<=len[i];j++)a[i][j]=(a[i][j-1]*bas+val[c[j]-'a'])%mod;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			ans.e[i][j]=len[j];
			for(int k=min(len[i],len[j])-1;k;k--)if(calc(i,len[i]-k+1,len[i])==calc(j,1,k)){
				ans.e[i][j]=len[j]-k;break;
			}
			// cout<<ans.e[i][j]<<" "<<i<<" "<<j<<"\n";
		}
		// cout<<"\n";
	}
	int res=inf;
	ans=ksm(ans,m-1);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)res=min(res,ans.e[i][j]);
	}
	printf("%lld\n",res);
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
