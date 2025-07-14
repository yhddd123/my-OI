#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
using namespace std;
const int maxn=1000010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n;
// int f[maxn],dp[maxn];
double d;
int que(int l,int r){
	printf("? %lld %lld\n",l,r);fflush(stdout);
	int x=read();
	return x;
}
void work(){
	n=read();d=0.60;
	// f[3]=1,dp[3]=1;
	// for(int i=4;i<=n;i++){
		// int l=i*d,r=i-i*d;
		// f[i]=max(f[l]+1,f[r]+2);
		// dp[i]=max(dp[l]+l,dp[r]+i);
	// }
	// cout<<f[n]+1<<" "<<dp[n]+n<<"\n";
	// cout<<1.5*log2(n)<<" "<<3*n<<"\n";
	int l=1,r=n,pos=que(l,r);
	while(r-l>2){
		int mid=l+(r-l)*d;
		if(pos<=mid){
			if(que(l,mid)==pos)r=mid;
			else l=mid+1,pos=que(l,r);
		}
		else{
			mid=r-(r-l)*d+1;
			if(que(mid,r)==pos)l=mid;
			else r=mid-1,pos=que(l,r);
		}
	}
	if(r-l==1)printf("! %lld\n",l==pos?r:l),fflush(stdout);
	else{
		if(pos==l)printf("! %lld\n",l+1==que(l+1,r)?r:l+1),fflush(stdout);
		else if(pos==l+1)printf("! %lld\n",l==que(l,l+1)?r:l),fflush(stdout);
		else printf("! %lld\n",l==que(l,r-1)?r-1:l),fflush(stdout);
	}
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
