#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
#define pii pair<int,int>
#define mems(x,y) memset(x,y,sizeof x)
using namespace std;
const int maxn=100010;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

bool mbe;
int n,k,q,ans,s;
int a[maxn],b[maxn];
vector<int> p[maxn],num;
int lowbit(int x){return x&(-x);}
struct bit{
	int c[maxn];
	void clear(){memset(c,0,sizeof(c));}
	void updata(int x,int w){
		while(x<=n){
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
}t;
vector<pair<int,pii> > res[maxn];
void work(){
	n=read();k=read();q=read();s=n*5/sqrt(q);
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=k;i++)b[i]=i;
	for(int i=1;i<=n;i++){
		p[a[i]].push_back(i);
		ans+=i-1-t.query(a[i]);
		t.updata(a[i],1);
	}
	for(int i=1;i<=k;i++)if(p[i].size()>s)num.push_back(i);
	for(int i=1;i<=k;i++)if(p[i].size()){//n^2/s*logn
		for(int j:num)if(i!=j){
			int s1=0,s2=0;
			for(int k:p[i]){
				if(k<p[j].front())s1+=0;
				else if(k>=p[j].back())s1+=p[j].size();
				else s1+=(upper_bound(p[j].begin(),p[j].end(),k)-p[j].begin());
				if(k>p[j].back())s2+=0;
				else if(k<=p[j].front())s2+=p[j].size();
				else s2+=p[j].size()-(lower_bound(p[j].begin(),p[j].end(),k)-p[j].begin());
			}
//			cout<<i<<" "<<j<<" "<<s1<<" "<<s2<<"\n";
			res[i].push_back(make_pair(j,make_pair(s1,s2)));
		}
	}
	while(q--){
		int pos=read(),u=b[pos],v=b[pos+1];
		swap(b[pos],b[pos+1]);
		if(p[u].size()&&p[v].size()){
			if(p[u].size()>s){
				for(auto i:res[v])if(i.first==u){
					ans+=i.second.first;
					ans-=i.second.second;
				}
			}
			else if(p[v].size()>s){
				for(auto i:res[u])if(i.first==v){
					ans+=i.second.second;
					ans-=i.second.first;
				}
			}
			else{
				for(int i=0,j=0;i<p[u].size();i++){
					while(j<p[v].size()&&p[v][j]<=p[u][i])j++;
					ans-=j;ans+=p[v].size()-j;
				}
			}
		}
		printf("%lld\n",ans);
	}
}
bool med;
int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
//	cerr<<(&mbe-&med)/1027876.0<<"MB\n";
	T=1;
	while(T--)work();
}
