#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
#define db double
using namespace std;
const int maxn=400010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,k;
vector<vector<int>> ans;
struct nd{
	int l,r,fl;
}a[maxn],b[maxn];
bool vis[maxn];
void work(){
	n=read();m=read();k=read();
	ans.resize(n+2);
	for(int i=0;i<=n+1;i++)ans.resize(m+2);
	if(n==1){
		while(k--){
			int u=read(),v=read(),x=read(),y=read(),fl=read();
			if(v!=y&&v!=(y^1)&&fl){puts("-1");return ;}
			if((v==y||v==(y^1))&&!fl){puts("-1");return ;}
		}
		for(int i=1;i<=m;i++){
			if(i&1)putchar('R');
			else putchar('L');
		}
		return ;
	}
	if(m==1){
		while(k--){
			int u=read(),v=read(),x=read(),y=read(),fl=read();
			if(u!=x&&u!=(x^1)&&fl){puts("-1");return ;}
			if((u==x||u==(x^1))&&!fl){puts("-1");return ;}
		}
		for(int i=1;i<=n;i++){
			if(i&1)puts("D");
			else puts("U");
		}
		return ;
	}
	for(int i=1;i<=k;i++){
		int u=read(),v=read(),x=read(),y=read(),fl=read();
		a[i]={u,x,fl};b[i]={v,y,fl};
	}
	if(n==2&&m==2){
		bool fl=1;
		for(int i=1;i<=k;i++){
			if(a[i].l!=a[i].r&&a[i].fl)fl=0;
			if(a[i].l==a[i].r&&!a[i].fl)fl=0;
		}
		if(fl){
			printf("DD\nUU\n");
			return ;
		}
		fl=1;
		for(int i=1;i<=k;i++){
			if(b[i].l!=a[i].r&&a[i].fl)fl=0;
			if(b[i].l==a[i].r&&!a[i].fl)fl=0;
		}
		if(fl){
			printf("RR\nLL\n");
			return ;
		}
		puts("-1");
		return ;
	}
	bool fl=1;
	for(int i=1;i<=k;i++)fl&=a[i].fl;
	if(fl){
		if(!(n&1)){
			
		}
		return ;
	}
	fl=1;
	sort(a+1,a+k+1,[&](nd u,nd v){return u.r<v.r||(u.r==v.r&&u.l<v.l)||(u.r==v.r&&u.l==v.l&&u.fl<v.fl);});
	for(int i=1;i<=n;i++){
		
	}
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
