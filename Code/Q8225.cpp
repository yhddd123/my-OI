#include<bits/stdc++.h>
// #define int long long
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
const int maxn=85;
const int inf=1e9;
bool mbe;

int n,a[maxn],b[maxn];
bool f[maxn][maxn][maxn*maxn];
pii pre[maxn][maxn][maxn*maxn];
void dfs(int l,int r,int k,int s=0){
	if(l==r)return ;
	auto[p,v]=pre[l][r][k];
	b[p]=s+v;
	dfs(l,p,k+v*(r-l),s+v),dfs(p+1,r,k+v*(r-l),s+v);
}
int val[maxn][maxn];
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)f[i][i][a[i]]=1;
	for(int i=1;i<=n;i++){
		int mn=a[i];for(int j=i;j<=n;j++){
			mn=min(mn,a[j]);
			val[i][j]=mn;
		}
	}
	for(int len=2;len<=n;len++){
		for(int i=1,j=len;j<=n;i++,j++){
			cout<<i<<" "<<j<<" ";
			for(int k=0;k<=n*m;k++){
				for(int p=i;p<j;p++){
					for(int v=0;v<=m&&k+v*(j-i)<=val[i][j];v++){
						if(f[i][p][k+v*(j-i)]&&f[p+1][j][k+v*(j-i)]){
							f[i][j][k]=1;
							pre[i][j][k]={p,v};
							break;
						}
					}
					if(f[i][j][k])break;
				}
				cout<<f[i][j][k];
			}
			cout<<"\n";
		}
	}
	if(f[1][n][0]){
		puts("Yes");
		dfs(1,n,0);
		for(int i=1;i<n;i++)printf("%d ",b[i]);
	}
	else puts("No");
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