#include<bits/stdc++.h>
using namespace std;
int n,m,t,mp[2010][2010],ans,f[2010][2010],mx;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf("%d",&mp[i][j]);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(mp[i][j]==1){
				f[i][j]=min(f[i-1][j],min(f[i-1][j-1],f[i][j-1]))+1;
				mx=max(mx,f[i][j]);
			}
		}
	}
	printf("%d",mx);
}
