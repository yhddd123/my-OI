#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
#define db double
using namespace std;
const int maxn=200010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,l=3;
map<int,int> mp;
struct mat{
	int e[3][3];
	mat(){mems(e,0);}
	mat operator*(const mat&tmp)const{
		mat res;
		for(int i=0;i<l;i++){
			for(int j=0;j<l;j++){
				for(int k=0;k<l;k++)(res.e[i][j]+=e[i][k]*tmp.e[k][j])%=mod;
			}
		}
		return res;
	}
}a,b;
mat one(){
	mat res;
	for(int i=0;i<l;i++)res.e[i][i]=1;
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
int sovle(int m){
	if(mp[m])return mp[m];
	if(!m)return 1;
	if(m==1){
		int res=0;
		b.e[0][1]=b.e[0][2]=b.e[1][0]=b.e[2][1]=1;
		b=ksm(b,n);
		res=(b.e[0][0]+b.e[1][1]+b.e[2][2])%mod;
		return mp[1]=res;
	}
	if(m&1){
		return mp[m]=sovle(1)*sovle(m/2)%mod;
	}
	else{
		return mp[m]=(sovle(m/2)+sovle(m/2-1))%mod;
	}
}
void work(){
	n=read();m=read();
	printf("%lld\n",sovle(m));
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
