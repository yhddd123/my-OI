#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn=500010;

extern long long play_game(long long N, int Q, long long K, vector<long long> L, vector<long long> R);

ll n,q,k,l[maxn],r[maxn];
ll a[maxn];
ll lsh[maxn],len;
ll lsh1[maxn],len1;
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
ll mx[maxn<<2],mn[maxn<<2],tag[maxn<<2],cov[maxn<<2];
void updt(int nd,ll w){mx[nd]+=w,mn[nd]+=w,tag[nd]+=w;}
void updc(int nd,ll w){mx[nd]=mn[nd]=w,tag[nd]=0,cov[nd]=w;}
void down(int nd){
	if(cov[nd])updc(ls,cov[nd]),updc(rs,cov[nd]),cov[nd]=0;
	if(tag[nd])updt(ls,tag[nd]),updt(rs,tag[nd]),tag[nd]=0;
}
void updata(int nd,int l,int r,int ql,int qr,ll w){
	if(l>=ql&&r<=qr)return updt(nd,w);
	down(nd);
	if(ql<=mid)updata(ls,l,mid,ql,qr,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
	mx[nd]=max(mx[ls],mx[rs]);
	mn[nd]=min(mn[ls],mn[rs]);
}
void chkmx(int nd,int l,int r,int ql,int qr,ll w){
	if(mn[nd]>=w)return ;
	if(l>=ql&&r<=qr){
		if(mx[nd]<w)return updc(nd,w);
	}
	down(nd);
	if(ql<=mid)chkmx(ls,l,mid,ql,qr,w);
	if(qr>mid)chkmx(rs,mid+1,r,ql,qr,w);
	mx[nd]=max(mx[ls],mx[rs]);
	mn[nd]=min(mn[ls],mn[rs]);
}
ll query(int nd,int l,int r,int p){
	if(l==r)return mx[nd];
	down(nd);
	if(p<=mid)return query(ls,l,mid,p);
	else return query(rs,mid+1,r,p);
}
long long play_game(long long N, int Q, long long K, vector<long long> L, vector<long long> R){
	n=N,q=Q,k=K;
	for(int i=1;i<=q;i++){
		l[i]=L[i-1],r[i]=R[i-1];
		lsh[++len]=l[i],lsh[++len]=r[i]+1;
	}
	sort(lsh+1,lsh+len+1),len=unique(lsh+1,lsh+len+1)-lsh-1;
	for(int i=1;i<=q;i++){
		l[i]=lower_bound(lsh+1,lsh+len+1,l[i])-lsh,r[i]=lower_bound(lsh+1,lsh+len+1,r[i]+1)-lsh;
		a[l[i]]++,a[r[i]]--;
	}
	for(int i=1;i<=len;i++)a[i]+=a[i-1];
	for(int i=1;i<=len;i++)lsh1[++len1]=lsh[i]%k;
	sort(lsh1+1,lsh1+len1+1),len1=unique(lsh1+1,lsh1+len1+1)-lsh1-1;
	// build(1,1,len1);
	for(int i=1;i<len;i++){
		int pl=lower_bound(lsh1+1,lsh1+len1+1,lsh[i]%k)-lsh1,pr=lower_bound(lsh1+1,lsh1+len1+1,lsh[i+1]%k)-lsh1;
		if(lsh[i]/k<lsh[i+1]/k){
			// for(int j=pl;j<=len1;j++)f[j]=max(f[j-1],f[j]+a[i]);
			updata(1,1,len1,pl,len1,a[i]);
			if(pl>1)chkmx(1,1,len1,pl,len1,query(1,1,len1,pl-1));
			pl=1;
		}
		if(lsh[i]/k+1<lsh[i+1]/k){
			ll d=lsh[i+1]/k-lsh[i]/k-1;
			// for(int j=1;j<=len1;j++)f[j]+=a[i]*d;
			updt(1,a[i]*d);
		}
		if(pl<pr){
			updata(1,1,len1,pl,pr-1,a[i]);
			if(pl>1)chkmx(1,1,len1,pl,pr-1,query(1,1,len1,pl-1));
		}
		// for(int j=pl;j<pr;j++)f[j]=max(f[j-1],f[j]+a[i]);
		// cout<<lsh[i]<<" "<<lsh[i+1]-1<<" "<<pl<<" "<<pr<<" "<<a[i]<<"\n";
		// for(int j=1;j<=len1;j++)cout<<f[j]<<" ";cout<<"\n";
	}
	// ll ans=0;for(int i=1;i<=len1;i++)ans=max(ans,f[i]);
	return mx[1];
}

// int main() {
	// ios_base::sync_with_stdio(0);
	// cin.tie(0);
	// cout.tie(0);
	// int Q;
	// long long N, K;
	// cin >> N >> Q >> K;
	// vector<long long> L(Q), R(Q);
	// for(int i = 0; i < Q; i++) cin >> L[i] >> R[i];
	// cout << play_game(N, Q, K, L, R) << "\n";
// }