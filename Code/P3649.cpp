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

int n;
char c[maxn];
struct pam{
	int len[maxn],fa[maxn];
	int sum[maxn];
	int a[maxn][26];
	int p,cur=1;
	int getfail(int nd,int id){
		while(id-len[nd]-1<=0||c[id-len[nd]-1]!=c[id])nd=fa[nd];
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
		++sum[p];
	}
	void build(){
		fa[0]=1;len[1]=-1;
		for(int i=1;i<=n;i++)insert(c[i]-'a',i);
		for(int i=cur;i;i--)sum[fa[i]]+=sum[i];
		int ans=0;for(int i=2;i<=cur;i++)ans=max(ans,len[i]*sum[i]);
		printf("%lld\n",ans);
	}
}p;
void work(){
	scanf("%s",c+1);n=strlen(c+1);
	p.build();
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
