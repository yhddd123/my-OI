#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=255;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,cnt,ans;
int dp[maxn];
struct poi{
	int x,y;
}p[maxn];
struct nd{
	int id1,id2;
	double x,y;
}e[maxn*maxn];
bool cmp(nd u,nd v){return atan2(u.x,u.y)<atan2(v.x,v.y);}

signed main(){
	n=read();
	for(int i=1;i<=n;i++)p[i].x=read(),p[i].y=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i==j)continue;
			e[++cnt]={i,j,(double)p[i].x-p[j].x,(double)p[i].y-p[j].y};
		}
	}
	sort(e+1,e+cnt+1,cmp);
	for(int i=1;i<=n;i++){
		memset(dp,-0x3f,sizeof(dp));
		dp[i]=0;
		for(int j=1;j<=cnt;j++){
			dp[e[j].id2]=max(dp[e[j].id2],dp[e[j].id1]+1);
		}
		ans=max(ans,dp[i]);
	}
	printf("%lld\n",ans);
}
