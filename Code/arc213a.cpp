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
const int maxn=30010;
const int inf=1e9;
bool mbe;

int n,m,ans;
int f[maxn];
int a[maxn][12],rnk[12],t[12];
void work(){
	n=read(),m=read();
	for(int i=1;i<=m;i++)a[0][i]=i;
	for(int i=1,mx=-inf;i<=n;i++){
		int c=read();
		for(int j=1;j<=m;j++)a[i][j]=read(),rnk[a[i][j]]=j;
		if(i-81>=0)mx=max(mx,f[i-81]);
		f[i]=mx;
		for(int j=max(0ll,i-80);j<i;j++){
			int num=0;
			for(int k=1;k<=m;k++){
				int v=rnk[a[j][k]];
				for(int l=v+1;l<=m;l++)num+=t[l];t[v]++;
				if(num>i-j)break;
			}
			if(num<=i-j)f[i]=max(f[i],f[j]+c);
			for(int i=1;i<=m;i++)t[i]=0;
		}
		ans=max(ans,f[i]);
		// cout<<i<<" "<<f[i]<<"\n";
	}
	printf("%lld\n",ans);
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