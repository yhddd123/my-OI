#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=1010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48),c=getchar();}
	return x*f;
}

int n,m,a[maxn][maxn],ans;
int l[maxn][maxn],up[maxn][maxn];
struct nd{
	int l,up;
}st[maxn];
int h,sum;

signed main(){
	n=read();m=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			a[i][j]=read();
			l[i][j]=1;up[i][j]=1;
			if(a[i][j]==a[i][j-1])l[i][j]=l[i][j-1]+1;
			if(a[i][j]==a[i-1][j])up[i][j]=up[i-1][j]+1;
		}
	}
	for(int j=1;j<=m;j++){
		h=sum=0;
		for(int i=1;i<=n;i++){
			if(up[i][j]==1)h=sum=0;
			st[++h].l=l[i][j];st[h].up=1;
			sum+=l[i][j];
			while(h>1&&st[h-1].l>=st[h].l){
				sum=sum-st[h-1].l*st[h-1].up-st[h].l*st[h].up;
				st[h-1].l=st[h].l;st[h-1].up+=st[h].up;
				h--;
				sum+=st[h].l*st[h].up;
			}
			ans+=sum;
		}
	}
	printf("%lld\n",ans);
}

