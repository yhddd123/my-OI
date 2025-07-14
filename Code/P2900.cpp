#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=50010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m;
struct nd{
	int x,y;
}e[maxn];
bool cmp(nd u,nd v){
	if(u.x==v.x)return u.y<v.y;
	return u.x<v.x;
}
int q[maxn],h=1,t;
int dp[maxn];
double X(int u){return 1.0*(-e[u+1].y);}
double Y(int u){return 1.0*dp[u];}
double slope(int u,int v){
	if(X(u)==X(v)){
		if(Y(u)<Y(v))return inf;
		return -inf;
	}
	return (double)((Y(u)-Y(v))/((X(u)-X(v))));
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();
	for(int i=1;i<=n;i++)e[i].x=read(),e[i].y=read();
	sort(e+1,e+n+1,cmp);
	for(int i=1;i<=n;i++){
		while(m&&e[i].y>=e[m].y)m--;
		e[++m]=e[i];
	}
	q[++t]=0;
	for(int i=1;i<=m;i++){
		while(h<t&&slope(q[h],q[h+1])<=e[i].x)h++;
		dp[i]=dp[q[h]]+e[q[h]+1].y*e[i].x;
		while(h<t&&slope(q[t-1],q[t])>=slope(q[t-1],i))t--;
		q[++t]=i;
	}
	printf("%lld\n",dp[m]);
}
