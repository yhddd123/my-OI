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

int n,m,a[maxn],b[maxn];
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=a[i+n]=read();
	for(int i=1;i<=m;i++)b[i]=read();
	for(int i=1;i<=n;i++)if(a[i]==b[1]){
		bool fl=1;
		for(int j=1;j<=m;j++)if(a[i+j-1]!=b[j])fl=0;
		if(fl){puts("1");return ;}
	}
	reverse(a+1,a+2*n+1);
	for(int i=1;i<=n;i++)if(a[i]==b[1]){
		bool fl=1;
		for(int j=1;j<=m;j++)if(a[i+j-1]!=b[j])fl=0;
		if(fl){puts("1");return ;}
	}
	puts("0");
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
