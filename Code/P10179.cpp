// Problem: P10179 水影若深蓝
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10179
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=300010;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m;
int f[maxn];
int fd(int x){
	if(x==f[x])return x;
	return f[x]=fd(f[x]);
}
int ans[maxn];
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)f[i]=i;
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		int x=fd(u),y=fd(v);
		f[x]=y;
	}
	int pos=0;for(int i=1;i<=n;i++)if(fd(i)!=fd(1))pos=i;
	if(!pos){printf("No\n");return ;}
	printf("Yes\n");
	for(int i=1;i<=n;i++)if(fd(i)!=fd(1))printf("1 %lld\n",i);
	for(int i=2;i<=n;i++)if(fd(i)==fd(1))printf("%lld %lld\n",pos,i);
}

int T;
signed main(){	
	T=read();
	while(T--)work();
}