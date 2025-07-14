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

double n,a[maxn][maxn],b[maxn];

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)a[i][j]=read();
		b[i]=read();
	}
	for(int i=1;i<=n;i++){
		int mxt=i;
		for(int j=i+1;j<=n;j++)if(fabs(a[j][i])>fabs(a[mxt][i]))mxt=j;
		for(int j=1;j<=n;j++)swap(a[i][j],a[mxt][j]);
		swap(b[i],b[mxt]);
		if(!a[i][i]){
			printf("No Solution\n");
			exit(0);
		}
		for(int j=1;j<=n;j++){
			if(i!=j){
				double d=a[j][i]/a[i][i];
				for(int k=i+1;k<=n;k++){
					a[j][k]-=a[i][k]*d;
				}
				b[j]-=b[i]*d;
			}
		}
	}
	for(int i=1;i<=n;i++){
		printf("%.2lf\n",b[i]/a[i][i]);
	}
}
