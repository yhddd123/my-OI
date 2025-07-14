#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=2010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,num;
int a[maxn][maxn];
int b[maxn][maxn];
int x[maxn],y[maxn];
char c[maxn];

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();
	for(int i=1;i<=n;i++){
		scanf("%s",c+1);
		for(int j=1;j<=i;j++)a[i][j]=c[j]-'0';
	}
	for(int ii=0;ii<=1;ii++){
		for(int jj=0;jj<=1;jj++){
			for(int kk=0;kk<=1;kk++){
				bool fl=0;
				for(int i=1;i<=n;i++){
					for(int j=1;j<=i;j++)b[i][j]=a[i][j];
				}
				for(int i=1;i<=n;i++)b[n][i]^=ii;
				for(int i=1;i<n;i++)b[n-1][i]^=jj;
				y[n]=kk;
				for(int i=1;i<n;i++){
					b[n][i]^=y[n-i+1];
					x[i]=b[n][i];
					b[n-1][i]^=x[i];
					y[n-i]=b[n-1][i];
				}
				for(int i=2;i<=n-2;i++){
					num=b[i][1]^x[1]^y[i];
					for(int j=2;j<=i;j++){
						b[i][j]^=x[j]^y[i-j+1]^num;
						if(b[i][j]){
							fl=1;
							break;
						}
					}
					if(fl)break;
				}
				if(!fl){
					printf("Yes\n");
					exit(0);
				}
			}
		}
	}
	printf("No\n");
}
