#include<bits/stdc++.h>
#define mod 1000000007ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=25010;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,k,a[maxn],ans;
map<int,int> mp[maxn];int id[maxn];
int f[maxn][27][2][27];
int ans1[maxn][27][2],ans2[maxn][27][2];
void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
void work(){
	n=read();k=read();
	for(int i=1;i<=n;i++)a[i]=read();
	mp[0][0]=++id[0];f[0][0][0][mp[0][0]]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=k;j++){
			for(int fl=0;fl<=1;fl++){
				for(auto [p,idd]:mp[i-1])if(f[i-1][j][fl][idd]){
					if(a[i]>a[p]){
						if(!mp[i][i])mp[i][i]=++id[i];
						inc(f[i][j][fl][mp[i][i]],f[i-1][j][fl][idd]);
					}
					else{
						if(!mp[i][p])mp[i][p]=++id[i];
						inc(f[i][j][fl^((a[p]-a[i])&1)][mp[i][p]],f[i-1][j][fl][idd]);
					}
					if(j<k){
						if(!mp[i][p])mp[i][p]=++id[i];
						inc(f[i][j+1][fl^(a[p]&1)][mp[i][p]],f[i-1][j][fl][idd]);
					}
				}
				ans1[i][j][fl]=f[i][j][fl][mp[i][i]];
			}
		}
	}
	for(int i=0;i<=n+1;i++)mp[i].clear(),id[i]=0;mems(f,0);
	mp[n+1][n+1]=++id[n+1];f[n+1][0][0][mp[n+1][n+1]]=1;
	for(int i=n;i;i--){
		for(int j=0;j<=k;j++){
			for(int fl=0;fl<=1;fl++){
				for(auto [p,idd]:mp[i+1])if(f[i+1][j][fl][idd]){
					if(a[i]>=a[p]){
						if(!mp[i][i])mp[i][i]=++id[i];
						inc(f[i][j][fl][mp[i][i]],f[i+1][j][fl][idd]);
					}
					else{
						if(!mp[i][p])mp[i][p]=++id[i];
						inc(f[i][j][fl^((a[p]-a[i])&1)][mp[i][p]],f[i+1][j][fl][idd]);
					}
					if(j<k){
						if(!mp[i][p])mp[i][p]=++id[i];
						inc(f[i][j+1][fl^(a[p]&1)][mp[i][p]],f[i+1][j][fl][idd]);
					}
				}
				ans2[i][j][fl]=f[i][j][fl][mp[i][i]];
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<=k;j++){
			inc(ans,(1ll*ans1[i][j][0]*ans2[i][k-j][0]%mod+1ll*ans1[i][j][1]*ans2[i][k-j][1]%mod)%mod);
			// cout<<i<<" "<<j<<" "<<ans1[i][j][0]<<" "<<ans2[i][k-j][0]<<" "<<ans1[i][j][1]<<" "<<ans2[i][k-j][1]<<"\n";
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
	
	// cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
