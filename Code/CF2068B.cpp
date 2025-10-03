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
const int maxn=2030;
const int inf=1e9;
bool mbe;

int k,n,m=2025;
bool a[maxn][maxn];
void work(){
	k=read();
	if(!k)n=1;
	else if(k<=4186000000000){
		while(k){
			int p=n;
			while(n-p<=k){
				n++;
				if(n>2025)exit(0);
				for(int j=1,lst=0;j<=m;j++){
					int v=(n-p-1)*(j-lst-1);
					if(v>k)lst=j;
					else k-=v,a[n][j]=1;
				}
			}
			if(k){
				n++;
			}
		}
	}
	else{
		n=2023;
		for(int i=1;i<=n;i++){
			for(int j=1;j<m;j++){
				a[i][j]=1;
				k-=(i-1)*(j-1);
			}
		}
		if(k<n*(n-1)){
			for(int i=1;i<=n;i++){
				for(int j=1;j<=i;j++){
					a[j][i]=0;
					k+=(n-j)*(n+1-i);
					if(k>=n*(n-1))break;
				}
				for(int j=1;j<i;j++){
					a[i][j]=0;
					k+=(n-i)*(n+1-j);
					if(k>=n*(n-1))break;
				}
				if(k>=n*(n-1))break;
			}
		}
		int v1=0,v2=0;
		for(int a=1;a*n<=k;a++){
			if((k-a*n)%(n+1)==0){v1=a,v2=(k-a*n)/(n+1);break;}
		}
		while(v1+n+1<=v2-n)v1+=n+1,v2-=n;
		// cout<<v1<<" "<<v2<<"\n";
		for(int i=n+1,lst=n+2;i;i--){
			int v=(lst-i-1);
			if(v1>=v)a[n+1][i]=1,v1-=v;
			else lst=i;
		}
		for(int i=n,lst=n+1;i;i--){
			int v=(lst-i-1);
			if(v2>=v)a[i][n+2]=1,v2-=v;
			else lst=i;
		}
		// cout<<v1<<" "<<v2<<"\n";
		n++;
	}
	printf("%lld %lld\n",n,m);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)putchar(a[i][j]?'#':'.');puts("");
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