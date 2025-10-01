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
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
inline void write(int x){static char buf[20];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
const int maxn=500010;
const int inf=1e18;
bool mbe;

int n,c;
tuple<int,int,int> tmp[maxn];
int x[maxn],y[maxn],w[maxn];
int st[19][maxn];
int quemn(int l,int r){
	int k=__lg(r-l+1);
	return min(st[k][l],st[k][r-(1<<k)+1]);
}
int quemx(int l,int r){
	int k=__lg(r-l+1);
	return max(st[k][l],st[k][r-(1<<k)+1]);
}
int mnl[maxn],mnr[maxn],mxl[maxn],mxr[maxn];
int dp[maxn];
int lsh[maxn],pos[maxn];
int id1[20][maxn],id2[20][maxn],id3[20][maxn],val[maxn];
void merge(int *a,int *b,int l,int r){
	int mid=l+r>>1;
	int p=l,q=mid+1,pp=l;
	while(p<=mid&&q<=r){
		if(val[b[p]]<val[b[q]])a[pp++]=b[p],p++;
		else a[pp++]=b[q],q++;
	}
	while(p<=mid)a[pp++]=b[p],p++;
	while(q<=r)a[pp++]=b[q],q++;
}
void init(int l,int r,int d=0){
	if(l==r){id1[d][l]=id2[d][l]=id3[d][l]=l;return ;}
	int mid=l+r>>1;
	init(l,mid,d+1),init(mid+1,r,d+1);
	for(int i=l;i<=r;i++)val[i]=pos[i];
	merge(id1[d],id1[d+1],l,r);
	for(int i=l;i<=r;i++)val[i]=mnr[pos[i]];
	merge(id2[d],id2[d+1],l,r);
	for(int i=l;i<=r;i++)val[i]=mnl[pos[i]];
	merge(id3[d],id3[d+1],l,r);
}
int id[maxn];
int mx[1<<20],m;
void init(int n){
	for(m=1;m<=n+1;m<<=1);
	for(int i=1;i<2*m;i++)mx[i]=-inf;
}
void upd(int p,int w){
	p+=m;
	while(p)mx[p]=max(mx[p],w),p>>=1;	
}
void clr(int p){
	p+=m;
	while(p)mx[p]=-inf,p>>=1;
}
int que(int l,int r){
	if(l>r)return -inf;
	int ans=-inf;
	for(l+=m-1,r+=m+1;l^r^1;l>>=1,r>>=1){
		if(~l&1)ans=max(ans,mx[l^1]);
		if(r&1)ans=max(ans,mx[r^1]);
	}
	return ans;
}
void sovle(int l,int r,int d=0){
	if(r-l+1<=32){
		for(int i=l;i<=r;i++){
			dp[i]=max(dp[i],dp[i-1]);
			for(int j=l;j<i;j++){
				if(pos[j]<pos[i]&&mxl[pos[i]]<pos[j]&&pos[i]<mnr[pos[j]]){
					dp[i]=max(dp[i],dp[j-1]+w[pos[i]]-w[pos[j]]-x[pos[i]]+x[pos[j]]+c);
				}
				if(pos[j]>pos[i]&&mnl[pos[j]]<pos[i]&&mxr[pos[i]]>pos[j]){
					dp[i]=max(dp[i],dp[j-1]+w[pos[i]]-w[pos[j]]+x[pos[i]]-x[pos[j]]+c);
				}
			}
		}
		return ;
	}
	int mid=l+r>>1;
	sovle(l,mid,d+1);
	// cout<<l<<" "<<r<<" s\n";
	for(int i=l;i<=mid;i++)id[i]=id2[d+1][i];
	for(int i=mid+1;i<=r;i++)id[i]=id1[d+1][i];
	for(int i=r,j=mid;i>mid;i--){
		while(j>=l&&mnr[pos[id[j]]]>pos[id[i]]){
			upd(pos[id[j]],dp[id[j]-1]-w[pos[id[j]]]+x[pos[id[j]]]+c);
			j--;
		}
		dp[id[i]]=max(dp[id[i]],que(mxl[pos[id[i]]]+1,pos[id[i]]-1)+w[pos[id[i]]]-x[pos[id[i]]]);
	}
	for(int i=l;i<=mid;i++)clr(pos[i]);
	for(int i=l;i<=mid;i++)id[i]=id3[d+1][i];
	for(int i=mid+1;i<=r;i++)id[i]=id1[d+1][i];
	for(int i=mid+1,j=l;i<=r;i++){
		while(j<=mid&&mnl[pos[id[j]]]<pos[id[i]]){
			upd(pos[id[j]],dp[id[j]-1]-w[pos[id[j]]]-x[pos[id[j]]]+c);
			j++;
		}
		dp[id[i]]=max(dp[id[i]],que(pos[id[i]]+1,mxr[pos[id[i]]]-1)+w[pos[id[i]]]+x[pos[id[i]]]);
	}
	for(int i=l;i<=mid;i++)clr(pos[i]);
	sovle(mid+1,r,d+1);
}
void work(){
	n=read();c=read();
	for(int i=1;i<=n;i++)tmp[i]={read(),read(),read()};
	sort(tmp+1,tmp+n+1);
	for(int i=1;i<=n;i++)tie(x[i],y[i],w[i])=tmp[i];
	for(int i=1;i<=n;i++)st[0][i]=y[i];
	for(int j=1;j<=18;j++){
		for(int i=1;i+(1<<j)-1<=n;i++)st[j][i]=min(st[j-1][i],st[j-1][i+(1<<j-1)]);
	}
	for(int i=1;i<=n;i++){
		int l=1,r=i-1,res=0;
		while(l<=r){
			int mid=l+r>>1;
			if(quemn(mid,i)==y[i])r=mid-1;
			else l=mid+1,res=mid;
		}
		mnl[i]=res;
		l=i+1,r=n,res=n+1;
		while(l<=r){
			int mid=l+r>>1;
			if(quemn(i,mid)==y[i])l=mid+1;
			else r=mid-1,res=mid;
		}
		mnr[i]=res;
	}
	for(int j=1;j<=18;j++){
		for(int i=1;i+(1<<j)-1<=n;i++)st[j][i]=max(st[j-1][i],st[j-1][i+(1<<j-1)]);
	}
	for(int i=1;i<=n;i++){
		int l=1,r=i-1,res=0;
		while(l<=r){
			int mid=l+r>>1;
			if(quemx(mid,i)==y[i])r=mid-1;
			else l=mid+1,res=mid;
		}
		mxl[i]=res;
		l=i+1,r=n,res=n+1;
		while(l<=r){
			int mid=l+r>>1;
			if(quemx(i,mid)==y[i])l=mid+1;
			else r=mid-1,res=mid;
		}
		mxr[i]=res;
	}
	for(int i=1;i<=n;i++)lsh[i]=y[i];sort(lsh+1,lsh+n+1);
	for(int i=1;i<=n;i++)y[i]=lower_bound(lsh+1,lsh+n+1,y[i])-lsh,pos[y[i]]=i;
	init(n);
	init(1,n);
	sovle(1,n);
	printf("%lld\n",dp[n]);
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