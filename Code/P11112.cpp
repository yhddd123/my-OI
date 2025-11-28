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

int n,m,c,p,ans;
void work(){
	n=read();m=read();c=read();p=read();
	vector<int> val;
	for(int i=1,s=0;i<=n+m;i++){
		int op=read(),h=read();
		if(op==1)s+=h;
		else val.pb(s+h);
	}
	sort(val.begin(),val.end());
	for(int i=0;i<val.size();i++)ans=max(ans,-(val[i]-1)*c+(i+1)*p);
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