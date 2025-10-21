// Problem: P14231 复读机 / repeat
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P14231
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-10-21 16:31:43
// 
// Powered by CP Editor (https://cpeditor.org)

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
const int maxn=300010;
const int inf=1e9;
bool mbe;

int n,q,a[maxn];
int id[maxn],pre[maxn],nxt[maxn];
int mn[19][maxn];
int quemn(int l,int r){
	int k=__lg(r-l+1);
	return min(mn[k][l],mn[k][r-(1<<k)+1]);
}
struct opt{
	int p,v,w,op;
}upd[maxn<<2],tmpu[maxn<<2];int uu;
struct ask{
	int p,k,w,id;
}que[maxn<<1],tmpq[maxn<<1];int qq;
int ans[maxn],val[maxn],v[maxn];
int fr[maxn],bk[maxn];
void sovle(int l,int r,int ul,int ur,int ql,int qr){
	if(ql>qr)return ;
	if(l==r){
		for(int i=ql;i<=qr;i++)if(que[i].w==1)ans[que[i].id]=l;
		return ;
	}
	int mid=l+r>>1,u1=ul-1,u2=0,q1=ql-1,q2=0;
	// cout<<l<<" "<<r<<" "<<mid<<" "<<ul<<" "<<ur<<" "<<ql<<" "<<qr<<"\n";
	for(int i=ql,j=ul,s=0,lst=0;i<=qr;i++){
		while(j<=ur&&upd[j].p<=que[i].p){
			if(upd[j].v<=mid){
				s+=upd[j].w;
				if(upd[j].op)lst=upd[j].p;
			}
			j++;
		}
		if(que[i].w==-1){
			val[que[i].id]-=s;
			fr[i]=lst;
		}
		else{
			val[que[i].id]+=s;
			fr[i]=lst;
		}
	}
	for(int i=qr,j=ur,lst=n+1;i>=ql;i--){
		while(j>=ul&&upd[j].p>=que[i].p){
			if(upd[j].v<=mid){
				if(upd[j].op)lst=upd[j].p;
			}
			j--;
		}
		bk[i]=lst;
	}
	for(int i=ql;i<=qr;i++){
		if(que[i].w==-1){
			if(fr[i]<que[i].p+1&&que[i].p+1<bk[i]){
				v[que[i].id]+=(quemn(que[i].p+1,bk[i]-1)+a[bk[i]]<=mid);
			}
		}else{
			// cout<<fr[i]<<" "<<bk[i]<<"\n";
			if(fr[i]<que[i].p&&que[i].p<bk[i]){
				v[que[i].id]+=(quemn(fr[i]+1,que[i].p)+a[fr[i]]<=mid);
				v[que[i].id]-=(quemn(fr[i]+1,bk[i]-1)+max(a[fr[i]],a[bk[i]])<=mid);
			}
		}
	}
	for(int i=ul;i<=ur;i++){
		if(upd[i].v<=mid)upd[++u1]=upd[i];
		if(upd[i].v>mid)tmpu[++u2]=upd[i];
	}
	// cout<<val[1]<<" "<<val[1]+v[1]<<" "<<que[1].k<<"\n";
	for(int i=ql;i<=qr;i++){
		if(!val[que[i].id]||val[que[i].id]+v[que[i].id]<que[i].k){
			que[i].k-=val[que[i].id];	
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
	for(int j=1;j<=18;j++){
		for(int i=1;i+(1<<j)-1<=n;i++)mn[j][i]=min(mn[j-1][i],mn[j-1][i+(1<<j-1)]);
	}
	for(int i=1;i<=n;i++)id[i]=i;
	sort(id+1,id+n+1,[&](int u,int v){return a[u]<a[v];});
	set<int> s;s.insert(0),s.insert(n+1);
	for(int ii=1;ii<=n;ii++){
		int i=id[ii];
		auto it=s.insert(i).fi;
		pre[i]=(*--it);it++;nxt[i]=(*++it);
		// cout<<pre[i]<<" "<<nxt[i]<<"\n";
		if(pre[i]&&pre[i]+1<=i-1){
			int vmn=quemn(pre[i]+1,i-1);
			upd[++uu]={pre[i],a[i]+vmn,1,0};
			upd[++uu]={pre[i],2*vmn,-1,0};
		}
		if(i+1<=nxt[i]-1){
			int vmn=quemn(i+1,nxt[i]-1);
			upd[++uu]={i,a[i]+vmn,1,0};
			upd[++uu]={i,2*vmn,-1,0};
		}
		upd[++uu]={i,2*a[i],1,1};
	}
	// for(int i=1;i<=uu;i++)cout<<upd[i].p<<" "<<upd[i].v<<" "<<upd[i].w<<"\n";
	sort(upd+1,upd+uu+1,[&](opt u,opt v){return u.p<v.p;});
	for(int i=1;i<=q;i++){
		int l=read(),r=read(),k=read();
		if(k==1)printf("%d\n",quemn(l,r));
		else{
			int ll=0,rr=2*inf,ans=2*inf;
			while(ll<=rr){
				int mid=((long long)ll+rr)/2;
				int p1=0,p2=0,res=0;
				for(int j=l;j<=r;j++)if(a[j]<=mid/2){
					++res;
					if(!p1)p1=j,p2=j;
					else{
						if(p2+1<=j-1&&max(a[p2],a[j])+quemn(p2+1,j-1)<=mid){
							res++;
						}
						p2=j;
					}
				}
				// cout<<ll<<" "<<rr<<" "<<mid<<" "<<res<<"\n";
				if(l<p1&&p2<r)res+=(min(quemn(l,p1-1),quemn(p2+1,r))+max(a[p1],a[p2])<=mid);
				else if(p2<r)res+=(quemn(p2+1,r)+max(a[l],a[p2])<=mid);
				else if(l<p1)res+=(quemn(l,p1-1)+max(a[p1],a[r])<=mid);
				if(res>=k)ans=mid,rr=mid-1;
				else ll=mid+1;
			}
			printf("%lld\n",ans);
		}
	}
	// sort(que+1,que+qq+1,[&](ask u,ask v){return u.p<v.p;});
	// sovle(1,2*n,1,uu,1,qq);
	// for(int i=1;i<=q;i++)printf("%d\n",ans[i]);
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