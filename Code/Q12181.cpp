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

int n,ans,a[maxn];
char s[maxn];
int sum[maxn];
#define lb(x) (x&(-x))
struct bit{
	int n,tree[maxn<<1];
	void upd(int x,int w){
		while(x<=n)tree[x]+=w,x+=lb(x);
	}
	int que(int x){
		int res=0;
		while(x)res+=tree[x],x-=lb(x);
		return res;
	}
	void init(int _n){
		n=_n;
		for(int i=1;i<=n;i++)tree[i]=0;
	}
}t1,t2;
int calc(int l,int r,int c1,int c2){
	int B=r-l+1+1;
	sum[l-1]=0;t1.init(2*B),t2.init(2*B);
	for(int i=l;i<=r;i++){
		sum[i]=sum[i-1];
		if(a[i]==c1)sum[i]++;
		if(a[i]==c2)sum[i]--;
	}
	int res=0;
	for(int i=l,ss=0;i<=r;i++){
		t1.upd(sum[i-1]+B,1),t2.upd(sum[i-1]+B,sum[i-1]);ss+=sum[i-1];
		int nl=t1.que(sum[i]+B),nr=i-l+1-nl;
		int sl=t2.que(sum[i]+B),sr=ss-sl;
		res+=nl*sum[i]-sl+sr-nr*sum[i];
	}
	return res;
}
void work(){
	n=read();scanf("%s",s+1);
	for(int i=1;i<=n;i++)a[i]=s[i]-'a';
	// for(int i=1;i<=n;i++){
		// int t[3];t[0]=t[1]=t[2]=0;
		// for(int j=i;j<=n;j++){
			// t[a[j]]++;
			// int mx=max({t[0],t[1],t[2]}),mn=min({t[0],t[1],t[2]});
			// ans+=mx-mn;
		// }
	// }
	ans+=(calc(1,n,0,1)+calc(1,n,0,2)+calc(1,n,1,2))/2;
	for(int o=0;o<3;o++){
		for(int i=1,j;i<=n;i++)if(a[i]!=o){
			j=i;while(j<n&&a[j+1]!=o)j++;
			int l=j-i+1;
			ans-=(l*(l+1)*(l+2)/6-calc(i,j,(o+1)%3,(o+2)%3))/2;
			i=j;
		}
	}
	for(int o=0;o<3;o++){
		for(int i=1,j;i<=n;i++)if(a[i]==o){
			j=i;while(j<n&&a[j+1]==o)j++;
			int l=j-i+1;
			ans-=l*(l+1)*(l+2)/6;
			i=j;
		}
	}
	cout<<ans<<"\n";
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