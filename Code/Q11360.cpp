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

int n,k,a[maxn],ans;
int s[maxn],lsh[maxn],len;
#define mid ((l+r)>>1)
#define ls lc[nd]
#define rs rc[nd]
int tree[maxn<<5],lc[maxn<<5],rc[maxn<<5],rt[maxn],idx;
void updata(int &nd,int l,int r,int p){
	int lst=nd;nd=++idx;tree[nd]=tree[lst]+1,ls=lc[lst],rs=rc[lst];
	if(l==r)return ;
	if(p<=mid)updata(ls,l,mid,p);
	else updata(rs,mid+1,r,p);
}
int query(int nd,int l,int r,int ql,int qr){
	if(!nd||ql>qr)return 0;
	if(l>=ql&&r<=qr)return tree[nd];
	if(qr<=mid)return query(ls,l,mid,ql,qr);
	if(ql>mid)return query(rs,mid+1,r,ql,qr);
	return query(ls,l,mid,ql,qr)+query(rs,mid+1,r,ql,qr);
}
int mx[18][maxn];
int mmax(int u,int v){return a[u]>a[v]?u:v;}
int que(int l,int r){
	int k=__lg(r-l+1);
	return mmax(mx[k][l],mx[k][r-(1<<k)+1]);
}
int lson[maxn],rson[maxn],pl[maxn],pr[maxn];
int build(int l,int r){
	if(l>r)return 0;
	int u=que(l,r);pl[u]=l,pr[u]=r;
	lson[u]=build(l,u-1),rson[u]=build(u+1,r);
	return u;
}
void dfs(int u){
	if(!u||a[u]<0)return ;
	// cout<<u<<" "<<a[u]<<" "<<pl[u]<<" "<<pr[u]<<"\n";
	if(u-pl[u]<=pr[u]-u){
		for(int i=pl[u]-1;i<u;i++){
			int v=lsh[s[i]]+a[u]*(k+1);
			int p=lower_bound(lsh+1,lsh+len+1,v)-lsh;
			ans+=query(rt[pr[u]],1,len,p,len)-query(rt[u-1],1,len,p,len);
		}
	}
	else{
		for(int i=u;i<=pr[u];i++){
			int v=lsh[s[i]]-a[u]*(k+1);
			int p=upper_bound(lsh+1,lsh+len+1,v)-lsh-1;
			ans+=query(rt[u-1],1,len,1,p)-(pl[u]>1?query(rt[pl[u]-2],1,len,1,p):0);
		}
	}
	// for(int i=pl[u]-1;i<u;i++){
		// for(int j=u;j<=pr[u];j++)ans+=(lsh[s[j]]-lsh[s[i]]-a[u]*(k+1)>=0);
	// }
	dfs(lson[u]),dfs(rson[u]);
}
void work(){
	n=read();k=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)a[i]-=read();
	for(int i=1;i<=n;i++)s[i]=s[i-1]+(a[i]>=0?a[i]:k*a[i]);
	// for(int i=1;i<=n;i++)cout<<a[i]<<" ";cout<<"\n";
	// for(int i=1;i<=n;i++)cout<<s[i]<<" ";cout<<"\n";
	for(int i=0;i<=n;i++)lsh[++len]=s[i];
	sort(lsh+1,lsh+len+1),len=unique(lsh+1,lsh+len+1)-lsh-1;
	for(int i=0;i<=n;i++)s[i]=lower_bound(lsh+1,lsh+len+1,s[i])-lsh;
	for(int i=0;i<=n;i++)updata(rt[i]=(i?rt[i-1]:0),1,len,s[i]);
	for(int i=1;i<=n;i++)mx[0][i]=i;
	for(int j=1;j<18;j++){
		for(int i=1;i+(1<<j)-1<=n;i++)mx[j][i]=mmax(mx[j-1][i],mx[j-1][i+(1<<j-1)]);
	}
	int rt=build(1,n);
	dfs(rt);
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