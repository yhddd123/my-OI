// Problem: P10220 [省选联考 2024] 迷宫守卫
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10220
// Memory Limit: 512 MB
// Time Limit: 500000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=150010;
inline ll read(){
	ll x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-'0');ch=getchar();}
	return x*fl;
}
const ll inf=2e18;

int n,m;ll k;
ll a[maxn];int b[maxn];
vector<int> val[maxn];
int pre[maxn],suf[maxn];
ll dp[17][maxn];int to[17][maxn];
short flag[17][maxn];
void dfs(int u){
	if(u>=m)return ;
	vector<int>().swap(val[u]);
	int ls=u<<1,rs=u<<1|1,dep=31^__builtin_clz(u);
	dfs(ls),dfs(rs);
	int hl=0,hr=0;
	while(hl<val[ls].size()&&hr<val[rs].size()){
		if(val[ls][hl]>val[rs][hr])val[u].push_back(val[ls][hl]),hl++;
		else val[u].push_back(val[rs][hr]),hr++;
	}
	while(hl<val[ls].size())val[u].push_back(val[ls][hl]),hl++;
	while(hr<val[rs].size())val[u].push_back(val[rs][hr]),hr++;
	pre[0]=val[rs][0];
	for(int i=1;i<val[rs].size();i++){
		if(dp[dep+1][val[rs][i]]<dp[dep+1][pre[i-1]])pre[i]=val[rs][i];
		else pre[i]=pre[i-1];
	}
	suf[val[rs].size()-1]=val[rs].back();
	for(int i=val[rs].size()-2;~i;i--){
		if(dp[dep+1][val[rs][i]]<dp[dep+1][suf[i+1]])suf[i]=val[rs][i];
		else suf[i]=suf[i+1];
	}
	for(int i=0,j=-1;i<val[ls].size();i++)if(dp[dep+1][val[ls][i]]<=k){
		while(j+1<val[rs].size()&&val[rs][j+1]>val[ls][i])j++;
		if(~j){
			ll v=dp[dep+1][val[ls][i]]+dp[dep+1][pre[j]];
			if(dp[dep][val[ls][i]]>v){
				dp[dep][val[ls][i]]=v;
				to[dep][val[ls][i]]=pre[j];
			}
		}
		if(j!=val[rs].size()-1){
			ll v=dp[dep+1][val[ls][i]]+a[u];
			if(dp[dep][val[ls][i]]>v){
				dp[dep][val[ls][i]]=v;
				to[dep][val[ls][i]]=suf[j+1];
				flag[dep][val[ls][i]]=2;
			}
		}
	}
	pre[0]=val[ls][0];
	for(int i=1;i<val[ls].size();i++){
		if(dp[dep+1][val[ls][i]]<dp[dep+1][pre[i-1]])pre[i]=val[ls][i];
		else pre[i]=pre[i-1];
	}
	for(int i=0,j=-1;i<val[rs].size();i++)if(dp[dep+1][val[rs][i]]<=k){
		while(j+1<val[ls].size()&&val[ls][j+1]>val[rs][i])j++;
		if(~j){
			ll v=dp[dep+1][pre[j]]+dp[dep+1][val[rs][i]];
			if(dp[dep][val[rs][i]]>v){
				dp[dep][val[rs][i]]=v;
				to[dep][val[rs][i]]=pre[j];
				flag[dep][val[rs][i]]=1;
			}
		}
	}
}
ll res;
int ans[maxn],tp;
void dfs1(int u,int num){
	if(u>=m){ans[++tp]=b[u];return ;}
	int ls=u<<1,rs=u<<1|1,dep=31^__builtin_clz(u);
	if(flag[dep][num]==1){
		dfs1(rs,num);
		for(int i:val[ls])if(to[dep][num]<=i){
			if(dp[dep+1][i]-dp[dep+1][to[dep][num]]<=res){
				res-=(dp[dep+1][i]-dp[dep+1][to[dep][num]]);
				dfs1(ls,i);
				break;
			}
		}
	}
	else if(!flag[dep][num]){
		dfs1(ls,num);
		for(int i:val[rs])if(to[dep][num]<=i){
			if(dp[dep+1][i]-dp[dep+1][to[dep][num]]<=res){
				res-=(dp[dep+1][i]-dp[dep+1][to[dep][num]]);
				dfs1(rs,i);
				break;
			}
		}
	} 
	else{
		dfs1(ls,num);
		for(int i:val[rs])if(num<i){
			if(dp[dep+1][i]-a[u]<=res){
				res-=(dp[dep+1][i]-a[u]);
				dfs1(rs,i);
				return ;
			}
		}
		for(int i:val[rs])if(to[dep][num]<=i){
			if(dp[dep+1][i]<=res){
				res-=(dp[dep+1][i]);
				dfs1(rs,i);
				break;
			}
		}
	}
}
void sovle(){
	n=read(),m=1<<n,k=read();
	for(int i=1;i<m;i++)a[i]=read();
	for(int i=m;i<=m*2-1;i++)b[i]=read();
	for(int i=0;i<=n;i++)for(int j=1;j<=m;j++)dp[i][j]=inf,flag[i][j]=0;
	for(int i=m;i<m*2;i++){
		dp[n][b[i]]=0;
		vector<int>().swap(val[i]);
		val[i].push_back(b[i]);
	}
	dfs(1);
	for(int i=m;i;i--)if(dp[0][i]<=k){
		res=k-dp[0][i];
		dfs1(1,i);
		printf("%lld",ans[1]);
		for(int j=2;j<=tp;j++)printf(" %lld",ans[j]);
		printf("\n");tp=0;
		return ;
	}
}

int T;
signed main(){
	// freopen("maze.in","r",stdin);
	// freopen("maze.out","w",stdout);
	
	T=read();
	while(T--)sovle();
} 