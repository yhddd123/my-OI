#include<bits/stdc++.h>
#define int unsigned
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0;char ch=getchar();
	while(ch<'0'||ch>'9'){ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x;
}
const int maxn=100010;
const int inf=1e9;
bool mbe;

int n,q,a[maxn],b[maxn],tmp[maxn];
const int B=500;
const int maxm=maxn/B+5;
int pl[maxm],pr[maxm],Bnum,bel[maxn];
const int BB=9;
struct DS{
	int s1[(maxn>>BB)+5],s2[maxn];
	void upd(int p,int w){
		for(int i=(p>>BB)+1;i<=(n+1>>BB);i++)s1[i]+=w;
		int pr=min(n+1,(((p>>BB)+1)<<BB)-1);
		for(int i=p;i<=pr;i++)s2[i]+=w;
	}
	inline int que(int p){return s1[p>>BB]+s2[p];}
	inline int que(int l,int r){return que(r)-que(l-1);}
	void clr(){
		for(int i=0;i<=(n+1)>>BB;i++)s1[i]=0;
		for(int i=0;i<=n+1;i++)s2[i]=0;
	}
}ka,ba,num,sum;
void upda(int l,int r,int w){
	ka.upd(l,w),ka.upd(r+1,-w);
	ba.upd(l,-w*(l-1)),ba.upd(r+1,w*r);
}
inline int quea(int p){return ka.que(p)*p+ba.que(p);}
struct node{
	int l,r,c;
	bool operator<(const node&tmp)const{return r<tmp.l;}
};
struct odt{
	set<node> s;
	void split(int p){
		auto it=s.lower_bound({p,p,0});
		if(it!=s.end()&&(*it).r>p){
			auto[l,r,c]=*it;
			s.erase(it);
			s.insert({l,p,c}),s.insert({p+1,r,c});
		}
	}
	vector<node> ins(int l,int r,int c){
		vector<node> res;
		if(l-1)split(l-1);split(r);
		auto it=s.lower_bound({l,l,0});
		while(it!=s.end()&&(*it).r<=r){
			res.pb(*it);
			it=s.erase(it);
		}
		s.insert({l,r,c});
		return res;
	}
	void init(int *a){
		for(int i=1;i<=n;i++)s.insert({i,i,a[i]});
	}
}ta,tb;
int cov[maxm],ans[maxm];
void down(int id){
	int l=pl[id],r=pr[id];
	if(cov[id]){
		for(int i=l;i<=r;i++)b[i]=cov[id];
		cov[id]=0;
	}
}
void init(int id){
	int l=pl[id],r=pr[id];
	ans[id]=0;for(int i=l;i<=r;i++)ans[id]+=quea(b[i]);
}
void mdfa(int p,int w){
	for(int id=1;id<=Bnum;id++){
		if(cov[id])ans[id]=(pr[id]-pl[id]+1)*quea(cov[id]);
	}
}
void mdfb(int l,int r,int w){
	if(bel[l]==bel[r]){
		down(bel[l]);
		for(int i=l;i<=r;i++)b[i]=w;
		init(bel[l]);
		return;
	}
	else{
		down(bel[l]);
		for(int i=l;i<=pr[bel[l]];i++)b[i]=w;
		init(bel[l]);
		for(int id=bel[l]+1;id<=bel[r]-1;id++){
			cov[id]=w;
			ans[id]=(pr[id]-pl[id]+1)*quea(w);
		}
		down(bel[r]);
		for(int i=pl[bel[r]];i<=r;i++)b[i]=w;
		init(bel[r]);
	}
}
void updb(int w,int o){num.upd(w,o),sum.upd(w,o*w);}
void updb(int l,int r,int w1,int w2){
	if(bel[l]==bel[r]){
		updb(bel[l],w1,-(r-l+1)),updb(bel[l],w2,r-l+1);
		return;
	}
	else{
		updb(bel[l],w1,-(pr[bel[l]]-l+1)),updb(bel[l],w2,pr[bel[l]]-l+1);
		for(int id=bel[l]+1;id<=bel[r]-1;id++){
			updb(id,w1,-(pr[id]-pl[id]+1)),updb(id,w2,pr[id]-pl[id]+1);
		}
		updb(bel[r],w1,-(r-pl[bel[r]]+1)),updb(bel[r],w2,r-pl[bel[r]]+1);
	}
}
int queb(int l,int r){
	int res=0;
	if(bel[l]==bel[r]){
		down(bel[l]);
		init(bel[l]);
		for(int i=l;i<=r;i++)res+=quea(b[i]);
	}
	else{
		down(bel[l]);
		init(bel[l]);
		for(int i=l;i<=pr[bel[l]];i++)res+=quea(b[i]);
		for(int id=bel[l]+1;id<=bel[r]-1;id++)res+=ans[id];
		down(bel[r]);
		init(bel[r]);
		for(int i=pl[bel[r]];i<=r;i++)res+=quea(b[i]);
	}
	return res;
}
vector<node> mdf[maxn];
tuple<int,int,int,int> ask[maxn];
int res[maxn];
void work(){
	n=read();q=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();
	for(int l=1,r;l<=n+1;l=r+1){
		r=min(l+B-1,n+1);pl[++Bnum]=l,pr[Bnum]=r;
		for(int i=l;i<=r;i++)bel[i]=Bnum;
	}
	ta.init(a),tb.init(b);
	for(int i=1;i<=n;i++)ba.upd(i,a[i]);
	for(int id=1;id<=Bnum;id++){
		int l=pl[id],r=pr[id];
		init(id);
	}
	for(int i=1;i<=n;i++)tmp[i]=b[i];
	for(int i=1;i<=q;i++){
		int op=read(),l,r,c;
		if(op==1){
			l=read(),r=read(),c=read();
			mdf[i]=ta.ins(l,r,c);
			for(auto [ll,rr,cc]:va){
				cc=c-cc;
				upda(ll,rr,cc);
				if(ll>1)mdfa(ll-1,-cc);
				mdfa(rr,cc);
			}
		}
		if(op==2){
			l=read(),r=read(),c=read();
			mdf[i]=tb.ins(l,r,c);
			mdfb(l,r,c);
		}
		if(op==3){
			l=read(),r=read();
			res[i]+=queb(l,r);
		}
		ask[i]={op,l,r,c};
		// for(int i=1;i<=n;i++)cout<<ans[i]<<" "<<sum[i].que(n)<<"\n";
	}
	for(int i=1;i<=n;i++)b[i]=tmp[i];
	for(int id=1;id<=Bnum;id++){
		cov[id]=ans[id]=0;
		auto mdfa1=[&](int p,int w){
			ans[id]+=(num.que(p+1,n)*p+sum.que(1,p))*w;
		};
		auto in=[&](int l,int r){return l<=id&&id<=r;};
		auto mdfb1=[&](int l,int r,int w){
			if(id==bel[l]||id==bel[r])cov[id]=ans[id]=0;
			else if(in(bel[l]+1,bel[r]-1))cov[id]=w,ans[id]=0;
		};
		auto updb1=[&](int l,int r,int w1,int w2){
			if(bel[l]==bel[r]){
				if(id==bel[l])upd(w1,-(r-l+1)),upd(w2,r-l+1);
			}
			else{
				if(id==bel[l])upd(w1,-(pr[id]-l+1)),upd(w2,pr[id]-l+1);
				else if(in(bel[l]+1,bel[r]-1))upd(w1,-(pr[id]-pl[id]+1)),upd(w2,pr[id]-pl[id]+1);
				else if(id==bel[r])upd(w1,-(r-pl[id]+1)),upd(w2,r-pl[id]+1);
			}
		};
		auto queb1=[&](int l,int r){
			
		};
		num.clr(),sum.clr();
		for(int i=l;i<=r;i++)updb(b[i],1);
		for(int i=1;i<=q;i++){
			auto[op,l,r,c]=ask[i];
			if(op==1){
				for(auto[ll,rr,cc]:mdf[i]){
					if(ll>1)mdfa1(ll-1,-cc);
					mdfa1(rr,cc);
				}
			}
			if(op==2){
				for(auto[ll,rr,cc]:mdf[i]){
					updb1(ll,rr,cc,c);
				}
				mdfb1(l,r,c);
			}
			if(op==3)res[i]+=queb1(l,r);
		}
	}
	for(int i=1;i<=q;i++)if(get<0>(ask[i])==3)printf("%u\n",res[i]);
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