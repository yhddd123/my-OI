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

int n,l,k,a[maxn],ans;
int f[maxn*4],s0[maxn*4],s1[maxn*4],s2[maxn*4];
int mx[maxn*3];
int que0(int l,int r){return s0[r]-(l?s0[l-1]:0);}
int que1(int l,int r){return s1[r]-(l?s1[l-1]:0);}
int que2(int l,int r){return s2[r]-(l?s2[l-1]:0);}
int st[20][maxn*3];
int que(int l,int r){
	if(l>r)return -inf;
	int k=__lg(r-l+1);
	return max(st[k][l],st[k][r-(1<<k)+1]);
}
void work(){
	n=read();l=read();k=read();ans=0;
	for(int i=0;i<=4*n;i++)f[i]=0;
	for(int i=1;i<=n;i++){
		a[i]=read();
		f[a[i]]++,f[a[i]+l]--;
	}
	for(int i=1;i<=4*n;i++)f[i]+=f[i-1];
	for(int i=0;i<=4*n;i++){
		s0[i]=(f[i]==k-1);
		s1[i]=(f[i]==k);
		s2[i]=(f[i]==k+1);
	}
	for(int i=1;i<=4*n;i++)s0[i]+=s0[i-1],s1[i]+=s1[i-1],s2[i]+=s2[i-1];
	for(int i=0;i<=3*n+1;i++)mx[i]=max(i?mx[i-1]:-inf,que0(i,i+l-1)-que1(i,i+l-1));
	for(int i=1;i<=n;i++)if(a[i]>=l){
		ans=max(ans,que2(a[i],a[i]+l-1)-que1(a[i],a[i]+l-1)+mx[a[i]-l]);
	}
	for(int i=3*n+1;i;i--)mx[i]=max(i<=3*n?mx[i+1]:-inf,que0(i,i+l-1)-que1(i,i+l-1));
	for(int i=1;i<=n;i++){
		ans=max(ans,que2(a[i],a[i]+l-1)-que1(a[i],a[i]+l-1)+mx[a[i]+l]);
	}
	for(int i=0;i<=3*n;i++)st[0][i]=(i?s2[i-1]-s1[i-1]:0)+s0[i+l-1]-s1[i+l-1];
	// for(int i=1;i<=3*n;i++)cout<<st[0][i]<<" ";cout<<"\n";
	for(int j=1;j<20;j++){
		for(int i=0;i+(1<<j)-1<=3*n;i++)st[j][i]=max(st[j-1][i],st[j-1][i+(1<<j-1)]);
	}
	for(int i=1;i<=n;i++){
		ans=max(ans,que(a[i],a[i]+l-1)+(a[i]?-s2[a[i]-1]+s1[a[i]-1]:0)-s0[a[i]+l-1]+s1[a[i]+l-1]);
		// cout<<i<<" "<<que(a[i]-n,a[i]+l-1-n)<<" "<<que(a[i]-n,a[i]+l-1-n)-s2[a[i]-1]+s1[a[i]-1]-s0[a[i]+l-1]+s1[a[i]+l-1]<<"\n";
	}
	for(int i=0;i<=3*n;i++)st[0][i]=(i>=l?-s0[i-l]+s1[i-l]:0)-s2[i]+s1[i];
	for(int j=1;j<20;j++){
		for(int i=0;i+(1<<j)-1<=3*n;i++)st[j][i]=max(st[j-1][i],st[j-1][i+(1<<j-1)]);
	}
	for(int i=1;i<=n;i++){
		ans=max(ans,que(max(a[i],l-1),a[i]+l-1)+(a[i]?s0[a[i]-1]-s1[a[i]-1]:0)+s2[a[i]+l-1]-s1[a[i]+l-1]);
		// cout<<i<<" "<<a[i]<<" "<<a[i]+l-1<<" "<<que(a[i]-n,a[i]+l-1-n)<<" "<<s0[a[i]-1]-s1[a[i]-1]+s2[a[i]+l-1]-s1[a[i]+l-1]<<" "<<ans<<"\n";
	}
	printf("%lld\n",s1[4*n]+ans);
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