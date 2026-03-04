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
__int128 ans;
int st1[maxn],tp1,st2[maxn],tp2;
int id[maxn],tmp[maxn];
struct dsu{
	int f[maxn];
	__int128 sum[maxn];
	void init(int l,int r){
		for(int i=l;i<=r;i++)f[i]=i,sum[i]=0;
	}
	int fd(int x){
		if(f[x]==x)return x;
		return f[x]=fd(f[x]);
	}
	void merge(int u,int v){
		f[v]=u,sum[u]+=sum[v];
	}
	__int128 &calc(int x){return sum[fd(x)];}
}f1,f2;
#define vl(p) (m+1-a[st1[p]])*(st1[p]-st1[p+1])
#define vr(p) (m+1-a[st2[p]])*(st2[p+1]-st2[p])
void sovle(int l,int r){
	if(l==r){ans+=(__int128)(m+1-a[l])*a[l];return ;}
	int mid=l+r>>1;
	sovle(l,mid),sovle(mid+1,r);
	merge(id+l,id+mid+1,id+mid+1,id+r+1,tmp,[&](int u,int v){return a[u]<a[v]||(a[u]==a[v]&&u<v);});
	for(int i=l;i<=r;i++)id[i]=tmp[i-l];
	f1.init(l-1,r+1),f2.init(l-1,r+1);
	tp1=0,tp2=0;
	__int128 res=0;
	for(int rr=r,ll;rr>=l;rr=ll-1){
		ll=rr;while(ll>l&&a[id[ll-1]]==a[id[rr]])ll--;
		int p1=-1,p2=-1;
		for(int ii=ll;ii<=rr;ii++){
			int p=id[ii];
			if(p<=mid)p1=p;
			else if(p2==-1)p2=p;
		}
		// cout<<ll<<" "<<rr<<" "<<res<<"\n";
		if(p1!=-1){
			auto upd=[&](int i,int w){
				int j=f2.fd(st1[i]);
				res+=(__int128)w*vl(i)*(j-1-mid);
				res+=w*f1.calc(st1[i])*(mid-st1[i]);
				f2.sum[j]+=(__int128)w*vl(i);
			};
			while(tp1&&st1[tp1]<p1){
				upd(tp1,-1);
				f1.merge(p1,st1[tp1]);
				tp1--;
			}
			for(int j=tp2;j;j--){
				if(f1.fd(st2[j])==l-1){
					res-=(__int128)vr(j)*(mid-l+1);
					f1.f[st2[j]]=st2[j];
					f1.sum[st2[j]]=vr(j);
					f1.merge(p1,st2[j]);
				}
				else break;
			}
			if(tp1)upd(tp1,-1);
			st1[++tp1]=p1;st1[tp1+1]=l-1;
			if(tp1>1)upd(tp1-1,1);
			f2.merge(r+1,p1);
			upd(tp1,1);
		}
		if(p2!=-1){
			auto upd=[&](int i,int w){
				int j=f1.fd(st2[i]);
				res+=(__int128)w*vr(i)*(mid-j);
				res+=w*f2.calc(st2[i])*(st2[i]-1-mid);
				f1.sum[j]+=(__int128)w*vr(i);
			};
			while(tp2&&st2[tp2]>p2){
				upd(tp2,-1);
				f2.merge(p2,st2[tp2]);
				tp2--;
			}
			for(int j=tp1;j;j--){
				if(f2.fd(st1[j])==r+1){
					res-=(__int128)vl(j)*(r-mid);
					f2.f[st1[j]]=st1[j];
					f2.sum[st1[j]]=vl(j);
					f2.merge(p2,st1[j]);
				}
				else break;
			}
			if(tp2)upd(tp2,-1);
			st2[++tp2]=p2;st2[tp2+1]=r+1;
			if(tp2>1)upd(tp2-1,1);
			f1.merge(l-1,p2);
			upd(tp2,1);
		}
		// for(int i=1;i<=tp1;i++)cout<<st1[i]<<" ";cout<<"\n";
		// for(int i=1;i<=tp2;i++)cout<<st2[i]<<" ";cout<<"\n";
		// st1[tp1+1]=l-1,st2[tp2+1]=r+1;
		// for(int i=1,j=1;i<=tp1;i++){
			// while(j<=tp2&&a[st1[i]]<=a[st2[j]])j++;
			// res+=__int128(m+1-a[st1[i]])*(st1[i]-st1[i+1])*(st2[j]-1-mid);
		// }
		// for(int i=1,j=1;i<=tp2;i++){
			// while(j<=tp1&&a[st2[i]]<a[st1[j]])j++;
			// res+=__int128(m+1-a[st2[i]])*(st2[i+1]-st2[i])*(mid-st1[j]);
		// }
		// cout<<ans<<" "<<res<<"\n";
		ans+=res*(a[id[rr]]-(ll==l?0:a[id[ll-1]]));
	}
	// cout<<l<<" "<<r<<" "<<ans<<" s\n";
}
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read(),id[i]=i;
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