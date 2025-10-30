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
const int maxn=100010;
const int maxq=300010;
const int B=300;
const int inf=1e9;
bool mbe;

int n,q;
struct node{
	int u,v,w,t;
}upd[maxn],que[maxq<<2],tmpu[maxn],tmpq[maxq<<2];int uu,qq;
bool vis[maxq];
int ans[maxq];
struct Ds{
	int v1[maxn],v2[maxn];
	void upd(int p,int w){
		for(int i=p/B+1;i<=n/B;i++)v1[i]+=w;
		for(int i=p;i<(p/B+1)*B;i++)v2[i]+=w;
	}
	int que(int p){
		return v1[p/B]+v2[p];
	}
}t1,t2;
void calc(int ul,int ur,int ql,int qr){
	if(ul>qr||ql>qr)return ;
	for(int i=ql,j=ul;i<=qr;i++){
		while(j<=ur&&upd[j].u<=que[i].u){
			t1.upd(upd[j].v,upd[j].u*upd[j].v*upd[j].w);
			j++;
		}
	}
}
void sovle(int l,int r,int ul,int ur,int ql,int qr){
	if(ul>ur){
		sort(que+ql,que+qr+1,[&](node u,node v){return u.u<v.u;});
		return ;
	}
	if(ql>qr){
		sort(upd+ul,upd+ur+1,[&](node u,node v){return u.u<v.u;});
		return ;
	}
	int mid=l+r>>1;
	int up=ul-1,qp=ql-1;
	for(int i=ul;i<=ur;i++){
		if(upd[i].t>mid)break;
		up=i;
	}
	for(int i=ql;i<=qr;i++){
		if(que[i].t>mid)break;
		qp=i;
	}
	sovle(l,mid,ul,up,ql,qp),sovle(mid+1,r,up+1,ur,qp+1,qr);
	calc(ul,up,qp+1,qr);
	int p1=ul,p2=up+1,p=0;
	while(p1<=up&&p2<=ur){
		if(upd[p1].u<=upd[p2].u)tmpu[++p]=upd[p1++];
		else tmpu[++p]=upd[p2++];
	}
	while(p1<=up)tmpu[++p]=upd[p1++];
	while(p2<=ur)tmpu[++p]=upd[p2++];
	for(int i=ul;i<=ur;i++)upd[i]=tmpu[i-ul+1];
	p1=ql,p2=qp+1,p=0;
	while(p1<=qp&&p2<=qr){
		if(que[p1].u<=que[p2].u)tmpq[++p]=que[p1++];
		else tmpq[++p]=que[p2++];
	}
	while(p1<=qp)tmpq[++p]=que[p1++];
	while(p2<=qr)tmpq[++p]=que[p2++];
	for(int i=ql;i<=qr;i++)que[i]=tmpq[i-ql+1];
}
void work(){
	n=read();q=read();
	set<int> sx,sy;
	sx.insert(0),sx.insert(n),sy.insert(0),sy.insert(n);
	for(int i=1;i<=q;i++){
		int op=read();
		if(op==1){
			int o=read(),p=read();
			if(!o)sx.insert(p);
			else sy.insert(q);
		}
		if(op==2){
			int u=read(),v=read(),w=read();
			int l1=*--sx.lower_bound(u),r1=sx.lower_bound(u);
			int l2=*--sy.lower_bound(v),r2=sy.lower_bound(v);
			upd[++uu]={r1,r2,w,i};
			if(l1-1)upd[++uu]={l1-1,r2,-w,i};
			if(l2-1)upd[++uu]={r1,l2-1,-w,i};
			if(ll-1&&rr-1)upd[++uu]={l1-1,l2-1,w,i};
		}
		if(op==3){
			vis[i]=1;
			int l1=read(),r1=read(),l2=read(),r2=read();
			que[++qq]={r1,r2,w,i};
			if(l1-1)que[++qq]={l1-1,r2,-w,i};
			if(l2-1)que[++qq]={r1,l2-1,-w,i};
			if(ll-1&&rr-1)que[++qq]={l1-1,l2-1,w,i};	
		}
	}
	sovle(1,q,1,uu,1,qq);
	for(int i=1;i<=q;i++)if(vis[i])printf("%lld\n",ans[i]);
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