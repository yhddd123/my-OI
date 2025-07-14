#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
using namespace std;
const int maxn=200010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int t,n,k,x,y;
int id[8];
void work(){
	t=read(),n=read(),k=read(),x=read(),y=read();
	if(!t){
		printf("%lld\n",y-x);
		return ;
	}
	if(n<=k){
		puts("-1");
		return ;
	}
	if(t==1){
		if(y-x>=k)puts("1");
		else if(x-1>=k||n-y>=k)puts("2");
		else if(y-1<k||n-x<k)puts("-1");
		else puts("3");
		return ;
	}
	if(k>3)puts("-1");
	if(k==3){
		if(n==5){
			if(t==2&&x==2&&y==4)puts("1");
			else puts("-1");
		}
		else if(n==6){
			if(t==2){
				if((x==2&&y==4)||(x==3&&y==4)||(x==3&&y==5))puts("1");
				else if((x==2&&y==3)||(x==4&&y==5))puts("2");
				else if(x==2&&y==5)puts("3");
				else puts("-1");
			}
			else if(t==3){
				if(x==2&&y==5)puts("1");
				else puts("-1");
			}
			else puts("-1");
		}
		else if(n==7){
			if(t==2&&x==3&&y==5)puts("1");
			else puts("-1");
		}
		else puts("-1");
	}
	if(k==2){
		if(n>=4){
			if(t&1){
				if(n==4){
					if(x==2&&y==3)puts("3");
					else if(x+1==y)puts("2");
					else puts("1");
				}
				else{
					if(x+1==y)puts("2");
					else puts("1");
				}
			}
			else printf("%lld\n",y-x);
		}
		else puts("-1");
	}
	if(k==1)puts("1");
	
}

// \
444

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=read();
	while(T--)work();
}
