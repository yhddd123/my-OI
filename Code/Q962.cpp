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
const int maxn=20010;
const int inf=1e9;
bool mbe;

int n,a[maxn];
vector<int> ans[maxn];int tp;
vector<tuple<int,int,int,int>> b;
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	b.pb({1,n,1,n});
	while(1){
		bool fl=1;for(int i=1;i<=n;i++)fl&=a[i]==i;
		if(fl)break;
		fl=1;for(int i=1;i<=n;i++)fl&=a[i]==n-i+1;
		if(fl)break;
		bool flag=0;
		++tp;
		// cout<<tp<<endl;
		vector<tuple<int,int,int,int>> nw;
		for(auto[l,r,pl,pr]:b)if(pl<=pr){
			// cout<<l<<" "<<r<<" "<<pl<<" "<<pr<<endl;
			if(l!=r){
				flag=1;
				int mid=l+r>>1;
				int p=pl-1;for(int i=pl;i<=pr&&a[i]<=mid;i++)p=i;
				if(pl<=p)ans[tp].pb({p-pl+1}),reverse(a+pl,a+p+1);
				for(int i=p+1,op=1;i<=pr;i++){
					if(a[i]<=mid&&(i==pr||a[i+1]>mid)){
						ans[tp].pb(i-p),reverse(a+p+1,a+i+1),p=i;
						op^=1;
					}
					else if(a[i]>mid&&(i==pr||a[i+1]<=mid)){
						if(!op)ans[tp].pb(i-p),reverse(a+p+1,a+i+1),p=i;
					}
				}
				if(p!=pr)ans[tp].pb(pr-p),reverse(a+p+1,a+pr+1);
				auto ddfs=[&](auto &&self,int l,int r,int pl,int pr)->void{
					if(pl>pr)return ;
					if(l==r){nw.pb({l,r,pl,pr});return ;}
					int mid=l+r>>1;
					int p=pl-1;for(int i=pl;i<=pr&&a[i]<=mid;i++)p=i;
					bool fl=1;for(int i=p+1;i<=pr;i++)fl&=a[i]>mid;
					if(fl)self(self,l,mid,pl,p),self(self,mid+1,r,p+1,pr);
					else nw.pb({l,r,pl,pr});
				};
				ddfs(ddfs,l,r,pl,pr);
			}
			else{
				for(int i=pl;i<=pr;i++)ans[tp].pb(1);
				nw.pb({l,r,pl,pr});
			}
		}
		if(!flag){ans[tp--].clear();break;}
		b=nw;
	}
	if(tp&1)reverse(a+1,a+n+1);
	bool fl=1;for(int i=1;i<=n;i++)fl&=a[i]==i;
	if(!fl){
		++tp;
		for(int i=1;i<=n;i++)ans[tp].pb(1);
	}
	for(int i=2;i<=tp;i+=2)reverse(ans[i].begin(),ans[i].end());
	printf("%d\n",tp);
	for(int i=1;i<=tp;i++){
		printf("%d ",ans[i].size());
		for(int v:ans[i])printf("%d ",v);puts("");
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