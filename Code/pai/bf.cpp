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
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n,a[maxn],b[maxn],c[maxn],flag;
void dfs(int d){
	if(d==n+1){
		for(int i=1;i<=n;i++)c[i]=a[a[i]];
		if(!flag){
			flag=1;
			for(int i=1;i<=n;i++)b[i]=c[i];
		}
		else{
			bool fl=0;for(int i=1;i<=n;i++)if(b[i]!=c[i]){
				if(b[i]>c[i])fl=1;break;
			}
			if(fl){
				for(int i=1;i<=n;i++)b[i]=c[i];
			}
		}
		return ;
	}
	if(a[d]==-1){
		for(int i=1;i<=n;i++)a[d]=i,dfs(d+1);
		a[d]=-1;
	}
	else dfs(d+1);
}
void work(){
	n=read();flag=0;
	for(int i=1;i<=n;i++)a[i]=read();
	dfs(1);
	for(int i=1;i<=n;i++)cout<<b[i]<<" ";cout<<"\n";
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