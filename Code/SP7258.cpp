#include<bits/stdc++.h>
#define int long long
#define mod 998244353
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

int n,q,m;
char c[maxn];
int len[maxn],lnk[maxn],sum[maxn];
int a[maxn][26];
int p=1,cur=1;
void insert(int c){
	int nd=++cur;
	len[nd]=len[p]+1;
	while(p&&!a[p][c])a[p][c]=nd,p=lnk[p];
	if(!p){lnk[p=nd]=1;return ;}
	int q=a[p][c];
	if(len[p]+1==len[q])lnk[nd]=q;
	else{
		int cl=++cur;
		len[cl]=len[p]+1;lnk[cl]=lnk[q];
		memcpy(a[cl],a[q],sizeof(a[q]));
		lnk[q]=lnk[nd]=cl;
		while(p&&a[p][c]==q)a[p][c]=cl,p=lnk[p];
	}
	p=nd;
}
void sovle(int nd,int num){
	if(num<=1)return ;
	num--;
	for(int i=0;i<26;i++)if(a[nd][i]){
		int v=a[nd][i];
		if(num>sum[v])num-=sum[v];
		else{
			putchar(i+'a');
			sovle(v,num);
			return ;
		}
	}
}
int head[maxn],tot;
struct edgend{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
void dfs(int u){
	if(sum[u])return ;sum[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;dfs(v);
		sum[u]+=sum[v];
	}
}
void work(){
	scanf("%s",c+1);n=strlen(c+1);
	for(int i=1;i<=n;i++)insert(c[i]-'a');
	for(int i=1;i<=cur;i++){
		for(int j=0;j<26;j++)if(a[i][j])add(i,a[i][j]);
	}
	dfs(1);
	q=read();
	while(q--){
		m=read()+1;
		if(sum[1]<m)printf("-1\n");
		else sovle(1,m),printf("\n");
	}
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
