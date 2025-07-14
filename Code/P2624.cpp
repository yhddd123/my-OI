#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,a[maxn];
int sum,cnt;
int t[maxn][maxn],s[maxn][maxn];
int ans[maxn],res=1;

int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		if(a[i]!=-1)sum+=a[i]-1;
		else cnt++;
	}
	for(int i=1;i<=n;i++){
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
		for(int j=1;j<=n;j++)s[i][j]=s[i-1][j]+t[i][j];
	}
	for(int i=1;i<=n;i++)ans[i]=s[n-2][i];
	for(int i=1;i<=n;i++){
		if(a[i]!=-1)for(int j=1;j<=n;j++)ans[j]-=s[a[i]-1][j];
	}
	for(int i=1;i<=n;i++)ans[i]+=t[cnt][i]*(n-2-sum)-t[n-2-sum][i];
	for(int i=1;i<=n;i++)for(int j=1;j<=ans[i];j++)res*=i;
	printf("%lld\n",res);
}
