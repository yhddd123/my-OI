// Problem: P7372 [COCI2018-2019#4] Slagalica
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P7372
// Memory Limit: 64 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353
#define pii pair<int,int>
#define mems(x,y) memset(x,y,sizeof x)
using namespace std;
const int maxn=200010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,k,sum;
int pre[maxn],cnt;
bool vis[maxn];
void s(int n){
	for(int i=2;i<=n;i++){
		if(!vis[i])pre[++cnt]=i;
		for(int j=1;j<=cnt&&i*pre[j]<=n;j++){
			vis[i*pre[j]]=1;
			if(i%pre[j]==0)break;
		}
	}
}
vector<int> val;
struct nd{
	int op,u,v;
};
vector<nd> ans;
pii go(pii u){
	if(u.first&1){
		if(u.second==m)return {u.first+1,m};
		else return {u.first,u.second+1};
	}
	else{
		if(u.second==1)return {u.first+1,1};
		return {u.first,u.second-1};
	}
}
void dw(pii p){
	int u=p.first,v=p.second;
	ans.push_back({2,u,v});
	ans.push_back({2,u,v});
	ans.push_back({1,u,v});
	ans.push_back({2,u,v});
	ans.push_back({1,u,v});
	ans.push_back({1,u,v});
}
void l(pii p){
	int u=p.first,v=p.second;
	ans.push_back({1,u,v});
	ans.push_back({1,u,v});
	ans.push_back({2,u,v});
	ans.push_back({1,u,v});
	ans.push_back({2,u,v});
	ans.push_back({2,u,v});
}
void up(pii p){
	int u=p.first,v=p.second;
	ans.push_back({1,u-1,v});
	ans.push_back({2,u-1,v});
	ans.push_back({2,u-1,v});
}
void r(pii p){
	int u=p.first,v=p.second;
	ans.push_back({2,u,v-1});
	ans.push_back({2,u,v-1});
	ans.push_back({1,u,v-1});
}
void turn(pii u,pii v){
	if(u.first==v.first){
		if(u.first==1)dw(min(u,v));
		else up(min(u,v));
	}
	else{
		if(u.second==1)l(min(u,v));
		else r(min(u,v));
	}
}
void work(){
	n=read();m=read();k=read();s(maxn-10);
	for(int i=1;i<=cnt&&pre[i]*pre[i]<=k;i++)if(k%pre[i]==0){
		int v=1;
		while(k%pre[i]==0)v*=pre[i],k/=pre[i];
		val.push_back(v);sum+=v;
	}
	if(k>1)val.push_back(k),sum+=k;
	if(sum>n*m){printf("-1\n");return ;}
	pii p={1,1};
	for(int i:val){
		for(int j=1;j<i;j++){
			pii np=go(p);
			turn(p,np);
			p=np;
		}
		p=go(p);
	}
	printf("%lld\n",ans.size());
	for(nd i:ans){
		if(i.op==1)printf("R ");
		else printf("T ");
		printf("%lld %lld\n",i.u,i.v);
	}
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
