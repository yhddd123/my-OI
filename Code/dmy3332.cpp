#include<bits/stdc++.h>
#define ll long long
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
inline void write(ll x){static char buf[20];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
const int maxn=60010;
const int maxq=600010;
const int inf=1e9;
bool mbe;

int n,m,q;
int lsh1[maxn<<5],len1,lsh2[maxn<<5],len2;
#define lb(x) (x&(-x))
struct bit1{
	int n;
	int tree[maxn<<4];
	void upd(int x,int w){
		while(x<=n)tree[x]+=w,x+=lb(x);
	}
	int que(int x){
		int res=0;
		while(x)res+=tree[x],x-=lb(x);
		return res;
	}
	int kth(int k){
		int x=0,s=0;
		for(int i=__lg(n);~i;i--){
			if(x+(1<<i)<=n&&s+tree[x+(1<<i)]<k)s+=tree[x+=(1<<i)];
		}
		return x+1;
	}
}t1,t2;
struct bit2{
	int n;
	ll tree[maxn<<4];
	void upd(int x,int w){
		while(x<=n)tree[x]+=w,x+=lb(x);
	}
	ll que(int x){
		ll res=0;
		while(x)res+=tree[x],x-=lb(x);
		return res;
	}
}t3,t4;
int s1,s2;
void upd(int k,int b,int w){
	// cout<<k<<" "<<b<<" "<<w<<" upd\n";
	if(k==-1){
		b=lower_bound(lsh1+1,lsh1+len1+1,b)-lsh1;
		s1+=w,t1.upd(b,w),t3.upd(b,w*lsh1[b]);
	}
	else{
		b=lower_bound(lsh2+1,lsh2+len2+1,b)-lsh2;
		s2+=w,t2.upd(b,w),t4.upd(b,w*lsh2[b]);
	}
}
ll que1(int x){
	int v=t1.kth(x);
	int xx=t1.que(v-1);
	return t3.que(v-1)+1ll*(x-xx)*lsh1[v];
}
ll que2(int x){
	int v=t2.kth(x);
	int xx=t2.que(v-1);
	return t4.que(v-1)+1ll*(x-xx)*lsh2[v];
}
int lsh[maxn<<6],len;
vector<pii> add1,del1,add2,del2,ask;
ll ans[maxq];
void work(){
	n=read();m=n-read();q=read();
	for(int i=1;i<=n;i++){
		int x=read(),num=0;
		lsh[++len]=x;
		add2.pb({x,-x});lsh2[++len2]=-x;
		while(x){
			lsh[++len]=(x+x/2)/2,lsh[++len]=x/2;
			if((x+x/2)/2<x)add1.pb({(x+x/2)/2,num+x}),del1.pb({x,num+x});
			if(x/2<(x+x/2)/2)add2.pb({x/2,num+1-x/2}),del2.pb({(x+x/2)/2,num+1-x/2});
			lsh1[++len1]=num+x;
			lsh2[++len2]=num+1-x/2;
			x/=2;num++;
		}
	}
	lsh[++len]=inf;
	sort(lsh+1,lsh+len+1),len=unique(lsh+1,lsh+len+1)-lsh-1;
	sort(lsh1+1,lsh1+len1+1),len1=unique(lsh1+1,lsh1+len1+1)-lsh1-1;
	sort(lsh2+1,lsh2+len2+1),len2=unique(lsh2+1,lsh2+len2+1)-lsh2-1;
	t1.n=t3.n=len1,t2.n=t4.n=len2;
	for(int i=1;i<len;i++)if(lsh[i])ask.pb({lsh[i],0});
	for(int i=1;i<=q;i++)ask.pb({read(),i});
	for(int i=0;i<=q;i++)ans[i]=6e13;
	sort(add1.begin(),add1.end());
	sort(del1.begin(),del1.end());
	sort(add2.begin(),add2.end());
	sort(del2.begin(),del2.end());
	// cout<<add1.size()<<" "<<del1.size()<<" "<<add2.size()<<" "<<del2.size()<<"\n";
	sort(ask.begin(),ask.end());
	for(int i=0,j1=0,j2=0,j3=0,j4=0,fl=0;i<ask.size();i++){
		auto[p,id]=ask[i];
		if(!id&&fl)continue;
		while(j1<add1.size()&&add1[j1].fi<=p)upd(-1,add1[j1].se,1),j1++;
		while(j2<del1.size()&&del1[j2].fi<=p)upd(-1,del1[j2].se,-1),j2++;
		while(j3<add2.size()&&add2[j3].fi<=p)upd(1,add2[j3].se,1),j3++;
		while(j4<del2.size()&&del2[j4].fi<=p)upd(1,del2[j4].se,-1),j4++;
		int l=max(0,m-s2)+1,r=min(m,s1),res=l-1;
		// cout<<l<<" "<<r<<" "<<res<<"\n";
		while(l<=r){
			int mid=l+r>>1;
			if(lsh1[t1.kth(mid)]-p<lsh2[t2.kth(m-mid+1)]+p)res=mid,l=mid+1;
			else r=mid-1;
		}
		// cout<<p<<" "<<id<<" "<<res<<" "<<s1<<" "<<s2<<"\n";
		// for(int j=1;j<=s1;j++)cout<<lsh1[t1.kth(j)]<<" ";cout<<" a\n";
		// for(int j=1;j<=s2;j++)cout<<lsh2[t2.kth(j)]<<" ";cout<<" b\n";
		// cout<<lsh1[t1.kth(res)]<<" "<<lsh2[t2.kth(m-res)]<<"\n";
		// cout<<que1(res)-res*p<<" "<<que2(m-res)<<" "<<(m-res)*p<<"\n";
		ll val=que1(res)+que2(m-res)+1ll*(m-2*res)*p;
		ans[id]=min(ans[id],val);
		if(!id&&val-10*n>=ans[id])fl=1;
		while(i+1<ask.size()&&ask[i+1].fi==p)i++,ans[ask[i].se]=val;
	}
	for(int i=0;i<=q;i++)write(ans[i]),puts("");
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen("A.out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}