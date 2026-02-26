#include<bits/stdc++.h>
#define ll long long
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
inline ll read(){ll x=0;char c=getchar();while(c<'0'||c>'9')c=getchar();while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x;}
inline void write(ll x){static char buf[20];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
const int maxn=500010;
const ll inf=1e18;
bool mbe;

int n,q;ll k,a[maxn],tim;
ll lshk[maxn],lenk;
ll lshb[maxn],lenb;
#define mid ((l+r)>>1)
#define ls lc[nd]
#define rs rc[nd]
int num[maxn<<6],lc[maxn<<6],rc[maxn<<6],rt[maxn],idx,nw;
void modif(int &nd,int l,int r,int p,int w){
	if(!nd)nd=++idx;num[nd]+=w;
	if(l==r)return ;
	if(p<=mid)modif(ls,l,mid,p,w);
	else modif(rs,mid+1,r,p,w);
}
int query(int nd,int l,int r,int ql,int qr){
	if(!nd||ql>qr)return 0;
	if(l>=ql&&r<=qr)return num[nd];
	if(qr<=mid)return query(ls,l,mid,ql,qr);
	if(ql>mid)return query(rs,mid+1,r,ql,qr);
	return query(ls,l,mid,ql,qr)+query(rs,mid+1,r,ql,qr);
}
int find(int nd,int l,int r,int k){
	if(l==r)return l;
	if(num[ls]>=k)return find(ls,l,mid,k);
	else return find(rs,mid+1,r,k-num[ls]);
}
int merge(int u,int v,int l,int r){
	if(!u||!v)return u|v;
	if(l==r){
		int nd=++idx;
		num[nd]=num[u]+num[v];
		return nd;
	}
	int nd=++idx;
	ls=merge(lc[u],lc[v],l,mid),rs=merge(rc[u],rc[v],mid+1,r);
	num[nd]=num[ls]+num[rs];
	return nd;
}
void work(){
	n=read();q=read();k=read();
	for(int i=1;i<=n;i++)a[i]=read();
	sort(a+1,a+n+1,greater<ll>());
	for(int i=1;i<=n;i++)lshk[++lenk]=a[i]/k,lshb[++lenb]=a[i]%k;
	sort(lshk+1,lshk+lenk+1),sort(lshb+1,lshb+lenb+1);
	lenk=unique(lshk+1,lshk+lenk+1)-lshk-1,lenb=unique(lshb+1,lshb+lenb+1)-lshb-1;
	for(int i=1;i<=n;i++){
		int p=lower_bound(lshk+1,lshk+lenk+1,a[i]/k)-lshk;
		int r=lower_bound(lshb+1,lshb+lenb+1,a[i]%k)-lshb;
		r=lenb-r+1;
		modif(rt[p],1,lenb,r,1);
	}
	reverse(lshb+1,lshb+lenb+1);
	nw=rt[lenk];
	if(lshk[lenk]==lshk[lenk-1]+1)nw=merge(nw,rt[lenk-1],1,lenb);
	lshk[0]=-inf;
	// cout<<num[nw]<<"\n";
	while(q--){
		char ch=getchar();
		while(ch!='A'&&ch!='C')ch=getchar();
		if(ch=='A'){
			// cout<<tim<<" "<<lenk<<" "<<lshk[lenk]<<" "<<lshk[lenk-1]<<" "<<num[nw]<<"\n";
			int t=read();
			if(lshk[lenk]==lshk[lenk-1]+1){
				if(t<=num[nw]){
					int p=tim?find(rt[lenk],1,lenb,tim):0;
					int q=query(nw,1,lenb,1,p-1)+tim-query(rt[lenk],1,lenb,1,p-1);
					// cout<<lshb[p]<<" "<<q<<"\n";
					if(t<=num[rt[lenk]]-tim){
						ll ans=lshb[find(rt[lenk],1,lenb,tim+t)]+lshk[lenk]*k;
						write(ans),puts("");
					}
					else if(t<=num[rt[lenk]]-tim+q){
						ll ans=lshb[find(nw,1,lenb,t-(num[rt[lenk]]-tim))]+lshk[lenk-1]*k;
						write(ans),puts("");
					}
					else{
						ll ans=lshb[find(rt[lenk-1],1,lenb,t-(num[rt[lenk]]-tim+q)+query(rt[lenk-1],1,lenb,1,p-1))]+lshk[lenk-1]*k;
						write(ans),puts("");
					}
				}
				else write(a[t]),puts("");
			}
			else{
				if(t<=num[nw]){
					if(t<=num[nw]-tim){
						ll ans=lshb[find(nw,1,lenb,tim+t)]+lshk[lenk]*k;
						write(ans),puts("");
					}
					else{
						ll ans=lshb[find(nw,1,lenb,t-(num[nw]-tim))]+(lshk[lenk]-1)*k;
						write(ans),puts("");
					}
				}
				else write(a[t]),puts("");
			}
		}
		else{
			tim+=read();
			while(1){
				if(lshk[lenk]==lshk[lenk-1]+1){
					if(tim>=num[rt[lenk]]){
						tim-=num[rt[lenk]],lenk--;
						rt[lenk]=nw;
						if(lshk[lenk]==lshk[lenk-1]+1)nw=merge(nw,rt[lenk-1],1,lenb);
					}
					else break;
				}
				else{
					ll d=min(tim/num[nw],lshk[lenk]-lshk[lenk-1]-1);
					if(d){
						lshk[lenk]-=d,tim-=d*num[nw];
						if(lshk[lenk]==lshk[lenk-1]+1){
							nw=merge(nw,rt[lenk-1],1,lenb);
						}
						else break;
					}
					else break;
				}
			}
		}
	}
}

bool med;
signed main(){
	// freopen("a.in","r",stdin);
	// freopen("a.out","w",stdout);
	
	cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	int T=1;
	while(T--)work();
}