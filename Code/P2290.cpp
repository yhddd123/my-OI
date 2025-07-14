#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=210;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,a[maxn],tot;
int t[maxn][maxn];
int ans[maxn],res=1;

int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		if(!a[i]&&n!=1){
			printf("0\n");
			return 0;
		}
		tot+=a[i];
	}
	if(tot!=2*n-2){
		printf("0\n");
		return 0;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)t[i][j]=t[i-1][j];
		int x=i;
		for(int j=2;j*j<=i;j++){
			if(x%j==0){
				while(x%j==0){
					t[i][j]++;
					x/=j;
				}
			}
		}
		if(x>1)t[i][x]++;
	}
	for(int i=1;i<=n;i++)ans[i]=t[n-2][i];
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)ans[j]-=t[a[i]-1][j];
	}
	for(int i=1;i<=n;i++)for(int j=1;j<=ans[i];j++)res*=i;
	printf("%lld\n",res);
}
