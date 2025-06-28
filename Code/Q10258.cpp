#include<bits/stdc++.h>
// #define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=100010;
const int inf=1e9;
bool mbe;

int n,a[maxn];
void work(){
	n=read();read();
	for(int i=2;i<=n;i++){
		printf("? 1 %d\n",i);fflush(stdout);
		a[i]=read();
	}
	for(int i=1;i<n;i++){
		bool fl=1;int sum=i;
		for(int j=2;j<=n;j++){
			sum+=(i^a[j]);
			if((i^a[j])<=0||(i^a[j])>=n||sum>2*n-2){fl=0;break;}
		}
		if(sum==2*n-2&&fl){
			printf("! %d ",i);
			for(int j=2;j<=n;j++)printf("%d ",i^a[j]);puts("");fflush(stdout);
			return ;
		}
	}
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}