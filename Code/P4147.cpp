#include<bits/stdc++.h>
using namespace std;
const int maxn=1010;
int n,m,a[maxn][maxn],ans;
int up[maxn][maxn],l[maxn][maxn],r[maxn][maxn];
char ch;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>ch;
			if(ch=='F'){
				a[i][j]=1;
				up[i][j]=i;l[i][j]=j;r[i][j]=j;
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=2;j<=m;j++){
			if(a[i][j]+a[i][j-1]==2)l[i][j]=l[i][j-1];
		}
		for(int j=m;j>=2;j--){
			if(a[i][j]+a[i][j-1]==2)r[i][j-1]=r[i][j];
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j]+a[i-1][j]==2 && i!=1){
				up[i][j]=up[i-1][j];
				l[i][j]=max(l[i][j],l[i-1][j]);
				r[i][j]=min(r[i][j],r[i-1][j]);
			}
			if(a[i][j]){
				int x=r[i][j]-l[i][j]+1,y=i-up[i][j]+1;
				ans=max(ans,x*y);
//				cout<<x*y<<" "<<i<<" "<<j<<" "<<ans<<endl;
			}
		}
	}
	printf("%d",ans*3);
} 
