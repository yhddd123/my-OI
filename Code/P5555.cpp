#include<bits/stdc++.h>
#define int long long
#define mod 998244353
#define mems(x,y) memset(x,y,sizeof x)
using namespace std;
const int maxn=300010;
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
char c[maxn],t[maxn];
struct pam{
	char s[maxn];
	int n;
	int len[maxn],fa[maxn];
	int a[maxn][26];
	int p,cur=1;
	int getfail(int nd,int id){
		while(id-len[nd]-1<=0||s[id-len[nd]-1]!=s[id])nd=fa[nd];
		return nd;
	}
	void insert(int c,int id){
		p=getfail(p,id);
		if(!a[p][c]){
			int nd=++cur;
			fa[nd]=a[getfail(fa[p],id)][c];
			a[p][c]=nd;
			len[nd]=len[p]+2;
		}
		p=a[p][c];
	}
	void build(char *ss){
		fa[0]=1;len[1]=-1;n=strlen(ss+1);
		for(int i=1;i<=n;i++)s[i]=ss[i];
		for(int i=1;i<=n;i++)insert(s[i]-'a',i);
	}
}p1,p2;
int mx,num;
void dfs(int u,int v){
	if(p1.len[u]>mx)mx=p1.len[u],num=1;
	else if(p1.len[u]==mx)num++;
	for(int i=0;i<26;i++)if(p1.a[u][i]&&p2.a[v][i])dfs(p1.a[u][i],p2.a[v][i]);
}
void work(){
	scanf("%lld%lld%s%s",&n,&m,c+1,t+1);
	p1.build(c);p2.build(t);
	dfs(0,0);dfs(1,1);
	printf("%lld %lld\n",mx,num);
}

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
