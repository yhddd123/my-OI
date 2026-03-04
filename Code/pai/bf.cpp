#include<bits/stdc++.h>
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
static char buf[1000000],*p1=buf,*p2=buf,obuf[1<<22];
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
static int opos=0;
inline void flush_out(){fwrite(obuf,1,opos,stdout);opos=0;}
inline void pc(char c){if(opos == (1<<22))flush_out();obuf[opos++]=c;}
inline void write(__int128 x){static char buf[40];static int len=-1;if(x<0)pc('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)pc(buf[len--]+48);}
const int maxn=1000010;
const int inf=1e9;
bool mbe;

int n,m,a[maxn],b[maxn];
int ans;
int lsh[maxn],len;
int st[maxn],tp;
int pl[maxn],pr[maxn];
void sovle(int l,int r){
	if(l==r){ans+=__int128(m+1-a[l])*a[l];return ;}
	int mid=l+r>>1;
	len=0;for(int i=l;i<=r;i++)lsh[++len]=a[i];
	sort(lsh+1,lsh+len+1),len=unique(lsh+1,lsh+len+1)-lsh-1;lsh[len+1]=m+1;
	for(int i=l;i<=r;i++)b[i]=lower_bound(lsh+1,lsh+len+1,a[i])-lsh;
	ans+=__int128(m+1)*lsh[len]*(mid-l+1)*(r-mid);
	for(int v=len;v;v--){
		for(int i=1;i<=len+1;i++)pl[i]=pr[i]=0;
		st[tp=0]=l-1;for(int i=l;i<=mid;i++)if(a[i]>=lsh[v]){
			while(tp&&a[st[tp]]>=a[i])tp--;
			st[++tp]=i;
		}
		for(int i=1;i<=tp;i++)pl[b[st[i]]]=st[i-1]+1;
		if(a[mid]<lsh[v])pl[len+1]=st[tp]+1;
		else pl[len+1]=mid+1;
		for(int i=len;i;i--)if(!pl[i])pl[i]=pl[i+1];
		st[tp=0]=r+1;for(int i=r;i>mid;i--)if(a[i]>=lsh[v]){
			while(tp&&a[st[tp]]>=a[i])tp--;
			st[++tp]=i;
		}
		for(int i=1;i<=tp;i++)pr[b[st[i]]]=st[i-1]-1;
		if(a[mid+1]<lsh[v])pr[len+1]=st[tp]-1;
		else pr[len+1]=mid;
		for(int i=len;i;i--)if(!pr[i])pr[i]=pr[i+1];
		for(int i=1;i<=len+1;i++){
			ans-=__int128(lsh[i]-lsh[i-1])*(mid-pl[i]+1)*(pr[i]-mid)*(lsh[v]-lsh[v-1]);
			// cout<<i<<" "<<ans<<" "<<pl[i]<<" "<<pr[i]<<"\n";
		}
	}
	// cout<<l<<" "<<r<<" "<<ans<<"\n";
	sovle(l,mid),sovle(mid+1,r);
}
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	sovle(1,n);
	write(ans);flush_out();
}

bool med;
signed main(){
	// freopen("basi.in","r",stdin);
	// freopen("basi.out","w",stdout);
	
	cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	int T=1;
	while(T--)work();
}