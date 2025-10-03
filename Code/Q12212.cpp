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
const int maxn=400010;
const int inf=2e9;
bool mbe;

int n,k;
int a[maxn];
bool check(int x){
	int res=0;
	for(int i=1;i<=n;i++)res+=(a[i]<=x/2);
	if(!res)return 0;
	for(int i=1,lst=0;lst<=n;i++){
		if(a[i]<=x/2){
			if(lst){
				bool fl=0;for(int j=lst+1;j<i;j++)if(a[j]+a[lst]<=x&&a[j]+a[i]<=x)fl=1;
				if(fl)++res;
			}
			lst=i;
		}
	}
	return res>=k;
}
void work(){
	n=read();k=read();
	for(int i=1;i<=n;i++)a[i]=a[i+n]=read();
	int l=1,r=inf,res=inf;
	while(l<=r){
		int mid=l+r>>1;
		if(check(mid))res=mid,r=mid-1;
		else l=mid+1;
	}
	printf("%lld\n",res);	
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