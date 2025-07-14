#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=500010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,res;
char c[maxn];
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){
	e[++tot]={head[u],v};
	head[u]=tot;
}
int f[maxn],ans[maxn],lst[maxn];
void dfs(int u,int fa){
	f[u]=fa;
	lst[u]=lst[fa];
	if(c[u]=='(')lst[u]=u;
	else{
		if(lst[u]){
			ans[u]=ans[f[lst[u]]]+1;
			lst[u]=lst[f[lst[u]]];
		}
	}
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v!=fa)dfs(v,u);
	}
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();
	scanf("%s",c+1);
	for(int i=2;i<=n;i++){
		int u=read();
		add(u,i);add(i,u);
	}
	dfs(1,0);
	for(int i=2;i<=n;i++)ans[i]+=ans[f[i]],res^=(ans[i]*i);
	printf("%lld\n",res);
}
