// Problem: P2292 [HNOI2004] L 语言
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P2292
// Memory Limit: 128 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-07-16 15:51:07
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=1010;
const int maxm=2000010;
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
int tree[maxn][26],fail[maxn],idx;
int g[maxn];
void insert(char *s){
	int n=strlen(s+1),nd=0;
	for(int i=1;i<=n;i++){
		int c=s[i]-'a';
		if(!tree[nd][c])tree[nd][c]=++idx;
		nd=tree[nd][c];
	}
	g[nd]|=(1<<n-1);
}
queue<int> q;
void build(){
	for(int i=0;i<26;i++)if(tree[0][i])q.push(tree[0][i]);
	while(!q.empty()){
		int u=q.front();q.pop();g[u]|=g[fail[u]];
		for(int i=0;i<26;i++){
			if(tree[u][i])fail[tree[u][i]]=tree[fail[u]][i],q.push(tree[u][i]);
			else tree[u][i]=tree[fail[u]][i];
		}
	}
}
char s[maxm];
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		insert(s);
	}
	build();
	for(int i=1;i<=m;i++){
		scanf("%s",s+1);n=strlen(s+1);
		int p=0,nw=1;
		for(int j=1,nd=0;j<=n;j++){
			int c=s[j]-'a';
			nd=tree[nd][c];
			if(nw&g[nd])nw=(nw<<1|1)&((1<<20)-1),p=j;
			else nw=(nw<<1)&((1<<20)-1);
		}
		printf("%lld\n",p);
	}
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
