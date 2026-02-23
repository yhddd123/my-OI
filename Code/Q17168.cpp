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
const int maxn=500010;
const int inf=1e9;
bool mbe;

int n,m,a[maxn],b[maxn];
int fa[maxn],d[maxn];
void gettree(int *a){
	for(int i=1;i<=n-2;i++)d[a[i]]++;a[n-1]=n,d[n]++;
	int nn=0;for(int i=1;i<n;i++)if(d[i]==0){
		fa[i]=a[++nn],d[fa[i]]--;
		int u=fa[i];
		while(d[u]==0&&u<i){
			fa[u]=a[++nn];d[fa[u]]--;
			u=fa[u];
		}
	}
}
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	if(n==1){
		if(a[1]<=0)puts("YES");
		else puts("NO");
		return ;
	}
	for(int i=1;i<=n;i++){
		if(a[i]==0)a[i]=m-1;
		else if(a[i]>0)a[i]--;
	}
	int s=n-2;for(int i=1;i<=n;i++)if(~a[i])s-=a[i];
	int p=0;for(int i=1;i<=n;i++)if(a[i]==-1)p=i;
	if(s<0){puts("NO");return ;}
	if(!p){
		if(s%m){puts("NO");return ;}
		p=1;
	}
	for(int i=1;i<=n;i++)if(a[i]==-1)a[i]=0;
	a[p]+=s;
	for(int i=1,k=0;i<=n;i++){
		for(int j=1;j<=a[i];j++)b[++k]=i;
	}
	gettree(b);
	puts("YES");
	for(int i=1;i<n;i++)printf("%d %d\n",fa[i],i);	
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}