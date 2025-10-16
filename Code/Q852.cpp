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
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n,ans;
int d[maxn],num[maxn];
vector<int> e[maxn];
void work(){
	n=read();ans=0;
	for(int i=1;i<=n;i++)e[i].clear(),d[i]=num[i]=0;
	for(int i=1;i<=n;i++){
		int u=read(),v=read();
		e[u].pb(v),e[v].pb(u);
		d[u]++,d[v]++;
	}
	queue<int> q;
	for(int i=1;i<=n;i++)if(d[i]==1)q.push(i),num[i]=1;
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int v:e[u]){
			if(d[v]>1){
				d[v]--;
				num[v]+=num[u];
				if(d[v]==1)q.push(v);
			}
		}
	}
	int s=0,c=0;for(int i=1;i<=n;i++)if(d[i]==2)s+=num[i],c++;
	ans=max(ans,s);
	if(c>=3)ans=max(ans,3);
	int mn=n;
	for(int i=1;i<=n;i++)if(d[i]==2)mn=min(mn,num[i]);
	ans=max(ans,s-mn+1);
	for(int u=1;u<=n;u++)if(d[u]==2){
		for(int v:e[u])if(d[v]==2){
			if(!num[u]&&!num[v])ans=max(ans,s+2);
		}
	}
	printf("%lld\n",ans);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}