#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
using namespace std;
const int maxn=1<<20;
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
int a[maxn],id[maxn],ans[maxn];
int siz[20][maxn];
void work(){
	n=read();m=read();
	for(int i=0;i<(1<<n);i++)a[i]=read(),id[i]=i;
	sort(id,id+(1<<n),[&](int u,int v){return a[u]<a[v];});
	for(int i=0;i<(1<<n);i++){
		int x=id[i];a[id[i]]--;ans[id[i]]=n;
		for(int j=0;j<n;j++){
			x>>=1;
			int num=(1<<j+1)-1-siz[j][x];
			// cout<<id[i]<<" "<<j<<" "<<siz[j][x]<<"\n";
			if(a[id[i]]-siz[j][x]<num||m<num){
				ans[id[i]]=j;
				break;
			}
		}
		x=id[i];
		for(int j=0;j<n;j++){
			x>>=1;
			siz[j][x]++;
		}
	}
	for(int i=0;i<(1<<n);i++)printf("%lld ",ans[i]);
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
