#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1000000007
using namespace std;
const int maxn=200010;
const int inf=1e9;
const db eps=1e-9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,p,lim;
int d[maxn],id[maxn];
vector<int> e[maxn];
vector<int> a;
vector<bitset<maxn> > f;
bitset<maxn> nw;
map<int,int> g[maxn];

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();m=read();p=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		e[u].push_back(v);e[v].push_back(u);
		d[u]++;d[v]++;
	}
	sort(d+1,d+n+1);reverse(d+1,d+n+1);
	lim=d[min(n,(int)sqrt(n)*6)];
	a.push_back(0);f.push_back(nw);
	for(int i=1;i<=n;i++){
		if(e[i].size()>lim){
			a.push_back(i);
			id[i]=a.size()-1;
			nw&=0;
			for(int j:e[i])nw[j]=1;
			f.push_back(nw);
		}
		else{
			for(int j:e[i])g[i][j]=1;
		}
	}
	while(p--){
		int u=read(),v=read(),ans=0;
		if(id[u]&&id[v]){
			nw=f[id[u]]^(f[id[u]]&f[id[v]]);
			nw[u]=0;nw[v]=0;
			printf("%lld\n",(int)nw.count());
		}
		else if(id[u]){
			for(int j:e[v]){
				if(j==u||j==v||f[id[u]][j])++ans;
			}
			printf("%lld\n",(int)f[id[u]].count()-ans);
		}
		else if(id[v]){
			for(int j:e[u]){
				if(j!=u&&j!=v&&!f[id[v]][j])++ans;
			}
			printf("%lld\n",ans);
		}
		else{
			for(int j:e[u]){
				if(j!=u&&j!=v&&!g[v][j])++ans;
			}
			printf("%lld\n",ans);
		}
	}
}
