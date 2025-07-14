// Problem: P8997 [CEOI2022] Homework
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P8997
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-08-12 20:03:43
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=2000010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,ans;
char s[maxn<<2];
int st[maxn],tp;
int ls[maxn],rs[maxn],op[maxn],dp[maxn][2][2],idx;
void dfs(int u){
	if(op[u]==3){
		dp[u][0][0]=1,dp[u][1][1]=1;
		return ;
	}
	dfs(ls[u]),dfs(rs[u]);
	if(op[u]==1){
		dp[u][0][0]=min({dp[ls[u]][0][0]+dp[rs[u]][0][0],dp[ls[u]][0][0]+dp[rs[u]][1][0],dp[ls[u]][1][0]+dp[rs[u]][0][0]});
		dp[u][0][1]=min({dp[ls[u]][0][1]+dp[rs[u]][0][1],dp[ls[u]][0][1]+dp[rs[u]][1][1],dp[ls[u]][1][1]+dp[rs[u]][0][1]});
		dp[u][1][0]=dp[ls[u]][1][0]+dp[rs[u]][1][0];
		dp[u][1][1]=dp[ls[u]][1][1]+dp[rs[u]][1][1];
	}
	else{
		dp[u][0][0]=dp[ls[u]][0][0]+dp[rs[u]][0][0];
		dp[u][0][1]=dp[ls[u]][0][1]+dp[rs[u]][0][1];
		dp[u][1][0]=min({dp[ls[u]][1][0]+dp[rs[u]][1][0],dp[ls[u]][1][0]+dp[rs[u]][0][0],dp[ls[u]][0][0]+dp[rs[u]][1][0]});
		dp[u][1][1]=min({dp[ls[u]][1][1]+dp[rs[u]][1][1],dp[ls[u]][1][1]+dp[rs[u]][0][1],dp[ls[u]][0][1]+dp[rs[u]][1][1]});
	}
	// cout<<u<<" "<<op[u]<<" "<<dp[u][0][0]<<" "<<dp[u][0][1]<<" "<<dp[u][1][0]<<" "<<dp[u][1][1]<<"\n";
}
int f[maxn];
void calc(int u,int l,int r){
	if(op[u]==3){
		f[l+1]++,f[m-r+1]--;
		return ;
	}
	if(op[u]==1){
		calc(ls[u],l+dp[rs[u]][1][0],r+dp[rs[u]][1][1]),calc(rs[u],l+dp[ls[u]][1][0],r+dp[ls[u]][1][1]);
	}
	else{
		calc(ls[u],l+dp[rs[u]][0][0],r+dp[rs[u]][0][1]),calc(rs[u],l+dp[ls[u]][0][0],r+dp[ls[u]][0][1]);
	}
}
void work(){
	scanf("%s",s+1);n=strlen(s+1);
	for(int i=1;i<=n;i++){
		if(s[i]=='m'){
			if(s[i+1]=='i')st[++tp]=++idx,op[idx]=1;
			else st[++tp]=++idx,op[idx]=2;
			if(s[i-1]=='(')ls[st[tp-1]]=st[tp];
			if(s[i-1]==',')rs[st[tp-1]]=st[tp];
		}
		if(s[i]=='?'){
			op[++idx]=3;++m;
			if(s[i-1]=='(')ls[st[tp]]=idx;
			if(s[i-1]==',')rs[st[tp]]=idx;			
		}
		if(s[i]==')')tp--;
	}
	// for(int i=1;i<=idx;i++)cout<<op[i]<<" "<<ls[i]<<" "<<rs[i]<<"\n";
	dfs(1);calc(1,0,0);
	for(int i=1;i<=m;i++)f[i]+=f[i-1],ans+=f[i]>0;
	// for(int i=1;i<=m;i++)cout<<f[i]<<" ";cout<<"\n";
	printf("%lld\n",ans);
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
