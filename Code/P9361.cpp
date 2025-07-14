#include<bits/stdc++.h>
using namespace std;
const int maxn=100010;
//better than IO.read
const int BUF_SIZE=(int)1e4+10;
struct fastIO{
	char buf[BUF_SIZE];
	int cur;
	FILE *in;
	fastIO(){
		cur=BUF_SIZE;
		in=stdin;
	}
	inline char nextChar(){
		if(cur==BUF_SIZE){
			fread(buf,BUF_SIZE,1,in);
			cur=0;
		}
		return buf[cur++];
	}
	inline int read(){
		int x=0,f=1;char c=nextChar();
		while(c<'0'||c>'9'){
			if(c=='-') f=-1;
			c=nextChar();
		}
		while('0'<=c&&c<='9'){
			x=(x<<1)+(x<<3)+(c^48);
			c=nextChar();
		}
		return x*f;
	}
}IO;

int n,m,q;
int a[6][maxn],b[6][maxn];
int f[18][maxn][6];
int p[6],p1[6];
signed main(){
	n=IO.read();m=IO.read();
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++)a[i][j]=IO.read(),b[i][a[i][j]]=j;
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
	q=IO.read();
	while(q--){
		int u=IO.read(),v=IO.read(),fl=0,ans=2;
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
