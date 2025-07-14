#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 998244353
#define pii pair<int,int>
#define mems(x,y) memset(x,y,sizeof x)
using namespace std;
const int maxn=2000010;
const int inf=1e18;
const db eps=1e-8;
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
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
int siz[maxn];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
struct sam{
	int p=1,cur=1;
	struct nd{
		int len,lnk;
		map<int,int> ch;
//		int ch[26];
		nd(int u=0,int v=0){
			len=u,lnk=v;
			ch.clear();
//			mems(ch,0);
		}
	}a[maxn];
	void insert(int c){
		int nd=++cur;
		a[nd].len=a[p].len+1;
		siz[nd]=1;
		while(p&&!a[p].ch[c])a[p].ch[c]=nd,p=a[p].lnk;
		if(!p){a[p=nd].lnk=1;return ;}
		int q=a[p].ch[c];
		if(a[p].len+1==a[q].len)a[nd].lnk=q;
		else{
			int cl=++cur;a[cl]=a[q];
			a[cl].len=a[p].len+1;
			a[q].lnk=a[nd].lnk=cl;
			while(p&&a[p].ch[c]==q)a[p].ch[c]=cl,p=a[p].lnk;
		}
		p=nd;
//		cout<<cur<<" "<<p<<"\n";
	}
	void dfs(int u){
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			dfs(v);
			siz[u]+=siz[v];
		}
	}
	int calc(){
		int res=0;
		for(int i=2;i<=cur;i++)add(a[i].lnk,i);
		dfs(1);
		for(int i=2;i<=cur;i++)if(siz[i]>1)res=max(res,siz[i]*a[i].len);
		return res;
	}
}s;
void work(){
	scanf("%s",c+1);n=strlen(c+1);
	for(int i=1;i<=n;i++)s.insert(c[i]-'a');
	printf("%lld\n",s.calc());
}

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
