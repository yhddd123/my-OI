#include<bits/stdc++.h>
#define int long long
#define mod 998244353
#define pii pair<int,int>
#define mems(x,y) memset(x,y,sizeof x)
using namespace std;
const int maxn=1000010;
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
char c[maxn];
int len[maxn],fa[maxn];
int ch[maxn][26];
int p=1,cur=1;
int siz[maxn];
void insert(int c){
	int nd=++cur;
	len[nd]=len[p]+1;
	siz[nd]=1;
	while(p&&!ch[p][c])ch[p][c]=nd,p=fa[p];
	if(!p){fa[p=nd]=1;return ;}
	int q=ch[p][c];
	if(len[p]+1==len[q])fa[nd]=q;
	else{
		int cl=++cur;
		len[cl]=len[p]+1;fa[cl]=fa[q];
		memcpy(ch[cl],ch[q],sizeof(ch[cl]));
		fa[q]=fa[nd]=cl;
		while(p&&ch[p][c]==q)ch[p][c]=cl,p=fa[p];
	}
	p=nd;
}
vector<int> g[maxn];
void dfs(int u){
	for(int v:g[u]){
		dfs(v);
		siz[u]+=siz[v];
	}
}
int num;
void work(){
	scanf("%s",c+1);n=strlen(c+1);
	for(int i=1;i<=n;i++)insert(c[i]-'a');
	for(int i=2;i<=cur;i++)g[fa[i]].push_back(i);
	dfs(1);
	for(int i=2;i<=cur;i++)num+=(len[i]-len[fa[i]])*siz[i]*(siz[i]-1)/2;
	printf("%lld\n",n*(n-1)*(n+1)/2-2*num);
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
