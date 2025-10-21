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
const int maxn=100010;
const int inf=1e9;
bool mbe;

int n,q,a[maxn];
int id[maxn];
int mn[18][maxn];
pii ask[maxn];
int quemn(int l,int r){
	int k=__lg(r-l+1);
	return min(mn[k][l],mn[k][r-(1<<k)+1]);
}
struct Opt{
	int p,v,w,op;
}upd[maxn*5],tmpu[maxn*5];int uu;
struct Ask{
	int p,k,w,id,fr,bk;
}que[maxn<<1],tmpq[maxn<<1];int qq;
int ans[maxn],val[maxn<<1],v[maxn<<1];
int fr[maxn<<1],bk[maxn<<1];
int pos[maxn];
void sovle(int l,int r,int ul,int ur,int ql,int qr){
	if(ql>qr)return ;
	if(l==r){
		for(int i=ql;i<=qr;i++)if(que[i].w==1)ans[que[i].id]=l;
		return ;
	}
	int mid=((long long)l+r)/2,u1=ul-1,u2=0,q1=ql-1,q2=0;
	// cout<<l<<" "<<r<<" "<<mid<<" "<<ul<<" "<<ur<<" "<<ql<<" "<<qr<<"\n";
	for(int i=ql,j=ul,s=0,j1=ul,s1=0;i<=qr;i++){
		while(j<=ur&&upd[j].p<=que[i].p){
			if(upd[j].v<=mid)s+=upd[j].w;
			j++;
		}
		while(j1<=ur&&upd[j1].p<que[i].p){
			if(upd[j1].v<=mid)s1+=upd[j1].w;
			j1++;
		}
		// cout<<i<<" "<<s<<" "<<s1<<"\n";
		if(que[i].w==-1){
			val[que[i].id]-=s1;
		}
		else{
			val[que[i].id]+=s;
		}
	}
	for(int i=ql;i<=qr;i++)fr[i]=que[i].fr,bk[i]=que[i].bk;
	for(int i=ql,j=ul,lst=0;i<=qr;i++){
		while(j<=ur&&upd[j].p<que[i].p){
			if(upd[j].v<=mid){
				if(upd[j].op)lst=upd[j].p;
			}
			j++;
		}
		fr[i]=max(fr[i],lst);
	}
	for(int i=qr,j=ur,lst=n+1;i>=ql;i--){
		while(j>=ul&&upd[j].p>que[i].p){
			if(upd[j].v<=mid){
				if(upd[j].op)lst=upd[j].p;
			}
			j--;
		}
		bk[i]=min(bk[i],lst);
	}
	for(int i=ql;i<=qr;i++){
		if(que[i].w==-1)pos[que[i].id]=i;
		else{
			// cout<<fr[i]<<" "<<bk[i]<<"\n";
			auto[l,r]=ask[que[i].id];int ii=pos[que[i].id];
			if(a[l]>mid/2&&a[r]>mid/2){
				if(l<=fr[i])v[que[i].id]+=(min(quemn(l,bk[ii]-1),quemn(fr[i]+1,r))+max(a[bk[ii]],a[fr[i]])<=mid);
			}
			else if(a[l]>mid/2){
				v[que[i].id]+=(quemn(l,bk[ii]-1)+max(a[bk[ii]],a[r])<=mid);
			}
			else if(a[r]>mid/2){
				v[que[i].id]+=(quemn(fr[i]+1,r)+max(a[l],a[fr[i]])<=mid);
			}
			if(l<=fr[i]&&a[que[i].p]>mid/2){
				v[que[i].id]-=(quemn(fr[i]+1,bk[i]-1)+max(a[fr[i]],a[bk[i]])<=mid);
			}
			if(a[que[i].p]<=mid/2&&que[i].p+1<=bk[i]-1){
				v[que[i].id]-=(quemn(que[i].p+1,bk[i]-1)+max(a[que[i].p],a[bk[i]])<=mid);
			}
		}
	}
	for(int i=ul;i<=ur;i++){
		if(upd[i].v<=mid)upd[++u1]=upd[i];
		if(upd[i].v>mid)tmpu[++u2]=upd[i];
	}
	// cout<<val[1]<<" "<<val[1]+v[1]<<" "<<que[1].k<<"\n";
	for(int i=ql;i<=qr;i++){
		if(val[que[i].id]+v[que[i].id]<que[i].k){
			que[i].k-=val[que[i].id];	
			que[i].fr=fr[i],que[i].bk=bk[i];
			tmpq[++q2]=que[i];
		}
		else{
			que[++q1]=que[i];
		}
		if(que[i].w==1)val[que[i].id]=v[que[i].id]=0;
	}
	// cout<<q1<<" "<<q2<<"\n";
	for(int i=1;i<=u2;i++)upd[u1+i]=tmpu[i];
	for(int i=1;i<=q2;i++)que[q1+i]=tmpq[i];
	sovle(l,mid,ul,u1,ql,q1);
	sovle(mid+1,r,u1+1,ur,q1+1,qr);
}
void work(){
	n=read();q=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)mn[0][i]=a[i];
	for(int j=1;j<18;j++){
		for(int i=1;i+(1<<j)-1<=n;i++)mn[j][i]=min(mn[j-1][i],mn[j-1][i+(1<<j-1)]);
	}
	for(int i=1;i<=n;i++)id[i]=i;
	sort(id+1,id+n+1,[&](int u,int v){return a[u]<a[v];});
	set<int> s;s.insert(0),s.insert(n+1);
	for(int ii=1;ii<=n;ii++){
		int i=id[ii];
		auto it=s.insert(i).fi;
		int pre=(*--it);it++;int nxt=(*++it);
		// cout<<pre<<" "<<nxt<<"\n";
		if(pre&&pre+1<=i-1){
			int vmn=quemn(pre+1,i-1);
			upd[++uu]={pre,a[i]+vmn,1,0};
			upd[++uu]={pre,2*vmn,-1,0};
		}
		if(i+1<=nxt-1){
			int vmn=quemn(i+1,nxt-1);
			upd[++uu]={i,a[i]+vmn,1,0};
			upd[++uu]={i,2*vmn,-1,0};
		}
		upd[++uu]={i,2*a[i],1,1};
	}
	// for(int i=1;i<=uu;i++)cout<<upd[i].p<<" "<<upd[i].v<<" "<<upd[i].w<<"\n";
	sort(upd+1,upd+uu+1,[&](Opt u,Opt v){return u.p<v.p;});
	for(int i=1;i<=q;i++){
		int l=read(),r=read(),k=read();ask[i]={l,r};
		if(k==1)ans[i]=2*quemn(l,r);
		else que[++qq]={l,k,-1,i,0,n+1},que[++qq]={r,k,1,i,0,n+1};
	}
	sort(que+1,que+qq+1,[&](Ask u,Ask v){return u.p<v.p;});
	sovle(0,2*inf,1,uu,1,qq);
	for(int i=1;i<=q;i++)printf("%d\n",ans[i]);
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