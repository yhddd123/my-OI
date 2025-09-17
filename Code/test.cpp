#include<bits/stdc++.h>
#define db long double
using namespace std;
const int maxn=110;
const int maxm=5000;

int n,m,k,cur;
db f[2][maxn][maxm*2+1][3];
signed main(){
	cin>>n>>m>>k;
	f[0][0][maxm][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=i;j++){
			for(int k=0;k<=2*maxm;k++){
				for(int l=0;l<=2;l++)f[i&1][j][k][l]=0;
			}
		}
		for(int j=0;j<i;j++){
			for(int k=0;k<=2*maxm;k++){
				for(int l=0;l<=2;l++)if(f[cur][j][k][l]){
					// cout<<i-1<<" "<<j<<" "<<k<<" "<<l<<" "<<f[cur][j][k][l]<<"\n";
					if(k-2*i>=0)f[i&1][j+1][k-2*i][l]+=f[cur][j][k][l]*(j+1-l)/(n-i+1);
					if(j)f[i&1][j][k+i-i][l]+=f[cur][j][k][l]*(2*j-l)/(n-i+1);
					if(j>1&&k+2*i<=2*maxm)f[i&1][j-1][k+2*i][l]+=f[cur][j][k][l]*(j-1)/(n-i+1);
					if(l<2){
						if(k-i>=0)f[i&1][j+1][k-i][l+1]+=f[cur][j][k][l]*(2-l)/(n-i+1);
						if(j&&k+i<=2*maxm)f[i&1][j][k+i][l+1]+=f[cur][j][k][l]*(2-l)/(n-i+1);
					}
				}
			}
		}
		cur^=1;
	}
	db ans=0;for(int i=maxm+m;i<=2*maxm;i++)ans+=f[n&1][1][i][2];
	printf("%.*Lf", k, ans);
}