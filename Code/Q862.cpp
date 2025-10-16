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

int n,p,q;
pii a[maxn];
int s[maxn];
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]={read(),i};
	p=read(),q=read();
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)s[i]=s[i-1]+a[i].fi;
	int num=0;
	for(int i=1;i<=n;i++){
		int l=1,r=i,res=i;
		while(l<=r){
			int mid=l+r>>1;
			if(a[i].fi*(i-mid+1)*q<=(s[i]-s[mid-1])*p)res=mid,r=mid-1;
			else l=mid+1;
		}
		num=max(num,i-res+1);
	}
	if(num==1){puts("0");puts("");return ;}
	set<pii> ss;
	int j=1;
	for(int i=num;i<=n;i++)if(a[i].fi*num*q<=(s[i]-s[i-num])*p){
		while(j<=i-num)ss.insert(a[j]),j++;
		int mn=(a[i].fi*num*q+p-1)/p-(s[i]-s[i-num+1]);
		auto it=ss.lower_bound({mn,0});
		ss.erase(it,ss.end());
		j=i+1;
	}
	while(j<=n)ss.insert(a[j]),j++;
	printf("%lld\n",ss.size());
	vector<int> id;
	for(pii p:ss)id.pb(p.se);
	sort(id.begin(),id.end());
	for(int p:id)printf("%lld ",p);puts("");
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