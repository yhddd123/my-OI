//#include<bits/stdc++.h>
//using namespace std;
//const int maxn=1010;
////static char buf[1000000],*p1=buf,*p2=buf;
////#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
//inline int read(){
//	int x=0,f=1;
//	char ch=getchar();
//	while(ch<'0' || ch>'9'){
//		if(ch=='-')f=-1;
//		ch=getchar();
//	}
//	while(ch>='0' && ch<='9'){
//		x=(x<<3)+(x<<1)+(ch^48);
//		ch=getchar();
//	}
//	return x*f;
//}
//
//int n,t;
//int a[maxn][maxn],f[maxn][maxn],ans;
//signed main(){
//	n=read();t=read();
//	while(t--){
//		a[read()][read()]=1;
//	}
//	for(int i=1;i<=n;i++){
//		for(int j=1;j<=n;j++){
//			if(!a[i][j]){
//				f[i][j]=min({f[i-1][j],f[i][j-1],f[i-1][j-1]})+1;
//				ans=max(ans,f[i][j]);
//			}
//		}
//	}
//	printf("%d",ans);
//}

#include<bits/stdc++.h>
using namespace std;
const int maxn=1010;
//static char buf[1000000],*p1=buf,*p2=buf;
//#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0' || ch>'9'){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9'){
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return x*f;
}

int n,t;
int a[maxn][maxn],up[maxn][maxn],l[maxn][maxn],r[maxn][maxn],ans;
signed main(){
	n=read();t=read();
	while(t--){
		a[read()][read()]=1;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(!a[i][j]){
				up[i][j]=i;
				l[i][j]=j;r[i][j]=j;
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=2;j<=n;j++){
			if(a[i][j]+a[i][j-1]==0)l[i][j]=l[i][j-1];
		}
		for(int j=n;j>=2;j--){
			if(a[i][j]+a[i][j-1]==0)r[i][j-1]=r[i][j];
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(a[i][j]+a[i-1][j]==0 && i!=1){
				up[i][j]=up[i-1][j];
				l[i][j]=max(l[i][j],l[i-1][j]);
				r[i][j]=min(r[i][j],r[i-1][j]);
			}
			if(a[i][j]==0){
				int x=r[i][j]-l[i][j]+1,y=i-up[i][j]+1;
				ans=max(ans,min(x,y));
			}
		}
	} 
	printf("%d",ans);
	
}

