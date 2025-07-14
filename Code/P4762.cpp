#include<bits/stdc++.h>
#define mems(x,y) memset(x,y,sizeof x)
using namespace std;
const int maxn=100010;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n;
char s[maxn];
int len[maxn],fa[maxn];
int to[maxn];
int p,cur=1;
int a[maxn][26];
int get(int nd,int id){
	while(s[id-len[nd]-1]!=s[id])nd=fa[nd];
	return nd;
}
void insert(int c,int id){
	p=get(p,id);
	if(!a[p][c]){
		int nd=++cur;
		fa[nd]=a[get(fa[p],id)][c];
		a[p][c]=nd;
		len[nd]=len[p]+2;
		if(len[nd]<=2)to[nd]=fa[nd];
		else{
			int q=to[p];
			while((len[q]+2)*2>len[nd]||s[id]!=s[id-len[q]-1])q=fa[q];
			to[nd]=a[q][c];
		}
	}
	p=a[p][c];
}
int dp[maxn];
void clr(){
	while(cur>=0){
		len[cur]=fa[cur]=to[cur]=0;
		mems(a[cur],0);
		dp[cur]=0;
		cur--;
	}
	p=0,cur=1;
	fa[0]=1;len[1]=-1;
}
queue<int> q;
void work(){
	scanf("%s",s+1);n=strlen(s+1);clr();
	for(int i=1;i<=n;i++)insert(s[i]-'A',i);
	for(int i=2;i<=cur;i++)dp[i]=len[i];
//	for(int i=0;i<=cur;i++)for(int j=0;j<26;j++)if(a[i][j])cout<<i<<" "<<a[i][j]<<" "<<j<<"\n";
	dp[0]=1;q.push(0);int ans=n;
	while(!q.empty()){
		int u=q.front();q.pop();ans=min(ans,dp[u]+n-len[u]);
//		cerr<<u<<" ";
		for(int i=0;i<26;i++)if(a[u][i]){
			int v=a[u][i];
			dp[v]=dp[u]+1;
			int vv=to[v];
			dp[v]=min(dp[v],dp[vv]+1+len[v]/2-len[vv]);
			q.push(v);
		}
	}
	printf("%d\n",ans);
}

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=read();
	while(T--)work();
}
