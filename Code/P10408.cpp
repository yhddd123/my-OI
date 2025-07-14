// Problem: P10408 「SMOI-R1」Apple
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10408
// Memory Limit: 512 MB
// Time Limit: 680000 ms
// Written by yhm.
// Start codeing:2024-05-28 15:00:29
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1<<20;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,q,a[maxn],f[maxn];

signed main(){
	n=read();q=read();int m=n>>1,ss=(1<<m)-1,sss=(1<<n-m)-1;
	for(int i=0;i<(1<<n);i++)f[i]=a[i]=read();
	for(int i=m;i<n;i++){
		for(int s=0;s<(1<<n);s++)if(!(s&(1<<i)))f[s|(1<<i)]+=f[s];
	}
	while(q--){
		int op=read();
		if(op==1){
			int s=read(),t1=(s>>m)<<m,t2=s&ss,ans=0;
			for(int i=t2;;i=(i-1)&t2){
				ans+=f[t1|i];
				if(!i)break;
			}
			printf("%lld\n",ans);
		}
		else{
			int s=read(),t1=s>>m,t2=s&ss,v=read()-a[s];
			for(int i=t1;;i=(i+1)|t1){
				f[(i<<m)|t2]+=v;
				if(i==sss)break;
			}
			a[s]+=v;
		}
	}
}
