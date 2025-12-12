#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=50010;
const ll inf=1e18;

int n,qq,ql,qr;
ll a[maxn],mx[16][maxn];
int lg[maxn];
inline ll quemx(int l,int r){
	r=min(r,n);
	if(l>r)return -inf;
	int k=lg[r-l+1];
	return max(mx[k][l],mx[k][r-(1<<k)+1]);
}
pii q[maxn<<1];int h,t;
ll res[16][maxn];
inline void chkmx(ll &u,ll v){(u<v)&&(u=v);}
inline void upd(int l,int r,ll w){
	int k=lg[r-l+1];
	chkmx(res[k][l],w),chkmx(res[k][r-(1<<k)+1],w);
}
inline void add(int l,int r){
	// cout<<l<<" "<<r<<" "<<quemx(r+ql,l+qr)<<" a\n";
	upd(l,r,quemx(r+ql,l+qr)-a[l]);
}
void sovle(){
	for(int j=0;j<16;j++){
		for(int i=0;i<=n;i++)res[j][i]=-inf;
	}
	h=n+1,t=n;
	ll lst=inf;
	for(int i=n-qr;i<=n-ql;i++){
		(a[i]<lst)?(q[--h]={i,i},lst=a[i]):(q[h].se=i);
	}
	// for(int i=n-ql;i>=n-qr;i--){
		// while(h<=t&&a[q[t].fi]>=a[i])t--;
		// (h>t)?(q[++t]={i,n-ql}):(++t,q[t]={i,q[t-1].fi-1});
	// }
	upd(q[h].fi,n-1,a[n]-a[q[h].fi]);
	for(int i=n-1;i;i--){
		if(h<=t&&q[h].se==i-ql+1){
			add(q[h].fi,q[h].se);
			q[h].se--;
			(q[h].fi>q[h].se)&&(h++);
		}
		if(i>=qr){
			while(h<=t&&a[q[t].fi]>=a[i-qr])add(q[t].fi,q[t].se),t--;
			(h>t)?(q[++t]={i-qr,i-ql}):(++t,q[t]={i-qr,q[t-1].fi-1});	
		}
		(i>=ql)&&(upd(q[h].fi,i-1,a[i]-a[q[h].fi]),0);
		// cout<<i<<endl;
		// for(int j=h;j<=t;j++)cout<<q[j].fi<<" "<<q[j].se<<"\n";
	}
	while(h<=t)add(q[h].fi,q[h].se),h++;
	for(int j=15;j;j--){
		for(int i=0;i+(1<<j)-1<n;i++)chkmx(res[j-1][i],res[j][i]),chkmx(res[j-1][i+(1<<j-1)],res[j][i]);
	}
	ull ans=0;
	for(int i=0;i<n;i++)ans^=(i+1)*res[0][i];
	printf("%llu\n",ans);
}
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=a[i-1]+read();
	// for(int i=1;i<=n;i++)cout<<a[i]<<" ";cout<<"\n";
	for(int i=0;i<=n;i++)mx[0][i]=a[i];
	for(int j=1;j<16;j++){
		for(int i=1;i+(1<<j)-1<=n;i++)chkmx(mx[j][i]=mx[j-1][i],mx[j-1][i+(1<<j-1)]);
	}
	lg[0]=-1;for(int i=1;i<=n;i++)lg[i]=lg[i>>1]+1;
	qq=read();
	while(qq--){
		ql=read(),qr=read();
		sovle();
	}
}


int T;
signed main(){
	// freopen("query.in","r",stdin);
	// freopen("query.out","w",stdout);
	
	T=1;
	while(T--)work();
}