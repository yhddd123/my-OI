// Problem: P5283 [十二省联考 2019] 异或粽子
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5283
// Memory Limit: 1 MB
// Time Limit: 3500 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353
#define pii pair<int,int>
using namespace std;
const int maxn=500010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,k,a[maxn];
int tree[maxn<<5][2],sum[maxn<<5],idx=1;
priority_queue<pii> q;
int num[maxn],ans;
int query(int id){
	int nd=1,res=0,s=num[id];
	for(int i=31;~i;i--){
		int v=(a[id]>>i)&1ll;
		if(tree[nd][v^1]){
			if(sum[tree[nd][v^1]]>s)nd=tree[nd][v^1],res|=(1ll<<i);
			else s-=sum[tree[nd][v^1]],nd=tree[nd][v];
		}
		else nd=tree[nd][v];
	}
	num[id]++;
	// cout<<id<<" "<<num[id]<<" "<<res<<"\n";
	return res;
}
void work(){
	n=read();k=read()<<1;
	for(int i=1;i<=n;i++)a[i]=read()^a[i-1];
	for(int i=0;i<=n;i++){
		int nd=1;
		for(int j=31;~j;j--){
			sum[nd]++;
			int v=(a[i]>>j)&1ll;
			if(!tree[nd][v])tree[nd][v]=++idx;
			nd=tree[nd][v];
		}
		sum[nd]++;
	}
	// for(int i=1;i<=idx;i++)cout<<tree[i][0]<<" "<<tree[i][1]<<" "<<sum[i]<<"\n";
	for(int i=0;i<=n;i++)q.push({query(i),i});
	while(!q.empty()&&k){
		ans+=q.top().first;int p=q.top().second;q.pop();k--;
		if(num[p]<n)q.push({query(p),p});
	}
	printf("%lld\n",ans>>1);
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
