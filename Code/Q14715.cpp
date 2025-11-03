#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n,m,k,b,ans;
void work(){
	n=read();m=read();k=read();b=read();ans=0;
	for(int i=1;i<=n;i++){
		int num1=0,num2=0,s=0;
		for(int j=1;j<=m;j++){
			int x=read();
			if(x<=0)num1++;
			else num2++;
			s+=x;
		}
		if(s>=k)++ans;
		else if(s+num1-num2>=k&&b)b--,++ans;
	}
	printf("%lld\n",ans);
	
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}