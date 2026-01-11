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
const int maxn=16;
const int inf=1e9;
bool mbe;

int n,a[1<<maxn],b[1<<maxn],ans;
void work(){
	n=read();
	for(int s=0;s<(1<<n);s++)a[s]=read();
	for(int s=0;s<(1<<n);s++){
		for(int t=s;t<(1<<n);t=(t+1)|s){
			b[t]=a[t];
		}
		for(int i=0;i<n;i++)if(!(s&(1<<i))){
			for(int t=s;t<(1<<n);t=(t+1)|s)if(t&(1<<i)){
				b[t]+=b[t^(1<<i)];
			}
		}
		for(int t=s;t<(1<<n);t=(t+1)|s)ans^=b[t];
	}
	printf("%lld\n",ans);
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