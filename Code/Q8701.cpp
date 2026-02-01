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
const int maxn=2000010;
const int inf=1e9;
bool mbe;

int n,ans[maxn];
char s[maxn],t[maxn];
mt19937 rnd(time(0));
int h[maxn],val[26],bas,pw[maxn];
int calc(int l,int r){return (h[r]+mod-h[l-1]*pw[r-l+1]%mod)%mod;}
int calc1(int l,int r,int p,int w){
	if(p<l||p>r)return calc(l,r);
	return (h[r]+mod-h[l-1]*pw[r-l+1]%mod+w*pw[r-p])%mod;}
int ff[maxn];
int fd(int x){
	if(ff[x]==x)return x;
	return ff[x]=fd(ff[x]);
}
void work(){
	scanf("%s%s",s+1,t+1);n=strlen(s+1);
	bas=rnd()%mod;for(int i=0;i<26;i++)val[i]=rnd()%mod;
	pw[0]=1;for(int i=1;i<=n;i++)pw[i]=pw[i-1]*bas%mod;
	for(int i=1;i<=n;i++)h[i]=(h[i-1]*bas+val[s[i]-'a'])%mod;
	for(int i=1;i<=n+1;i++)ff[i]=i;
	int mx=0;
	for(int i=n-1;i;i--){
		if(calc(1,i)==calc(n-i+1,n)){
			if(!mx)mx=i;
			int pl=i+1,pr=n-i;
			for(int j=fd(pl);j<=pr;j=fd(j)){
				ff[j]=fd(j+1);
				ans[j]=i;
			}
		}
		else{
			int l=1,r=i,res=0;
			while(l<=r){
				int mid=l+r>>1;
				if(calc(1,mid)==calc(n-i+1,n-i+mid))res=mid,l=mid+1;
				else r=mid-1;
			}
			res++;
			// cout<<i<<" "<<res<<"\n";
			int d=(val[t[res]-'a']+mod-val[s[res]-'a'])%mod;
			if(!ans[res]&&calc1(1,i,res,d)==calc1(n-i+1,n,res,d)){
				ans[res]=i,ff[res]=fd(res+1);
			}
			d=(val[t[n-i+res]-'a']+mod-val[s[n-i+res]-'a'])%mod;
			if(!ans[n-i+res]&&calc1(1,i,n-i+res,d)==calc1(n-i+1,n,n-i+res,d)){
				ans[n-i+res]=i,ff[n-i+res]=fd(n-i+res+1);
			}
		}
	}
	for(int i=1;i<=n;i++)if(s[i]==t[i])ans[i]=max(ans[i],mx);
	for(int i=1;i<=n;i++)printf("%lld\n",ans[i]);
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