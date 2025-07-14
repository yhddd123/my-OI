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
const int maxn=85;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n;
char s[maxn][maxn],t[maxn][maxn];
int a[maxn][maxn],b[maxn][maxn],c[maxn][maxn],d[maxn][maxn];
int pre[maxn],nxt[maxn];
vector<pii> ans,res;
namespace sub1{
	int a[maxn][maxn],b[maxn][maxn],c[maxn][maxn],d[maxn][maxn];
	int tmp[maxn];
	vector<pii> ans,res;
	void sovle(){
		for(int i=1;i<=n;i++)if(!b[i][n]){
			bool fl=0;
			for(int j=1;j<=n;j++){
				for(int k=1;k<n;k++)if(b[j][k]){
					int u=j,v=k;
					while(u!=i){
						for(int l=1;l<=n;l++)tmp[pre[l]]=b[l][v];
						for(int l=1;l<=n;l++)b[l][v]=tmp[l];
						res.pb({2,v});
						u=pre[u];
					}
					while(v!=n){
						for(int l=1;l<=n;l++)tmp[pre[l]]=b[u][l];
						for(int l=1;l<=n;l++)b[u][l]=tmp[l];
						res.pb({1,u});
						v=pre[v];
					}
					fl=1;break;
				}
				if(fl)break;
			}
		}
		reverse(res.begin(),res.end());
		for(int i=1;i<=n;i++){
			for(int j=1;j<n;j++)if(a[i][j]!=b[i][j]){
				bool fl=0;
				for(int k=n;k>=1;k--){
					for(int l=n;l>=(k<i?n:(k==i?j+1:1));l--)if(a[k][l]==b[i][j]){
						int u=k,v=l,vv=j;
						while(v!=n){
							for(int l=1;l<=n;l++)tmp[nxt[l]]=a[u][l];
							for(int l=1;l<=n;l++)a[u][l]=tmp[l];
							ans.pb({1,u});
							v=nxt[v];
							if(i==k)vv=nxt[vv];
						}
						if(i==k){
							for(int l=1;l<=n;l++)tmp[nxt[l]]=a[l][v];
							for(int l=1;l<=n;l++)a[l][v]=tmp[l];
							ans.pb({2,v});
							u=nxt[u];
						}
						while(vv!=n){
							for(int l=1;l<=n;l++)tmp[nxt[l]]=a[i][l];
							for(int l=1;l<=n;l++)a[i][l]=tmp[l];
							ans.pb({1,i});
							vv=nxt[vv];
						}
						while(u!=i){
							for(int l=1;l<=n;l++)tmp[nxt[l]]=a[l][v];
							for(int l=1;l<=n;l++)a[l][v]=tmp[l];
							ans.pb({2,v});
							u=nxt[u];
						}
						while(v!=j){
							for(int l=1;l<=n;l++)tmp[nxt[l]]=a[u][l];
							for(int l=1;l<=n;l++)a[u][l]=tmp[l];
							ans.pb({1,u});
							v=nxt[v];
						}
						fl=1;break;
					}
					if(fl)break;
				}
			}
		}
		for(pii p:res)ans.pb(p);
	}
}
namespace sub2{
	int a[maxn][maxn],b[maxn][maxn],c[maxn][maxn],d[maxn][maxn];
	int tmp[maxn];
	vector<pii> ans,res;
	void sovle(){
		for(int i=1;i<=n;i++)if(!b[i][n]){
			bool fl=0;
			for(int j=1;j<=n;j++){
				for(int k=1;k<n;k++)if(b[j][k]){
					int u=j,v=k;
					while(u!=i){
						for(int l=1;l<=n;l++)tmp[pre[l]]=b[l][v];
						for(int l=1;l<=n;l++)b[l][v]=tmp[l];
						res.pb({2,v});
						u=pre[u];
					}
					while(v!=n){
						for(int l=1;l<=n;l++)tmp[pre[l]]=b[u][l];
						for(int l=1;l<=n;l++)b[u][l]=tmp[l];
						res.pb({1,u});
						v=pre[v];
					}
					fl=1;break;
				}
				if(fl)break;
			}
		}
		reverse(res.begin(),res.end());
		for(int i=1;i<=n;i++){
			bool fl=1;
			for(int j=1;j<n;j++)fl&=(a[i][j]==b[i][j]);
			if(fl)continue;
			for(int j=n;j;j--){
				for(int l=1;l<=n;l++)tmp[nxt[l]]=a[i][l];
				for(int l=1;l<=n;l++)a[i][l]=tmp[l];
				ans.pb({1,i});
				if(!a[i][n]){
					for(int l=1;l<=n;l++)tmp[nxt[l]]=a[l][n];
					for(int l=1;l<=n;l++)a[l][n]=tmp[l];
					ans.pb({2,n});
					while(i==n&&!a[i][n]){
						for(int l=1;l<=n;l++)tmp[nxt[l]]=a[l][n];
						for(int l=1;l<=n;l++)a[l][n]=tmp[l];
						ans.pb({2,n});
					}
				}
			}
			fl=1;
			for(int j=1;j<n;j++)fl&=(a[i][j]==b[i][j]);
			if(fl)continue;
			for(int j=n-1;j;j--){
				for(int l=1;l<=n;l++)tmp[nxt[l]]=a[i][l];
				for(int l=1;l<=n;l++)a[i][l]=tmp[l];
				ans.pb({1,i});
				if(a[i][n]!=b[i][j]){
					bool fl=0;
					for(int k=n;k>=1;k--)if(i!=k){
						for(int l=n;l>=(k<=i?n:1);l--)if(a[k][l]==b[i][j]){
							int u=k,v=l;
							while(v!=n){
								for(int l=1;l<=n;l++)tmp[nxt[l]]=a[u][l];
								for(int l=1;l<=n;l++)a[u][l]=tmp[l];
								ans.pb({1,u});
								v=nxt[v];
							}
							while(u!=i){
								for(int l=1;l<=n;l++)tmp[nxt[l]]=a[l][v];
								for(int l=1;l<=n;l++)a[l][v]=tmp[l];
								ans.pb({2,v});
								u=nxt[u];
							}
							fl=1;break;
						}
						if(fl)break;
					}
				}
			}
			for(int l=1;l<=n;l++)tmp[nxt[l]]=a[i][l];
			for(int l=1;l<=n;l++)a[i][l]=tmp[l];
			ans.pb({1,i});
		}
		for(pii p:res)ans.pb(p);
	}
}
void work(){
	n=read();
	for(int i=1;i<=n;i++)pre[i]=i-1,nxt[i]=i+1;
	pre[1]=n,nxt[n]=1;
	for(int i=1;i<=n;i++)scanf("%s",s[i]+1);
	for(int i=1;i<=n;i++)scanf("%s",t[i]+1);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)a[i][j]=s[i][j]=='.';
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)b[i][j]=t[i][j]=='.';
	}
	int num=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)num+=a[i][j];
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)num-=b[i][j];
	}
	if(num){
		puts("No");
		return ;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)num+=a[i][j];
	}
	if(num<n){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++)a[i][j]=1-a[i][j],b[i][j]=1-b[i][j];
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)c[i][j]=a[i][j];
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)d[i][j]=b[i][j];
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)sub1::a[i][j]=sub2::a[i][j]=a[i][j];
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)sub1::b[i][j]=sub2::b[i][j]=b[i][j];
	}
	sub1::sovle(),sub2::sovle();
	if(sub1::ans.size()<sub2::ans.size())ans=sub1::ans;
	else ans=sub2::ans;
	assert(ans.size()<=n*n*n);
	puts("Yes");printf("%lld\n",(int)ans.size());
	for(auto[fl,x]:ans)printf("%lld %lld\n",fl,x);
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