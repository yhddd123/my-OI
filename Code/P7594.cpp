#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=200010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,a,ans;
int stl[maxn],str[maxn],tp;
int l,r,x,y;

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();
	for(int i=1;i<=n;i++){
		a=read();
		if(!a)continue;
		l=i-a;r=i+a;
		if(l>y){
			stl[++tp]=x;
			str[tp]=y;
			x=l;y=r;
		}
		else{
			x=min(x,l);y=max(y,r);
			while(tp>=1&&str[tp]>=x){
				x=min(x,stl[tp]);
				tp--;
			}
		}
	}
	stl[++tp]=x;str[tp]=y;
	for(int i=1;i<=tp;i++)ans+=(str[i]-stl[i]+1)>>1;
	printf("%lld\n",ans);
}
