#include<bits/stdc++.h>
#define int long long
#define mod 998244353
#define mems(x,y) memset(x,y,sizeof x)
using namespace std;
const int maxn=200010;
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
		if(len[fa[nd]]<=len[nd]>>1)to[nd]=fa[nd];
		else{
			int q=to[p];
			while(len[q]+2>len[nd]>>1||s[id]!=s[id-len[q]-1])q=fa[q];
			to[nd]=a[q][c];
		}
	}
	p=a[p][c];
}
void work(){
	n=read();
	scanf("%s",s+1);
	fa[0]=1;len[1]=-1;
	for(int i=1;i<=n;i++)insert(s[i]-'a',i);
	int ans=0;for(int i=2;i<=cur;i++)if(len[i]%4==0&&len[to[i]]==len[i]>>1)ans=max(ans,len[i]);
	printf("%lld\n",ans);
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
