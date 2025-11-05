#include<bits/stdc++.h>
// #define int long long
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
const int maxn=1000010;
const int N=1e6;
const int inf=1e9;
bool mbe;

#define all 1,-N,N
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
struct sgt{
	int mx[maxn<<3];
	multiset<int> s[maxn<<1];
	void build(int nd,int l,int r){
	    mx[nd]=-inf;
	    if(l==r){s[l+maxn].insert(-inf);return ;}
	    build(ls,l,mid),build(rs,mid+1,r);
	}
	void modif(int nd,int l,int r,int p,int w,int o){
	    if(l==r){
	    	if(o)s[l+maxn].insert(w);
	    	else s[l+maxn].erase(s[l+maxn].find(w));
	    	mx[nd]=*--s[l+maxn].end();
	    	return ;
	    }
	    if(p<=mid)modif(ls,l,mid,p,w,o);
	    else modif(rs,mid+1,r,p,w,o);
	    mx[nd]=max(mx[ls],mx[rs]);
	}
	int query(int nd,int l,int r,int ql,int qr){
	    if(l>=ql&&r<=qr)return mx[nd];
	    if(qr<=mid)return query(ls,l,mid,ql,qr);
	    if(ql>mid)return query(rs,mid+1,r,ql,qr);
	    return max(query(ls,l,mid,ql,qr),query(rs,mid+1,r,ql,qr));
	}
}t1,t2;
int q;
void work(){
	t1.build(all);
	t2.build(all);
	q=read();
	while(q--){
		int op=read();
		if(op==1){
			int a=read(),b=read();
			t1.modif(all,a-b,a,1);
			t2.modif(all,a-b,b,1);
		}else if(op==2){
			int a=read(),b=read();
			t1.modif(all,a-b,a,0);
			t2.modif(all,a-b,b,0);
		}else{
			int x=read();
			printf("%d\n",max(t1.query(all,-N,x),t2.query(all,x,N)+x));
		}
	}
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