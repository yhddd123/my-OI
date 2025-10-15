#include<bits/stdc++.h>
#define ll long long
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
const int maxn=100010;
const int inf=1e9;
bool mbe;

int n,d,a[maxn],B;
ll ans[maxn];
int f[1<<20];
ll sum[maxn];
void work(){
	n=read();d=read();B=min(15,d);
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)sum[i]=sum[i-1]+(a[i]==0)*i;
	for(int s=0;s<(1<<d);s++)f[s]=n+1;
	for(int i=n;i;i--){
		if(a[i]){
			int ss=a[i]&((1<<B)-1);
			for(int s=ss;s<(1<<B);s=(s+1)|ss)f[a[i]|s]=i;
		}
		for(int j=0;j<d;j++){
			int p=i,v=(1<<d)-1-(1<<j);
			while(p<=n){
				if(a[p]&&(v|a[p])==v){
					// cout<<i<<" "<<j<<" "<<p<<" "<<v<<"\n";
					ans[i]+=p,v^=a[p],p++;
				}
				else{
					int ss=v&((1<<d)-(1<<B));
					int mn=n+1;
					for(int s=ss;;s=(s-1)&ss){
						mn=min(mn,f[(s&v)|(v&((1<<B)-1))]);
						if(!s)break;
					}
					p=mn;
				}
			}
		}
		ans[i]+=d*(sum[n]-sum[i-1]);
	}
	for(int i=1;i<=n;i++)printf("%lld ",ans[i]);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}