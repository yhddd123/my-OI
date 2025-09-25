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

int n,l,r;
vector<int> ans;
bool sovle(int n,int l,int r){
	if(l==0&&r==n)return 1;
	if(2*l>r){
		for(int i=n-1;i>=r;i--)ans.pb(i);
		ans.pb(r-l);for(int i=r-1;i>r-l;i--)ans.pb(i);
		return 1;
	}
	if(r==n)return 0;
	if(l+r<n){
		ans.pb(n-l-1);for(int i=n-1;i>n-l-1;i--)ans.pb(i);
		for(int i=n-l-2;i>=r-l;i--)ans.pb(i);
		return 1;
	}
	// cout<<n<<" "<<l<<" "<<r<<"\n";
	ans.pb(r);for(int i=n-1;i>r;i--)ans.pb(i);
	int len=n-r-1;
	l-=len,r-=len,n-=len+1;
	return sovle(n,l,r);
}
void work(){
	n=read();l=read(),r=read();
	if(sovle(n,l,r)){
		puts("Yes");
		for(int u:ans)printf("%d ",u);puts("");
	}
	else puts("No");
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