#include<bits/stdc++.h>
#define int long long
#define mod 998244353
#define pii pair<int,int>
#define mems(x,y) memset(x,y,sizeof x)
using namespace std;
const int maxn=600010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,a[maxn];
char s[maxn];
int len[maxn],fa[maxn];
int ch[maxn][26];
int p=1,cur=1;
int siz[maxn];
int mn[maxn],mx[maxn];
void insert(int c,int w){
	int nd=++cur;
	len[nd]=len[p]+1;siz[nd]=1;
	mn[nd]=mx[nd]=w;
	while(p&&!ch[p][c]){ch[p][c]=nd,p=fa[p];}
	if(!p){fa[p=nd]=1;return ;}
	int q=ch[p][c];
	if(len[p]+1==len[q])fa[nd]=q;
	else{
		int cl=++cur;
		mx[cl]=-inf,mn[cl]=inf;
		len[cl]=len[p]+1;fa[cl]=fa[q];
		memcpy(ch[cl],ch[q],sizeof(ch[cl]));
		fa[nd]=fa[q]=cl;
		while(p&&ch[p][c]==q)ch[p][c]=cl,p=fa[p];
	}
	p=nd;
}
int ans1[maxn],ans2[maxn];
vector<int> e[maxn];
void dfs(int u){
	if(!mx[u])mx[u]=-inf,mn[u]=inf;
	for(int v:e[u]){
		dfs(v);
		ans1[len[u]]+=siz[u]*siz[v];
		siz[u]+=siz[v];
		if(mx[u]!=-inf)ans2[len[u]]=max({ans2[len[u]],mx[u]*mx[v],mn[u]*mn[v]});
		mx[u]=max(mx[u],mx[v]),mn[u]=min(mn[u],mn[v]);
	}
}
void work(){
	n=read();
	scanf("%s",s+1);
	reverse(s+1,s+n+1);
	for(int i=1;i<=n;i++)a[i]=read();
	reverse(a+1,a+n+1);
	for(int i=1;i<=n;i++)insert(s[i]-'a',a[i]);
	for(int i=2;i<=cur;i++)e[fa[i]].push_back(i);
	for(int i=0;i<=n;i++)ans2[i]=-inf;
	dfs(1);
	for(int i=n-1;~i;i--)ans1[i]+=ans1[i+1],ans2[i]=max(ans2[i],ans2[i+1]);
	for(int i=0;i<n;i++)printf("%lld %lld\n",ans1[i],(ans1[i]==0?0:ans2[i]));
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
