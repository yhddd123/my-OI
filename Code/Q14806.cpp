#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=1010;
const int inf=1e9;
bool mbe;

int n,q,ans;
struct bij{
	int f[maxn];
	void init(){
		for(int i=1;i<=n;i++)f[i]=i;
	}
	int fd(int x){
		if(f[x]==x)return x;
		return f[x]=fd(f[x]);
	}
	void merge(int u,int v){
		f[fd(u)]=fd(v);
	}
}a[1<<12];
void dfs(int w,int u,int v){
	if(a[w].fd(u)==a[w].fd(v))return ;
	a[w].merge(u,v);
	for(int i=0;i<12;i++)if(w&(1<<i))dfs(w^(1<<i),u,v);
}
void work(){
	n=read();q=read();ans=0;
	for(int s=0;s<(1<<12);s++)a[s].init();
	while(q--){
		char op[5];scanf("%s",op);
		if(op[0]=='+'){
			int u=read(),v=read(),w=read();
			dfs(w,u,v);
		}
		else{
			int u=read(),v=read(),s=0;
			if(a[0].fd(u)!=a[0].fd(v))ans--;
			else{
				for(int i=11;~i;i--)if(a[s|(1<<i)].fd(u)==a[s|(1<<i)].fd(v))s|=1<<i;
				ans+=s;
			}
		}
	}
	printf("%lld\n",ans);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}