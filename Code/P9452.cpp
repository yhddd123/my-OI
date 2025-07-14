#include<bits/stdc++.h>
#define mod 1000000007
using namespace std;
const int maxn=1000010;
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48),c=getchar();}
	return x*f;
}

int n,a[maxn],p[maxn];
int res,ans[maxn][2];
int st[maxn],tp,st1[maxn],tp1;

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=n;i>=1;i--)st[++tp]=a[i];
	for(int i=n;i>=1;i--){
		if(p[i]==0){
			while(st[tp]!=i){
				st1[++tp1]=st[tp];
				p[st[tp]]=1;
				tp--;
				ans[++res][0]=0;ans[res][1]=1;
			}
			tp--;
			ans[++res][0]=0;ans[res][1]=2;
		}
		else{
			while(st1[tp1]!=i){
				st[++tp]=st1[tp1];
				p[st1[tp1]]=0;
				tp1--;
				ans[++res][0]=1;ans[res][1]=0;
			}
			tp1--;
			ans[++res][0]=1;ans[res][1]=2;
		}
	}
	printf("%d\n",res);
	for(int i=1;i<=res;i++)cout<<(char)(ans[i][0]+'A')<<" "<<(char)(ans[i][1]+'A')<<"\n";
}
