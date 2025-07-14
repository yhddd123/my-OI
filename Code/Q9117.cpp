#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
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

int n,m;
void work(){
	n=read();m=read();
	if(m==1){
		if(n==1)printf("Yes\n1\n");
		else puts("No");
		return ;
	}
	if((n*m*(n*m+1)/2)%n){puts("No");return ;}
	puts("Yes");
	if(!(m&1)){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if(j&1)printf("%lld ",(j-1)*n+i);
				else printf("%lld ",j*n-i+1);
			}
			puts("");
		}
	}
	else{
		for(int i=1;i<=n;i++){
			if(i<=n/2+1)printf("%lld %lld %lld ",i,n+n/2+i,3*n-(i-1)*2);
			else printf("%lld %lld %lld ",i,n+i-n/2-1,3*n-(i-n/2-1)*2+1);
			for(int j=4;j<=m;j++){
				if(j&1)printf("%lld ",(j-1)*n+i);
				else printf("%lld ",j*n-i+1);
			}
			puts("");
		}
	}

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
	
	T=read();
	while(T--)work();
}
