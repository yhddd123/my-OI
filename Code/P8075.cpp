#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1000000007
using namespace std;
const int maxn=1010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,ans;
vector<int> ax,ay,bx,by;
char c[maxn];

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();m=read();
	for(int i=1;i<=n;i++){
		scanf("%s",c+1);
		for(int j=1;j<=m;j++){
			if(c[j]=='M')ax.push_back(i+j),ay.push_back(i-j);
			if(c[j]=='S')bx.push_back(i+j),by.push_back(i-j);
		}
	}
	int sa=ax.size(),sb=bx.size();
	sort(ax.begin(),ax.end());
	for(int i=1;i<sa;i++)ans+=i*(sa-i)*(ax[i]-ax[i-1]);
	sort(ay.begin(),ay.end());
	for(int i=1;i<sa;i++)ans+=i*(sa-i)*(ay[i]-ay[i-1]);
	printf("%lld ",ans/2);ans=0;
	sort(bx.begin(),bx.end());
	for(int i=1;i<sb;i++)ans+=i*(sb-i)*(bx[i]-bx[i-1]);
	sort(by.begin(),by.end());
	for(int i=1;i<sb;i++)ans+=i*(sb-i)*(by[i]-by[i-1]);
	printf("%lld\n",ans/2);
}
