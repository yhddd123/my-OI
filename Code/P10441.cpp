// Problem: P10441 [JOIST 2024] 乒乓球 / Table Tennis
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10441
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2026-01-05 12:43:40
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=5010;
const int inf=1e9;
bool mbe;

int n,m,d[maxn];
int calc(int n){
	return n*(n-1)*(n-2)/6-((n&1)?n*(n/2)*(n/2-1)/2:(n/2)*((n/2)*(n/2-1)/2+(n/2-1)*(n/2-2)/2));
}
bool ans[maxn][maxn];
int id[maxn];
void work(){
	n=read();m=read();
	if(calc(n)<m){puts("No");return ;}
	for(int i=1;i<=n;i++)d[i]=i-1;
	for(int i=1;i<=n;i++)if(calc(i)>=m){
		int del=calc(i)-m;
		if(i&1){
			for(int j=1;j<=i;j++)d[j]=i/2;
		}
		else{
			for(int j=1;j<=i/2;j++)d[j]=i/2-1;
			for(int j=i/2+1;j<=i;j++)d[j]=i/2;
		}
		while(del){
			for(int l=1,r=1;l<=i;l=r+1){
				r=l;while(r<i&&d[r+1]==d[r])r++;
				int tmp=r;
				while(del&&l<r){
					del--;
					d[l++]--,d[r--]++;
				}
				r=tmp;
			}
		}
		break;
	}
	sort(d+1,d+n+1);
	// for(int i=1;i<=n;i++)cout<<d[i]<<" ";cout<<"\n";
	for(int i=n;i;i--){
		int p1=0,p2=i-1;
		for(int j=1;j<i;j++)if(d[j]>=d[d[i]]){p1=j-1;break;}
		for(int j=1;j<i;j++)if(d[j]>d[d[i]]){p2=j-1;break;}
		for(int j=1;j<=p1;j++)ans[i][j]=1,d[i]--;
		for(int j=p2+1;j<i;j++)ans[i][j]=0,d[j]--;
		for(int j=p1+1;j<=p2-d[i];j++)ans[i][j]=0,d[j]--;
		for(int j=p2-d[i]+1;j<=p2;j++)ans[i][j]=1;
	}
	puts("Yes");
	for(int i=2;i<=n;i++){
		for(int j=1;j<i;j++)putchar('0'+ans[i][j]);puts("");
	}
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}