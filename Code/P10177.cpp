// Problem: P10177 似巨龙高歌
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10177?contestId=157909
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
const int maxn=1000010;
const int inf=2e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,a[maxn];
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	sort(a+1,a+n+1);
	int res=-inf;
	for(int i=2;i<=n;i++)res=max(res,a[i-1]-a[i]);
	printf("%d\n",res);
}

int T;
signed main(){
	T=1;
	while(T--)work();
}