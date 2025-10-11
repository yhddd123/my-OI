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
const int maxn=260;
const int inf=1e9;
bool mbe;

int n,t[maxn],ans1,ans2;
bitset<257> f[maxn<<1];
int calc(int p){
	int a=0;for(int i=0;i<256;i++)(a+=t[i]*i)%=p;
	int b=1;for(int i=1;i<=n&&b;i++)b=b*i%(p-1);
	if(!b){
		if(!a)return 0;
		return 1;
	}
	int ans=1;for(int i=1;i<=b;i++)ans=ans*a%p;
	return ans;
}
void work(){
	n=read();
	for(int i=0;i<256;i++)t[i]=0;
	for(int i=1;i<=n;i++){
		int v=read(),c=read();
		t[v]=c;
	}
	n=0;for(int i=0;i<256;i++)n+=t[i];
	{
		int ans3=calc(3),ans5=calc(5),ans17=calc(17);
		for(int i=0;i<255;i++)if(i%3==ans3&&i%5==ans5&&i%17==ans17)ans1=i;
		// cout<<ans3<<" "<<ans5<<" "<<ans17<<"\n";
	}
	{
		if(n<=11){
			vector<int> aa;
			for(int i=0;i<256;i++){
				for(int j=1;j<=t[i];j++)aa.pb(i);
			}
			int a=1;
			for(int s=0;s<(1<<n);s++)if(__builtin_popcount(s)==n/2){
				int val=0;
				for(int i=0;i<n;i++)(val+=((s&(1<<i))?-1:1)*aa[i])%=257;
				a=a*(val+257)%257;
			}
			int b=1;for(int i=1;i<=n/2;i++)b=b*i%256;
			for(int i=1;i<=(n+1)/2;i++)b=b*i%256;
			if(!b){
				if(!a)ans2=0;
				else ans2=1;
			}
			else{
				ans2=1;for(int i=1;i<=b;i++)ans2=ans2*a%257;
			}
		}
		else{
			pii mx={0,0};
			for(int i=0;i<256;i++)mx=max(mx,{t[i],i});
			if(n-mx.fi>2*257)ans2=0;
			else{
				vector<int> aa;
				for(int i=0;i<256;i++)if(i!=mx.se){
					for(int j=1;j<=t[i];j++)aa.pb(i);
				}
				int sum=0;for(int i=0;i<256;i++)(sum+=t[i]*i)%=257;
				for(int j=0;j<=n/2&&j<=aa.size();j++)f[j].reset();
				f[0][0]=1;
				for(int i=0;i<aa.size();i++){
					int v=2*aa[i]%257;
					for(int j=min({n/2,i});~j;j--){
						f[j+1]|=f[j]<<v;
						f[j+1]|=f[j]>>(257-v);
					}
					// cout<<aa[i]<<" "<<f[n/2][0]<<"\n";
				}
				// cout<<mx.fi<<" "<<mx.se<<" "<<min(n/2,(int)aa.size())<<"\n";
				bool fl=0;
				for(int i=max(0ll,n/2-mx.fi);i<=n/2&&i<=aa.size();i++){
					int v=(sum-2*mx.se*(n/2-i)%257+257)%257;
					// cout<<i<<" "<<v<<"\n";
					if(f[i][v]){fl=1;break;}
				}
				ans2=1-fl;
			}
		}
	}
	// cout<<ans1<<" "<<ans2<<"\n";
	for(int i=0;i<65535;i++)if(i%255==ans1&&i%257==ans2)printf("%d\n",i);
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