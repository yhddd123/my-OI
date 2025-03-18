---
title: 'CF2048F 题解'
date: 2024-12-26 16:19:44
tags: [题解,dp]
published: true
hideInList: false
feature: 
isTop: false
---
[CF2048F](https://www.luogu.com.cn/problem/CF2048F)

### 思路

如果想操作 $b_p$，选可以选的最长区间不劣，那可以选的区间即为小根笛卡尔树上 $p$ 对应的区间。只有 $O(n)$ 个包含关系成树的可行操作区间，从下往上操作。可以设 $dp_{u,v}$ 表示操作完 $u$ 的子树，$u$ 对应的区间中 $a_u$ 的最大值最小为 $v$，最少做几次。注意到至多只会操作 $\log V$ 次，交换 dp 的状态和答案，$dp_{u,i}$ 表示 $u$ 子树内做 $i$ 次 $a_u$ 的最大值最小为多少。暴力合并复杂度 $O(n\log V)$。

分步转移，$dp_{u,i}=\min_{j+k=i}(\max (dp_{ls,j},dp_{rs,k}))$。$dp_{u,i}$ 单调，min-max 卷积可以 $O(siz)$ 归并的合并。$dp_{u,i}=\max(dp_{u,i},a_u)$，$dp_{u,i}=\min(dp_{u,i},\lceil \frac{dp_{u,i-1}}{b_u}\rceil)$。复杂度 $O(n\log V)$。

### code

```cpp
int n,a[maxn],b[maxn];
int st[18][maxn];
bool cmp(int u,int v){return b[u]<b[v];}
int que(int l,int r){
	int k=__lg(r-l+1);
	return min(st[k][l],st[k][r-(1<<k)+1],cmp);
}
vector<int> dp[maxn];
vector<int> merge(vector<int> u,vector<int> v){
	if(!u.size())return v;
	if(!v.size())return u;
	vector<int> res;res.pb(max(u[0],v[0]));
	int p=1,q=1;
	while(p<u.size()&&q<v.size()){
		if(max(u[p],v[q-1])<max(u[p-1],v[q]))res.pb(max(u[p],v[q-1])),p++;
		else res.pb(max(u[p-1],v[q])),q++;
	}
	while(p<u.size())res.pb(max(u[p],v.back())),p++;
	while(q<v.size())res.pb(max(u.back(),v[q])),q++;
	res.resize(60);
	return res;
}
int idx;
int sovle(int l,int r){
	if(l>r)return 0;
	int nd=++idx;dp[nd].resize(60);
	if(l==r){
		for(int i=0,v=a[l];i<60;i++)dp[nd][i]=v,v=(v+b[l]-1)/b[l];
		return nd;
	}
	int mid=que(l,r),ls=sovle(l,mid-1),rs=sovle(mid+1,r);
	dp[nd]=merge(dp[ls],dp[rs]);
	for(int i=0;i<60;i++)dp[nd][i]=max(dp[nd][i],a[mid]);
	for(int i=1;i<60;i++)dp[nd][i]=min(dp[nd][i],(dp[nd][i-1]+b[mid]-1)/b[mid]);
	return nd;
}
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();
	for(int i=1;i<=n;i++)st[0][i]=i;
	for(int j=1;j<18;j++){
		for(int i=1;i+(1<<j)-1<=n;i++)st[j][i]=min(st[j-1][i],st[j-1][i+(1<<j-1)],cmp);
	}
	idx=0;sovle(1,n);
	int pos=60;for(int i=59;~i;i--)if(dp[1][i]==1)pos=i;
	printf("%lld\n",pos);
}
```