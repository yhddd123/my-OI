---
title: 'abc217g 题解'
date: 2023-12-31 07:35:14
tags: [题解,dp]
published: true
hideInList: false
feature: 
isTop: false
---
[abc217g](https://www.luogu.com.cn/problem/AT_abc217_g)

### 思路

设 $f_{i,j}$ 表示前 $i$ 个数分到 $j$ 组的情况数。

两种转移：

- 新开一组。$f_{i,j}=f_{i-1,j-1}$。

- 加入之前的组。在 $i$ 之前与 $i$ 模 $m$ 余数相同的有 $\frac{i-1}{m}$ 个，剩下 $j-\frac{i-1}{m}$ 组可以加入。$f_{i,j}=f_{i-1,j}\times (j-\frac{i-1}{m})$。

最后答案为 $f_{n,i}$。

### code

```cpp
int n,m;
int f[maxn][maxn];

int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);

	n=read();m=read();
	f[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			f[i][j]=f[i-1][j-1];
			if(j>=(i+1)/m)f[i][j]+=f[i-1][j]*(j-(i-1)/m);
			f[i][j]%=mod;
//			cout<<f[i][j]<<" ";
		}
//		cout<<"\n";
	}
	for(int i=1;i<=n;i++)printf("%lld\n",f[n][i]);
}
```