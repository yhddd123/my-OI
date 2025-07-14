#include<bits/stdc++.h>
using namespace std;
const int maxn=110;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,res;
int a[maxn][maxn];
int t[maxn][maxn];
void sovle(int l){
	for(int i=1;i<=n+1;i++)swap(a[l][i],a[n+1][i]);
	for(int i=1;i<=n;i++){
		int mxt=i;
		for(int j=i+1;j<=n;j++)if(abs(a[j][i])>abs(a[mxt][i]))mxt=j;
		for(int j=1;j<=n+1;j++)swap(a[i][j],a[mxt][j]);
		if(a[i][i]==0)continue;
		for(int j=1;j<=n;j++){
			if(i==j)continue;
			int d=a[j][i]/a[i][i];
			for(int k=i+1;k<=n+1;k++)a[j][k]-=a[i][k]*d;
		}
	}
}
int ans[maxn][maxn];
bool fl[maxn];
void check(int l){
	int mx=0,t=0;
	for(int i=1;i<=n;i++){
		if(!a[i][i]){
			fl[l]=1;
			return ;
		}
		else if(a[i][i]&&!a[i][n+1]){
			fl[l]=1;
			return ;
		}
		else if(a[i][n+1]/a[i][i]<=0){
			fl[l]=1;
			return ;
		}
		else{
			ans[l][i]=a[i][n+1]/a[i][i];
			if(mx<ans[l][i])mx=ans[l][i],t=1;
			else if(mx==ans[l][i])++t;
		}
	}
	if(t>1)fl[l]=1;
	else ++res;
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	srand(time(0));
	n=read();
	for(int i=1;i<=n+1;i++){
		int u=read();
		for(int j=1;j<=u;j++){
			int v=read();
			t[i][v]++;
		}
		t[i][n+1]=read();
	}
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			int x=rand();
			if(x&1)for(int k=1;k<=n+1;k++)swap(a[i][k],a[j][k]);
		}
	}
	for(int i=1;i<=n+1;i++){	
		for(int j=1;j<=n+1;j++)for(int k=1;k<=n+1;k++)a[j][k]=t[j][k];
		sovle(i);
		check(i);
	}
	if(res!=1)printf("illegal\n");
	else{
		for(int i=1;i<=n+1;i++){
			if(fl[i])continue;
			int mxt=1;
			for(int j=2;j<=n;j++)if(ans[i][j]>ans[i][mxt])mxt=j;
			printf("%d\n",mxt);
			exit(0);
		}
	}
}
