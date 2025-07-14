#include<bits/stdc++.h>
#define db double
#define mod 1000000007
#define pii pair<int,int>
#define mems(x,y) memset(x,y,sizeof x)
using namespace std;
const int maxn=200010;
const db eps=1e-8;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,a[maxn],ans;
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++)a[i]=read();
	for(int i=0;i<=n;i++){
		int sum=0;
		for(int j=1;j<=m;j++)sum+=max(0,a[j]-i);
		if(sum<=i*(n-i)){
			ans=i;
			break;
		}
	}
	printf("%lld\n",ans);
	vector<vector<int> > res(n+2,vector<int>(m+2,0));
	for(int i=n-ans+1;i<=n;i++){
		int x=i;
		for(int j=1;j<=m;j++){
			if(a[j]<=0)continue;
			res[x][j]=1;a[j]--;
			while(x>i-n+ans&&a[j]>n-i){
				a[j]--;x--;
				res[x][j]=1;
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(res[i][j])printf("#");
			else printf(".");
		}
		printf("\n");
	}
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	T=read();
	while(T--)work();
}
