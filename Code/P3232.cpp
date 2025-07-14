#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=510;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m;
int head[maxn],tot=1;
struct nd{
	int nxt,to;
}e[maxn*maxn];
void add(int u,int v){
	e[++tot]={head[u],v};
	head[u]=tot;
}
double d[maxn],f[maxn],g[maxn*maxn],ans;
double a[maxn][maxn],b[maxn];
void gas(int n){
	for(int i=1;i<=n;i++){
		int mxt=i;
		for(int j=i+1;j<=n;j++)if(fabs(a[j][i])>fabs(a[mxt][i]))mxt=j;
		for(int j=1;j<=n;j++)swap(a[i][j],a[mxt][j]);
		swap(b[i],b[mxt]);
		for(int j=1;j<=n;j++){
			if(i!=j){
				double d=a[j][i]/a[i][i];
				for(int k=i+1;k<=n;k++){
					a[j][k]-=d*a[i][k];
				}
				b[j]-=d*b[i];
			}
		}
	}
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int u,v;
		u=read();v=read();
		add(u,v);add(v,u);
		d[u]++;d[v]++;
	}
	for(int u=1;u<n;u++){
		a[u][u]=1.0;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(v!=n)a[u][v]=-1.0/d[v];
		}
	}
	b[1]=1.0;
	gas(n-1);
	for(int i=1;i<n;i++)f[i]=b[i]/a[i][i];
	for(int u=1;u<n;u++){
		for(int i=head[u];i;i=e[i].nxt){
			g[i/2]+=f[u]/d[u];
		}
	}
	sort(g+1,g+m+1);
	for(int i=1;i<=m;i++)ans+=g[i]*(m-i+1);
	printf("%.3lf\n",ans);
}
