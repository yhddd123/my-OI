#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=100010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,ans,res=1;
int lg[maxn],pw[21];
int f[maxn][21];
int fd(int x,int k){
	if(f[x][k]==x)return x;
	return f[x][k]=fd(f[x][k],k);
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();m=read();
	pw[0]=1;lg[1]=0;
	for(int i=1;i<=20;i++)pw[i]=pw[i-1]<<1;
	for(int i=2;i<=n;i++)lg[i]=lg[i>>1]+1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=lg[n];j++)f[i][j]=i;
	}
	while(m--){
		int l,r,l1,r1;
		l=read();r=read();l1=read();r1=read();
		int k=lg[r-l+1];
		f[fd(l,k)][k]=fd(l1,k);
		f[fd(r-pw[k]+1,k)][k]=fd(r1-pw[k]+1,k);
	}
	for(int j=lg[n];j>=1;j--){
		for(int i=1;i+pw[j]-1<=n;i++){
			f[fd(fd(i,j),j-1)][j-1]=fd(i,j-1);
			f[fd(fd(i,j)+pw[j-1],j-1)][j-1]=fd(i+pw[j-1],j-1);
		}
	}
	for(int i=1;i<=n;i++){
		if(fd(i,0)==i)++ans;
	}
	for(int i=1;i<ans;i++)res*=10,res%=mod;
	res*=9;res%=mod;
	printf("%lld\n",res);
}
