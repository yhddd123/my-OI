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
const int maxn=100010;
const int inf=1e9;
bool mbe;

int n,m,k;
int f[maxn<<1];
int fd(int x){
	if(f[x]==x)return x;
	return f[x]=fd(f[x]);
}
void work(){
	n=read();m=read();k=read();
	if(!m){
		int mul=1;for(int i=1;i<=n;i++)mul=mul*k%6;
		printf("%lld\n",mul);
		return ;
	}
	for(int i=1;i<=2*n;i++)f[i]=i;
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		f[fd(u)]=fd(v+n),f[fd(u+n)]=fd(v);
	}
	if(k<=1){puts("0");return ;}
	for(int i=1;i<=n;i++)if(fd(i)==fd(i+n)){puts("0");return ;}
	int num=0;for(int i=1;i<=n;i++)num+=(f[i]==i);
	int mul=1;for(int i=1;i<=num;i++)mul=mul*2%6;
	printf("%lld\n",mul*(k*(k-1)/2)%6);
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