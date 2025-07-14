#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=500010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,q;
pii a[maxn];
bool vis[maxn];
int f[maxn];
int fd(int x){
	if(x==f[x])return x;
	return f[x]=fd(f[x]);
}
char s[maxn];

void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++)a[i]={read(),read()};
	q=read()-1;scanf("%[^\n]",s+1);int lst=0;
	while(q--){
		int k=read();
		scanf("%[^\n]",s+1);int len=strlen(s+1);
		int num=1;for(int i=1;i<=len;i++)num+=(s[i]==' ');
		k^=num;
		if(k==lst)puts("Disconnected");
		else lst=k,puts("Connected");
	}
	int len=strlen(s+1);
	for(int i=1,v=0;i<=len;i++){
		if(s[i]>='0'&&s[i]<='9')v=v*10+s[i]-'0';
		else vis[v^lst]=1,v=0;
		if(i==len)vis[v^lst]=1;
	}
	for(int i=1;i<=n;i++)f[i]=i;
	for(int i=1;i<=m;i++)if(!vis[i])f[fd(a[i].fi)]=fd(a[i].se);
	int num=0;for(int i=1;i<=n;i++)if(f[i]==i)++num;
	if(num==1)puts("Connected");
	else puts("Disconnected");
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
