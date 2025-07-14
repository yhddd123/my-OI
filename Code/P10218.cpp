// Problem: P10218 [省选联考 2024] 魔法手杖
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10218
// Memory Limit: 1 MB
// Time Limit: 1500 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353
using namespace std;
inline __int128 read(){
	__int128 x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-'0');ch=getchar();}
	return x*fl;
}
void write(__int128 x){
	// print a __int128 variable
	if(x < 0){putchar('-'); x = -x;}
	if(x > 9)write(x / 10);
	putchar(x % 10 + '0');
}
const int maxn=100010;

int T,id;
__int128 pw[125];
int n,m,k;
__int128 a[maxn];int b[maxn];
int tree[maxn<<7][2],idx;
__int128 mn[maxn<<7];int sum[maxn<<7];
__int128 ans;
#define ls tree[u][0]
#define rs tree[u][1]
void dfs(int u,int dep,int res,__int128 x,__int128 y,__int128 z){
	if(dep==-1){
		ans=max(ans,z);
		return ;
	}
	if(!u)return ;
	bool fl=0;
	if(sum[ls]<=res){
		if((x|(pw[dep]-1))+min(y,mn[ls])<(z|pw[dep])){
			if(min(y,mn[ls])<pw[k])ans=max(ans,(x|(pw[dep]-1))+min(y,mn[ls]));
		}
		else dfs(rs,dep-1,res-sum[ls],x,min(y,mn[ls]),z|pw[dep]),fl=1;
	}
	if(sum[rs]<=res){
		if((x|(pw[dep+1]-1))+min(y,mn[rs])<(z|pw[dep])){
			if(min(y,mn[rs])<pw[k])ans=max(ans,(x|(pw[dep+1]-1))+min(y,mn[ls]));
		}
		else dfs(ls,dep-1,res-sum[rs],x|pw[dep],min(y,mn[rs]),z|pw[dep]),fl=1;
	}
	if(!fl){
		if((x|(pw[dep]-1))+y<z){
			if(y<pw[k])ans=max(ans,(x|(pw[dep]-1))+y);
		}
		else dfs(ls,dep-1,res,x,y,z);
		if((x|(pw[dep+1]-1))+y<z){
			if(y<pw[k])ans=max(ans,(x|(pw[dep+1]-1))+y);
		}
		else dfs(rs,dep-1,res,x|pw[dep],y,z);
	}
}
void work(){
	n=read();m=read();k=read();
	for(int i=1;i<=n;i++)a[i]=read();
	int s=0;
	for(int i=1;i<=n;i++)b[i]=read(),s+=b[i];
	if(s<=m){
		ans=a[1];
		for(int i=2;i<=n;i++)ans=min(ans,a[i]);
		write(ans+pw[k]-1);puts("");
		return ;
	}
	idx=1;
	mn[0]=mn[1]=pw[k],sum[1]=0;
	tree[1][0]=tree[1][1]=0;
	for(int i=1;i<=n;i++){
		int nd=1;
		for(int j=k-1;~j;j--){
			int v=(a[i]&pw[j])?1:0;
			if(!tree[nd][v]){
				tree[nd][v]=++idx;
				mn[idx]=pw[k],sum[idx]=0;
				tree[idx][0]=tree[idx][1]=0;
			}
			mn[nd]=min(mn[nd],a[i]),sum[nd]+=b[i];
			nd=tree[nd][v];
		}
		mn[nd]=min(mn[nd],a[i]),sum[nd]+=b[i];
	}
	ans=0;dfs(1,k-1,m,0,pw[k],0);write(ans);puts("");
}

signed main(){
	// freopen("xor.in","r",stdin);
	// freopen("xor.out","w",stdout);
	
	id=read();T=read();
	pw[0]=1;for(int i=1;i<=120;i++)pw[i]=pw[i-1]*2;
	while(T--)work();
}