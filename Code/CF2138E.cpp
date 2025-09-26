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
const int maxn=52;
const int inf=1e9;
bool mbe;

int n,a[maxn];
int m,b[maxn][maxn];
void work(){
	n=read();
	if(n==0){puts("1"),puts("0");return ;}
	if(n==1){puts("1");puts("1");return ;}
	for(int i=1;i<=50;i++){
		for(int j=1;j<=50;j++)b[i][j]=0;
	}
	for(int i=0;i<25;i++)a[i]=0;
	for(int i=0,j=0;i<25;i++)if(n&(1<<i)){
		j=i;while(n&(1<<j+1))j++;
		if(i&&a[i-1])a[j+1]=1,a[i-1]=-1;
		else if(i==j)a[i]=1;
		else a[j+1]=1,a[i]=-1;
		i=j;
	}
	for(int i=24;~i;i--)if(a[i]){m=i;break;}
	for(int i=1;i<=m;i++){
		b[2*i-1][2*i-1]=1,b[2*i-1][2*i]=1;
		b[2*i][2*i-1]=-1,b[2*i][2*i]=1,b[2*i][2*i+1]=1;
	}
	for(int i=0,p=1;i<=m-2;i++)if(a[i]){
		b[2*m-2*(i-p+1)-1][2*p]=-a[i];
		p++;
	}
	printf("%d\n",2*m);
	for(int i=1;i<=2*m;i++){
		for(int j=1;j<=2*m;j++)printf("%d ",b[i][j]);puts("");
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