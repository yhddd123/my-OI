// Problem: AT_agc064_e [AGC064E] Cross Sum Construction
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_agc064_e
// Memory Limit: 1024 MB
// Time Limit: 3000 ms
// Written by yhm.
// Start codeing:2026-01-30 11:34:07
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
const int maxn=510;
const int inf=1e9;
bool mbe;

int n,a[maxn],b[maxn],c[maxn][maxn],s[maxn],t[maxn];
int p[maxn][maxn],q[maxn][maxn];
int r[maxn][maxn];
void work(){
	n=read();
	for(int i=0;i<n;i++)a[i]=read();
	for(int i=0;i<n;i++)b[i]=read();
	if(n==1){
		printf("%lld\n",a[0]+b[0]);
		return ;
	}
	if(n&1){
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++)p[i][j]=(i-j+n)%n;
		}
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++)q[i][j]=(i+j)%n;
		}
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++)c[p[i][j]][q[i][j]]=a[i]+b[j];
		}
	}
	else{
		map<int,int> mp;
		int p1=0,p2=0;
		for(int i=0;i<n;i++){
			if(mp.find((a[i]%(n-1)+(n-1))%(n-1))!=mp.end()){
				p1=mp[(a[i]%(n-1)+(n-1))%(n-1)],p2=i;
				break;
			}
			else mp[(a[i]%(n-1)+(n-1))%(n-1)]=i;
		}
		// cout<<p1<<" "<<p2<<"\n";
		swap(a[p1],a[0]);
		swap(a[p2],a[n/2]);
		// cout<<p1<<" "<<(a[p1]%(n-1)+(n-1))%(n-1)<<" "<<p2<<" "<<(a[p2]%(n-1)+(n-1))%(n-1)<<"\n";
		// for(int i=0;i<n;i++)cout<<(a[i]%(n-1)+n-1)%(n-1)<<" ";cout<<"\n";
		for(int i=0;i<n;i++){
			for(int j=i;j<i+n;j++)p[i][j-i]=j%n;
		}
		int op=(n/2)&1;
		for(int i=0;i<n/2;i++){
			q[0][2*i]=q[0][2*i+1]=i;
			for(int j=1;j<n/2;j++)q[(-j+n)%n][(2*i-j+n)%n]=i;
			for(int j=1;j<n/2;j++)q[j%n][(2*i+1+j)%n]=i;
			q[n/2][(2*i+op)%n]=q[n/2][(2*i+1+op)%n]=n/2+i;
			for(int j=1;j<n/2;j++)q[(n/2-j+n)%n][(2*i-j+n+op)%n]=n/2+i;
			for(int j=1;j<n/2;j++)q[(n/2+j)%n][(2*i+1+j+op)%n]=n/2+i;
		}
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++)c[p[i][j]][q[i][j]]=a[i]+b[j];
		}
	}
	// for(int i=0;i<n;i++){
		// cout<<i<<"\n";
		// for(int j=0;j<n;j++)cout<<p[j][i]<<" "<<q[j][i]<<"\n";
	// }
	// for(int i=0;i<n;i++){
		// for(int j=0;j<n;j++)cout<<p[i][j]<<" ";cout<<"\n";
	// }cout<<"\n";
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++)cout<<q[i][j]<<" ";cout<<"\n";
	}cout<<"\n";
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++)r[p[i][j]][q[i][j]]=i;
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++)cout<<r[i][j]<<" ";cout<<"\n";
	}cout<<"\n";
	// for(int i=0;i<n;i++){
		// for(int j=0;j<n;j++)cout<<(c[i][j]%(n-1)+n-1)%(n-1)<<" ";
		// cout<<"\n";
	// }
	int ss=0;for(int i=0;i<n;i++)ss+=c[0][i];
	for(int i=0;i<n;i++){
		int sss=0;for(int j=0;j<n;j++)sss+=c[i][j];
		// cout<<(sss%(n-1)+n-1)%(n-1)<<"\n";
		if((sss%(n-1)+n-1)%(n-1)!=(ss%(n-1)+n-1)%(n-1)){
			cerr<<n<<"\n";
			for(int i=0;i<n;i++)cerr<<a[i]<<" ";cerr<<"\n";
			for(int i=0;i<n;i++)cerr<<b[i]<<" ";cerr<<"\n";
			exit(0);
		}
	}
	for(int i=0;i<n;i++){
		int sss=0;for(int j=0;j<n;j++)sss+=c[j][i];
		// cout<<(sss%(n-1)+n-1)%(n-1)<<"\n";
		if((sss%(n-1)+n-1)%(n-1)!=(ss%(n-1)+n-1)%(n-1)){
			cerr<<n<<"\n";
			for(int i=0;i<n;i++)cerr<<a[i]<<" ";cerr<<"\n";
			for(int i=0;i<n;i++)cerr<<b[i]<<" ";cerr<<"\n";
			exit(0);
		}
	}
	int sum=0;for(int i=0;i<n;i++){
		for(int j=0;j<n;j++)sum+=c[i][j];
	}
	while((sum%(2*n-1)+2*n-1)%(2*n-1)){
		sum+=n-1,c[0][0]+=n-1;
	}
	for(int i=0;i<n;i++){
		s[i]=0;for(int j=0;j<n;j++)s[i]+=c[i][j];
		s[i]-=sum/(2*n-1);
		s[i]/=n-1;
	}
	for(int i=0;i<n;i++){
		t[i]=0;for(int j=0;j<n;j++)t[i]+=c[j][i];
		t[i]-=sum/(2*n-1);
		t[i]/=n-1;
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++)printf("%lld ",s[i]+t[j]-c[i][j]);puts("");
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