// Problem: P11621 [Ynoi Easy Round 2025] TEST_139
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P11621
// Memory Limit: 512 MB
// Time Limit: 3000 ms
// Written by yhm.
// Start codeing:2025-03-24 18:14:00
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int unsigned
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0;char c=getchar();while(c<'0'||c>'9')c=getchar();while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x;}
inline void write(int x){static char buf[20];static int len=0;do buf[len++]=x%10,x/=10;while(x);while(len)putchar(buf[--len]+48);}
const int maxn=200010;
const int inf=1e9;
bool mbe;

int q,id=1;
struct node{
	int x,y,w,t,op;
}upd1[maxn<<1],upd2[maxn<<1],a[maxn*6],b[maxn*6];
int lsh[maxn<<2],len,tot1,tot2,n;
int ans[maxn];
struct bit{
	int tree[maxn<<2];
	#define lb(x) (x&(-x))
	void upd(int x,int w){
		while(x<=len)tree[x]+=w,x+=lb(x);
	}
	int que(int x){
		int res=0;
		while(x)res+=tree[x],x-=lb(x);
		return res;
	}
	int que(int l,int r){return que(r)-que(l-1);}
}t0,t1,t2,t3;
void cdq1(int l,int r){
	if(l==r)return ;
	int mid=l+r>>1;
	cdq1(l,mid),cdq1(mid+1,r);
	auto cmp=[&](node u,node v){return u.x>v.x||(u.x==v.x&&u.y>v.y)||(u.x==v.x&&u.y==v.y&&u.op<v.op);};
	// sort(a+l,a+mid+1,cmp);
	// sort(a+mid+1,a+r+1,cmp);
	auto upd=[&](int x,int y,int w){
		t0.upd(y,w);
		t1.upd(y,x*w);
		t2.upd(y,x*x*w);
	};
	// cout<<l<<" "<<r<<"\n";
	for(int i=mid+1,j=l;i<=r;i++){
		while(j<=mid&&cmp(a[j],a[i])){
			if(!a[j].op)upd(a[j].x,a[j].y,a[j].w);
			j++;
		}
		if(a[i].op){
			ans[a[i].t]+=a[i].w*(t2.que(a[i].y,len)-(a[i].x*2-3)*t1.que(a[i].y,len)+(a[i].x-1)*(a[i].x-2)*t0.que(a[i].y,len));
			// cout<<l<<" "<<r<<" "<<i<<" "<<j<<" "<<a[i].t<<" "<<ans[a[i].t]<<"\n";
		}
		if(i==r){
			for(int k=l;k<j;k++)if(!a[k].op)upd(a[k].x,a[k].y,-a[k].w);
		}
	}
	for(int i=l,j=mid+1,p=l;i<=mid&&j<=r;){
		if(cmp(a[i],a[j]))b[p++]=a[i++];
		else b[p++]=a[j++];
		if(i==mid+1){
			while(j<=r)b[p++]=a[j++];
		}
		if(j==r+1){
			while(i<=mid)b[p++]=a[i++];
		}
	}
	for(int i=l;i<=r;i++)a[i]=b[i];
}
void cdq2(int l,int r){
	if(l==r)return ;
	int mid=l+r>>1;
	cdq2(l,mid),cdq2(mid+1,r);
	auto cmp=[&](node u,node v){return u.x>v.x||(u.x==v.x&&u.y<v.y);};
	auto upd=[&](int x,int y,int w){
		t0.upd(y,w);
		t1.upd(y,x*w);
		t2.upd(y,x*x*w);
	};
	for(int i=mid+1,j=l;i<=r;i++){
		while(j<=mid&&cmp(a[j],a[i])){
			if(!a[j].op)upd(a[j].x,a[j].y,a[j].w);
			j++;
		}
		if(a[i].op){
			ans[a[i].t]+=a[i].w*(t2.que(1,a[i].y-1)-(a[i].x*2-3)*t1.que(1,a[i].y-1)+(a[i].x-1)*(a[i].x-2)*t0.que(1,a[i].y-1));
			// cout<<l<<" "<<r<<" "<<i<<" "<<j<<" "<<a[i].t<<" "<<ans[a[i].t]<<"\n";
		}
		if(i==r){
			for(int k=l;k<j;k++)if(!a[k].op)upd(a[k].x,a[k].y,-a[k].w);
		}
	}
	for(int i=l,j=mid+1,p=l;i<=mid&&j<=r;){
		if(cmp(a[i],a[j]))b[p++]=a[i++];
		else b[p++]=a[j++];
		if(i==mid+1){
			while(j<=r)b[p++]=a[j++];
		}
		if(j==r+1){
			while(i<=mid)b[p++]=a[i++];
		}
	}
	for(int i=l;i<=r;i++)a[i]=b[i];
}
void cdq3(int l,int r){
	if(l==r)return ;
	int mid=l+r>>1;
	cdq3(l,mid),cdq3(mid+1,r);
	auto cmp=[&](node u,node v){return u.x>v.x||(u.x==v.x&&u.y>v.y)||(u.x==v.x&&u.y==v.y&&u.op<v.op);};
	auto upd=[&](int x,int y,int w){
		t0.upd(y,w);
		t1.upd(y,x*w);
		t2.upd(y,lsh[y]*w);
		t3.upd(y,x*lsh[y]*w);
	};
	for(int i=mid+1,j=l;i<=r;i++){
		while(j<=mid&&cmp(a[j],a[i])){
			if(!a[j].op)upd(a[j].x,a[j].y,a[j].w);
			j++;
		}
		if(a[i].op){
			ans[a[i].t]+=2*a[i].w*(t3.que(a[i].y,len)-(a[i].x-1)*t2.que(a[i].y,len)-(lsh[a[i].y]-1)*t1.que(a[i].y,len)+(a[i].x-1)*(lsh[a[i].y]-1)*t0.que(a[i].y,len));
			// cout<<l<<" "<<r<<" "<<i<<" "<<j<<" "<<a[i].t<<" "<<ans[a[i].t]<<"\n";
		}
		if(i==r){
			for(int k=l;k<j;k++)if(!a[k].op)upd(a[k].x,a[k].y,-a[k].w);
		}
	}
	for(int i=l,j=mid+1,p=l;i<=mid&&j<=r;){
		if(cmp(a[i],a[j]))b[p++]=a[i++];
		else b[p++]=a[j++];
		if(i==mid+1){
			while(j<=r)b[p++]=a[j++];
		}
		if(j==r+1){
			while(i<=mid)b[p++]=a[i++];
		}
	}
	for(int i=l;i<=r;i++)a[i]=b[i];
}
void work(){
	q=read();
	while(q--){
		int op=read();
		if(op==1){
			int x=read(),y=read(),d=read(),w=read();
			upd1[++tot1]={x+d-1,y,w,id,0},upd1[++tot1]={x-1,y+d,-w,id,0};
			upd2[++tot2]={x-1,y+d-1,-w,id,0},upd2[++tot2]={x-1,y-1,w,id,0};
			lsh[++len]=y,lsh[++len]=y+d,lsh[++len]=y+d-1,lsh[++len]=y-1;
		}
		else{
			int x=read(),u=read(),y=read(),v=read();
			a[++n]={x,y,1,id,1},a[++n]={u+1,v+1,1,id,1};
			a[++n]={x,v+1,(int)-1,id,1},a[++n]={u+1,y,(int)-1,id,1};
			lsh[++len]=y,lsh[++len]=v+1;
			++id;
		}
	}
	sort(lsh+1,lsh+len+1),len=unique(lsh+1,lsh+len+1)-lsh-1;
	for(int i=1;i<=tot1;i++)upd1[i].y=lower_bound(lsh+1,lsh+len+1,upd1[i].y)-lsh;
	for(int i=1;i<=tot2;i++)upd2[i].y=lower_bound(lsh+1,lsh+len+1,upd2[i].y)-lsh;
	for(int i=1;i<=n;i++)a[i].y=lower_bound(lsh+1,lsh+len+1,a[i].y)-lsh;
	for(int i=1;i<=tot1;i++)a[++n]=upd1[i];
	auto cmp=[&](node u,node v){
		return u.t<v.t||(u.t==v.t&&u.op<v.op)||(u.t==v.t&&u.op==v.op&&u.x>v.x)||(u.t==v.t&&u.op==v.op&&u.x==v.x&&u.y>v.y);
	};
	auto cmp1=[&](node u,node v){
		return u.t<v.t||(u.t==v.t&&u.op<v.op)||(u.t==v.t&&u.op==v.op&&u.x>v.x)||(u.t==v.t&&u.op==v.op&&u.x==v.x&&u.y<v.y);
	};
	sort(a+1,a+n+1,cmp);
	cdq1(1,n);
	for(int i=1;i<=n;i++)a[i].x=a[i].x+lsh[a[i].y];
	sort(a+1,a+n+1,cmp1);
	cdq2(1,n);
	for(int i=1;i<=n;i++)a[i].x=a[i].x-lsh[a[i].y];
	sort(a+1,a+n+1,[&](node u,node v){return u.op<v.op;});
	for(int i=1;i<=tot2;i++)a[i]=upd2[i];
	sort(a+1,a+n+1,cmp);
	cdq3(1,n);
	// for(int i=1;i<id;i++)cout<<ans[i]<<" ";cout<<"\n";
	for(int i=1;i<id;i++)write((ans[i]<<1)>>2),puts("");
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