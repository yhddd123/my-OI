#include<bits/stdc++.h>
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

int n,m,q;
int a[6][maxn],b[6][maxn];
int f[18][maxn][6];
int p[6],p1[6];
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++)a[i][j]=read(),b[i][a[i][j]]=j;
	}
	memset(f[0],0x3f,sizeof(f[0]));
	for(int i=1;i<=m;i++){
		for(int j=1;j<=m;j++){
			int mn=n+1;
			for(int k=n;k;k--){
				mn=min(mn,b[j][a[i][k]]);
				f[0][a[i][k]][j]=min(f[0][a[i][k]][j],mn);
			}
		}
	}
	for(int i=1;i<=17;i++){
		for(int j=1;j<=n;j++){
			for(int k=1;k<=m;k++){
				f[i][j][k]=f[i-1][j][k];
				for(int l=1;l<=m;l++){
					f[i][j][k]=min(f[i][j][k],f[i-1][a[l][f[i-1][j][l]]][k]);
				}
			}
		}
	}
	q=read();
	while(q--){
		int u=read(),v=read(),fl=0,ans=2;
		for(int i=1;i<=m;i++){
			p[i]=b[i][u];
			if(p[i]<b[i][v]){fl=1;break;}
		}
		if(fl){printf("1\n");continue;}
		for(int i=17;~i;i--){
			for(int j=1;j<=m;j++){
				p1[j]=p[j];
				for(int k=1;k<=m;k++)p1[j]=min(p1[j],f[i][a[k][p[k]]][j]);
			}
			fl=0;
			for(int j=1;j<=m;j++){
				if(p1[j]<b[j][v]){fl=1;break;}
			}
			if(!fl){
				for(int j=1;j<=m;j++)p[j]=p1[j];
				ans+=(1<<i);
			}
		}
		if(ans>n)printf("-1\n");
		else printf("%d\n",ans);
	}
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	T=1;
	while(T--)work();
}