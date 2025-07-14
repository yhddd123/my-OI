#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1000000007
#define pii pair<int,int>
using namespace std;
const int maxn=200010;
const int inf=1e18;
const db eps=1e-8;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n;
int bfn[maxn],tmp[maxn];
int dfn[maxn],rnk[maxn];
int f[maxn],g[maxn];
db ans=1;
void work(){
	n=read();
	for(int i=1;i<=n;i++)dfn[i]=read();
	for(int i=1;i<=n;i++)bfn[i]=read(),tmp[bfn[i]]=i,bfn[i]=i;
	for(int i=1;i<=n;i++)dfn[i]=tmp[dfn[i]],rnk[dfn[i]]=i;
	for(int i=1;i<=n;i++)f[i]=f[i-1]+(i==1||rnk[i]>rnk[i+1]);
	for(int i=1;i<n;i++){//[x,y)
		int x=dfn[i],y=dfn[i+1];
		if(f[y-1]-f[x-1]==1)g[x]++,g[y]--;
	}
	for(int i=1;i<n;i++){
		g[i]+=g[i-1];
		if(!g[i])ans+=0.5;
		else if(f[i]-f[i-1])ans++;
	}
	printf("%.3lf\n",ans);
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	T=1;
	while(T--)work();
}
