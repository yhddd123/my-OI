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
const int maxn=200010;
const int maxk=64;
const int inf=1e9;
bool mbe;

int l;
struct mat{
	int e[maxk][maxk];
	mat(){memset(e,-0x3f,sizeof(e));}
}bas;
mat operator*(mat &u,mat &v){
	mat res;
	for(int i=0;i<l;i++){
		for(int k=0;k<l;k++){
			for(int j=0;j<l;j++)res.e[i][j]=max(res.e[i][j],u.e[i][k]+v.e[k][j]);
		}
	}
	return res;
}
mat one(){
	mat res;
	for(int i=0;i<l;i++)res.e[i][i]=0;
	return res;
}
mat qpow(mat a,int b){
	mat ans=one();
	while(b){
		if(b&1)ans=ans*a;
		a=a*a;
		b>>=1;
	}
	return ans;
}
int n,m,k,q;
int a[maxk],c[maxk];
void work(){
	n=read();m=read();k=read();q=read();l=1<<n;
	for(int i=0;i<n;i++)a[i]=read(),c[i]=read();
	bas=mat();
	for(int s=0;s<(1<<n);s++){
		for(int t=0;t<(1<<n);t++){
			int sum=0,val=0;
			for(int i=0;i<n;i++)if(t&(1<<i)){
				if(s&(1<<i))sum+=k;
				sum+=c[i],val+=a[i];
			}
			// cout<<s<<" "<<t<<" "<<sum<<" "<<val<<"\n";
			if(sum>m)continue;
			bas.e[t][s]=val;
		}
	}
	bas=qpow(bas,q);
	int ans=0;for(int s=0;s<(1<<n);s++)ans=max(ans,bas.e[s][0]);
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