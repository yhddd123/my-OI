#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=200010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n;
char c[maxn];
int tree[maxn][2],cnt;
int s[maxn],fail[maxn];
void insert(char *c){
	int len=strlen(c+1),nd=0;
	for(int i=1;i<=len;i++){
		if(!tree[nd][c[i]-'0'])tree[nd][c[i]-'0']=++cnt;
		nd=tree[nd][c[i]-'0'];
	}
	s[nd]++;
}
queue<int> q;
void build(){
	for(int i=0;i<=1;i++)if(tree[0][i])q.push(tree[0][i]);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=0;i<=1;i++){
			if(tree[u][i]){
				fail[tree[u][i]]=tree[fail[u]][i];
				if(s[fail[tree[u][i]]])s[tree[u][i]]=1;
				q.push(tree[u][i]);
			}
			else tree[u][i]=tree[fail[u]][i];
		}
	}
}
bool vis[maxn],bk[maxn];
void dfs(int u){
	vis[u]=bk[u]=1;
	for(int i=0;i<=1;i++){
		if(vis[tree[u][i]]){
			printf("TAK\n");
			exit(0);
		}
		if(s[tree[u][i]]||bk[tree[u][i]])continue;
		dfs(tree[u][i]);
	}
	vis[u]=0;
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();
	for(int i=1;i<=n;i++){
		scanf("%s",c+1);
		insert(c);
	}
	build();
//	for(int i=1;i<=cnt;i++)cout<<fail[i]<<" ";
//	cout<<"\n";
	dfs(0);
	printf("NIE\n");
}
