// Problem: CF1458C Latin Square
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1458C
// Memory Limit: 500 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-10-24 14:50:28
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
const int maxn=1010;
const int maxm=200010;
const int inf=1e9;
bool mbe;

int n,m,a[maxn][maxn],b[maxn][maxn];
int p[3],v[3];
char s[maxm];
void work(){
	n=read();m=read();
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++)a[i][j]=read()-1;
	}
	p[0]=0,p[1]=1,p[2]=2;v[0]=v[1]=v[2]=0;
	scanf("%s",s+1);
	for(int i=1;i<=m;i++){
		if(s[i]=='L')v[1]--;
		if(s[i]=='R')v[1]++;
		if(s[i]=='D')v[0]++;
		if(s[i]=='U')v[0]--;
		if(s[i]=='I')swap(p[1],p[2]),swap(v[1],v[2]);
		if(s[i]=='C')swap(p[0],p[2]),swap(v[0],v[2]);
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			int ii,jj,vv;
			if(p[0]==0)ii=i;
			if(p[0]==1)ii=j;
			if(p[0]==2)ii=a[i][j];
			if(p[1]==0)jj=i;
			if(p[1]==1)jj=j;
			if(p[1]==2)jj=a[i][j];
			if(p[2]==0)vv=i;
			if(p[2]==1)vv=j;
			if(p[2]==2)vv=a[i][j];
			ii+=v[0],jj+=v[1],vv+=v[2];
			ii%=n,ii+=n,ii%=n;
			jj%=n,jj+=n,jj%=n;
			vv%=n,vv+=n,vv%=n;
			b[ii][jj]=vv;
		}
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++)printf("%d ",b[i][j]+1);puts("");
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