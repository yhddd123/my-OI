---
title: 'CF1613F 题解'
date: 2025-02-20 21:51:39
tags: [题解,数学]
published: true
hideInList: false
feature: 
isTop: false
---

[CF1613F](https://www.luogu.com.cn/problem/CF1613F)

### 思路

容斥。钦定 $i$ 个点不满足 $c_u\neq c_{fa}-1$ 的限制的方案数为 $f_i$，有 $n-1$ 对限制，$ans=\sum_{i=0}^{n-1}(-1)^if_i$。

由于 $c$ 是排列，每个点 $u$ 只有一个儿子能被钦定不合法。而没有被钦定的点之间大小关系独立，即 $(n-i)!$；被钦定的点的值取决于祖先最近的没有被钦定的点，这部分的贡献即每个点独立的选一个儿子或不选，即 $[x^i]\prod(1+d_ux)$。

只需要快速求出 $n$ 个一次的多项式相乘的系数，分治 ntt 复杂度 $O(n\log^2 n)$。

因为有 $\sum d_u$ 是 $O(n)$ 的。将相同的 $(dx+1)$ 合起来做。记有 $t_i$ 个 $d_u=i$，$\prod (ix+1)^{t_i}$ 可以二项式系数展开。按 $d_u$ 的值从大往小做，直接和之前算出来的多项式 ntt 乘起来，复杂度是对的。即每次 ntt 的长度之和 $\sum_{i=1}^n (\sum_{j=i}^n t_j)=\sum i\times t_i=\sum d_u$，是 $O(n)$ 级别的。复杂度 $O(n\log n)$。

### code

```cpp
int n,ans;
int d[maxn],t[maxn];
vector<int> e[maxn];
void dfs(int u,int fa){
	for(int v:e[u])if(v!=fa)d[u]++,dfs(v,u);
}
vector<int> f;
using poly::mul;
int fac[maxn],inv[maxn];
int C(int m,int n){return fac[m]*inv[n]%mod*inv[m-n]%mod;}
void work(){
	n=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		e[u].pb(v),e[v].pb(u);
	}
	dfs(1,0);
	for(int i=1;i<=n;i++)t[d[i]]++;
	fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
	inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
	for(int i=n-1;i;i--){
		vector<int> g(t[i]+1);
		for(int j=0,mul=1;j<=t[i];j++)g[j]=C(t[i],j)*mul%mod,mul=mul*i%mod;
		f=mul(f,g);
	}
	for(int i=0;i<f.size();i++)(ans+=((i&1)?(mod-1):1)*fac[n-i]%mod*f[i])%=mod;
	printf("%lld\n",ans);
}
```

