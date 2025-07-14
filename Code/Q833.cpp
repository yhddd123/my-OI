#include<bits/stdc++.h>
#define int long long
#define mod 998244353
using namespace std;
const int maxn=3010;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,ans,num;
char c[maxn];
bool a[maxn][maxn],f[maxn][maxn],g[maxn][maxn];
vector<int> p[maxn<<1];
void work(){
	n=read(),m=read();
	for(int i=1;i<=n;i++){
		scanf("%s",c+1);
		for(int j=1;j<=m;j++)a[i][j]=(c[j]=='.'),num+=(c[j]=='.');
	}
	f[0][1]=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)if(a[i][j])f[i][j]=f[i-1][j]|f[i][j-1];
	}
	if(!f[n][m]){printf("%lld\n",num*(num-1)/2);return ;}
	g[n+1][m]=1;
	for(int i=n;i;i--){
		for(int j=m;j;j--)if(a[i][j])g[i][j]=g[i+1][j]|g[i][j+1];
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(f[i][j]&&g[i][j])p[i+j].push_back(i);
			else a[i][j]=0;
		}
	}
	for(int i=2;i<=n+m;i++){
		if(p[i].size()==1)ans+=--num;
		else if(p[i].size()>1){
			ans+=(p[i].size()==2);
			int ly=p[i][1],ry=p[i].back();
			for(int j=i+1;j<=n+m;j++){
				if(!a[ly][j-ly])ly++;
				if(a[ry+1][j-ry-1])ry++;
				if(ly==ry&&p[j].size()>1)++ans;
			}
			ly=p[i][0],ry=p[i][p[i].size()-2];
			for(int j=i+1;j<=n+m;j++){
				if(!a[ly][j-ly])ly++;
				if(a[ry+1][j-ry-1])ry++;
				if(ly==ry&&p[j].size()>1)++ans;
			}
		}
	}
	printf("%lld\n",ans);
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
