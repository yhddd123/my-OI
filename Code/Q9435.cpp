#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=40;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m=49;
struct mat{
	int e[55][55];
	mat(){mems(e,0);}
	mat operator*(const mat&tmp)const{
		mat res;
		for(int i=0;i<m;i++){
			for(int j=0;j<m;j++){
				for(int k=0;k<m;k++)(res.e[i][j]+=e[i][k]*tmp.e[k][j])%=mod;
			}
		}
		return res;
	}
}a,b;
mat one(){
	mat res;
	for(int i=0;i<m;i++)res.e[i][i]=1;
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
mat pw[maxn];
mat mul(mat u,mat v){
	mat res;
	for(int j=0;j<m;j++){
		for(int k=0;k<m;k++)(res.e[0][j]+=u.e[0][k]*v.e[k][j])%=mod;
	}
	return res;
}
void work(){
	n=read();
	mat ans;ans.e[0][0]=1;
	for(int i=31;~i;i--)if(n&(1<<i))ans=mul(ans,pw[i]);
	printf("%lld\n",ans.e[0][48]);
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
	
	for(int i=0;i<=6;i++){
		for(int j=0;j<=6;j++){
			int num=52;
			if(i<6)pw[0].e[i*7+j][(i+1)*7+j]=1,num--;
			if(j<6)pw[0].e[i*7+j][i*7+j+1]=1,num--;
			pw[0].e[i*7+j][i*7+j]=num;
		}
	}
	for(int i=1;i<32;i++)pw[i]=pw[i-1]*pw[i-1];
	T=read();
	while(T--)work();
}
