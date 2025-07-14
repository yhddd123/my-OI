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

int n,op,m;
vector<int> ans;
char c[maxn];
int len[maxn],lnk[maxn],siz[maxn],sum[maxn];
int a[maxn][26];
int p=1,cur=1;
void insert(int c){
	int nd=++cur;
	len[nd]=len[p]+1;siz[nd]=1;
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
	if(num<=siz[nd])return ;
	num-=siz[nd];
//	cout<<nd<<" "<<siz[nd]<<" "<<num<<"\n";
	for(int i=0;i<26;i++)if(a[nd][i]){
		int v=a[nd][i];
//		cout<<nd<<" "<<i<<"\n";
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
bool vis[maxn];
void dfs(int u,int *a){
	if(vis[u])return ;vis[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;dfs(v,a);
		a[u]+=a[v];
	}
}
void work(){
	scanf("%s",c+1);n=strlen(c+1);
	op=read();m=read();
	for(int i=1;i<=n;i++)insert(c[i]-'a');
	for(int i=2;i<=cur;i++)add(lnk[i],i);
	dfs(1,siz);
	mems(vis,false);mems(head,0);tot=0;
//	for(int i=1;i<=cur;i++)cout<<siz[i]<<" ";cout<<"\n";
	siz[1]=0;
	for(int i=2;i<=cur;i++)sum[i]=op==0?siz[i]=1:siz[i];
	for(int i=1;i<=cur;i++){
		for(int j=0;j<26;j++)if(a[i][j])add(i,a[i][j]);
	}
	dfs(1,sum);
//	for(int i=1;i<=cur;i++)cout<<sum[i]<<" ";cout<<"\n";
	if(sum[1]<m)printf("-1\n");
	else sovle(1,m);
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
