#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1000000007
#define pii pair<int,int>
#define mems(x,y) memset(x,y,sizeof x)
using namespace std;
const int maxn=1000010;
const int inf=1e18;
const db eps=1e-8;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,q;
int v[maxn];
struct ask{
	int op,x,y,k,id;
}p[maxn],p1[maxn],p2[maxn];
int ans[maxn],idx;
vector<int> a[maxn];
int lowbit(int x){return x&(-x);}
struct bit{
	int c[maxn];
	void clear(){memset(c,0,sizeof(c));}
	void updata(int x,int w){
		while(x<=m){
			c[x]+=w;
			x+=lowbit(x);
		}
	}
	int query(int x){
		int res=0;
		while(x){
			res+=c[x];
			x-=lowbit(x);
		}
		return res;
	}
}tr;
void sovle(int l,int r,int ql,int qr){
	if(l==r){
		for(int i=ql;i<=qr;i++)if(p[i].op==1)ans[p[i].id]=l;
		return ;
	}
	int mid=l+r>>1,h1=0,h2=0;
	for(int i=ql;i<=qr;i++){
		if(p[i].op==2){
			if(p[i].id<=mid){
				tr.updata(p[i].x,p[i].k);
				tr.updata(p[i].y+1,-p[i].k);
				p1[++h1]=p[i];
			}
			else p2[++h2]=p[i];
		}
		else{
			int num=0;
			for(int j:a[p[i].id]){
				num+=tr.query(j);
				if(num>=p[i].k)break;
			}
			if(p[i].k<=num)p1[++h1]=p[i];
			else{
				p[i].k-=num;
				p2[++h2]=p[i];
			}
		}
//		cout<<p[i].x<<" "<<p[i].y<<" "<<p[i].id<<" "<<p[i].op<<" "<<p[i].k<<" "<<i<<" "<<h1<<" "<<h2<<"\n";
	}
	for(int i=ql;i<=qr;i++)if(p[i].op==2&&p[i].id<=mid){
		tr.updata(p[i].x,-p[i].k);
		tr.updata(p[i].y+1,p[i].k);
	}
	int h=ql;
	for(int i=1;i<=h1;i++)p[h++]=p1[i];
	for(int i=1;i<=h2;i++)p[h++]=p2[i];
//	cout<<l<<" "<<r<<" "<<ql<<" "<<qr<<" "<<h1<<" "<<h2<<"\n";
	sovle(l,mid,ql,ql+h1-1);sovle(mid+1,r,ql+h1,qr);
}
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++)a[read()].push_back(i);
	for(int i=1;i<=n;i++)v[i]=read();
	q=read();
	for(int i=1;i<=q;i++){
		int l=read(),r=read(),w=read();
		if(l<=r)p[++idx]={2,l,r,w,i};
		else p[++idx]={2,l,m,w,i},p[++idx]={2,1,r,w,i};
	}
	for(int i=1;i<=n;i++)p[++idx]={1,0,0,v[i],i};
	sovle(1,q+1,1,idx);
	for(int i=1;i<=n;i++){
		if(ans[i]<=q)printf("%lld\n",ans[i]);
		else printf("NIE\n");
	}
}

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
