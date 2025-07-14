#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1000000007
#define pii pair<int,int>
#define mems(x,y) memset(x,y,sizeof x)
using namespace std;
const int maxn=50010;
const int inf=1e18;
const db eps=1e-8;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,l,r,b=50000;
bool vis[maxn];
char c[maxn];
namespace sub1{
	int dp[13][maxn][2][2];
	int a[13],len;
	int dfs(int dep,int num,bool pre,bool lim){
		if(dep==len+1)return !num;
		if(!pre&&~dp[dep][num][pre][lim])return dp[dep][num][pre][lim];
		int mx=lim?a[dep]:9;int res=0;
		for(int i=0;i<=mx;i++){
			if(pre&&!i)res+=dfs(dep+1,num*10%n,1,lim&&i==mx);
			else{
				if(!vis[i])continue;
				res+=dfs(dep+1,(num*10+i)%n,0,lim&&i==mx);
			}
		}
		return dp[dep][num][pre][lim]=res;
	}
	int calc(int x){
		int num=x;len=0;
		while(num){
			a[++len]=num%10;
			num/=10;
		}
		reverse(a+1,a+len+1);
		mems(dp,-1);
		return dfs(1,0,1,1);
	}
	void sovle(){
		printf("%lld\n",calc(r)-calc(l-1));
	}
}
namespace sub2{
	int ans;
	void sovle(){
		for(int i=(l+n-1)/n*n;i<=r/n*n;i+=n){
			int num=i;bool fl=1;
			while(num){
				if(!vis[num%10]){
					fl=0;
					break;
				}
				num/=10;
			}
			if(fl)++ans;
		}
		printf("%lld\n",ans);
	}
}
void work(){
	n=read();l=read();r=read();
	scanf("%s",c+1);int len=strlen(c+1);
	for(int i=1;i<=len;i++)vis[c[i]-'0']=1;
	if(n<=b)sub1::sovle();
	else sub2::sovle();
}

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
