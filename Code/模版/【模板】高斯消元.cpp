// Problem: P2455 [SDOI2006] 线性方程组
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P2455
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-09-05 19:55:04
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
const int maxn=110;
const int inf=1e9;
const double eps=1e-7;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,pos;
double a[maxn][maxn],b[maxn];

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)a[i][j]=read();
		b[i]=read();
	}
	pos=1;//当前行
	for(int i=1;i<=n;i++){//i列 
		int mxt=pos;//主元行
		for(int j=pos+1;j<=n;j++)if(fabs(a[j][i])>fabs(a[mxt][i]))mxt=j;
		if(fabs(a[mxt][i])<eps)continue;
		for(int j=1;j<=n;j++)swap(a[pos][j],a[mxt][j]);
		swap(b[pos],b[mxt]);
		for(int j=1;j<=n;j++){
			if(j==pos)continue;
			double d=a[j][i]/a[pos][i];
			for(int k=i+1;k<=n;k++)a[j][k]-=a[pos][k]*d;
			b[j]-=b[pos]*d;
		}
		++pos;
	}
	if(pos<=n){
		while(pos<=n){
			if(fabs(b[pos])>=eps){
				printf("-1\n");
				return 0;
			}
			pos++;
		}
		printf("0\n");
		return 0;
	}
	for(int i=1;i<=n;i++){
		if(fabs(b[i])<eps)printf("x%d=0.00\n",i);
		else printf("x%d=%.2lf\n",i,1.0*b[i]/a[i][i]);
	}
}