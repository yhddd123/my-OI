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
const int maxn=35;
const int inf=1e9;
bool mbe;

int n,ans,num;
char s[maxn];
int e[maxn],cnt[maxn],siz[maxn];
int ff[maxn];
int fd(int x){
	if(ff[x]==x)return x;
	return ff[x]=fd(ff[x]);
}
#define tup tuple<int,int,int>
map<tup,int> a;
map<map<tup,int>,int> f;
int dfs(map<tup,int> a){
	map<tup,int> tmp;
	for(auto[t,v]:a)if(v)tmp[t]=v;
	swap(a,tmp);
	// for(auto[t,v]:a)if(!v)a.erase(t);
	if(!a.size())return 0;
	if(f.find(a)!=f.end())return f[a];
	int res=inf;
	auto it=a.begin();
    auto ddfs=[&](auto &&self,int s1,int s2,int s3)->void{
    	// cout<<s1<<" "<<s2<<" "<<s3<<endl;
        if(it==a.end()){
        	if(s1==s2&&s1)res=min(res,dfs(a)+(s1*s1-s3));
        	return ;
        }
        for(int t=0;t<=(*it).se;t++){
        	auto[v1,v2,v3]=(*it).fi;
        	(*it).se-=t;
        	it++;
        	self(self,s1+v1*t,s2+v2*t,s3+v3*t);
        	it--;
        	(*it).se+=t;
        }
	};
	ddfs(ddfs,0,0,0);
	return f[a]=res;
}
void work(){
	n=read();ans=num=0;
	for(int i=1;i<=n;i++)ff[i]=i;
	for(int i=1;i<=n;i++){
		scanf("%s",s);e[i]=cnt[i]=siz[i]=0;
		for(int j=0;j<n;j++)if(s[j]=='1')e[i]|=1<<j,cnt[i]++;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)if(e[i]&e[j])ff[fd(i)]=fd(j);
	}
	for(int i=1;i<=n;i++)if(i!=ff[i])cnt[fd(i)]+=cnt[i],siz[fd(i)]++,e[fd(i)]|=e[i];
	int num=n;
	a.clear();
	for(int i=1;i<=n;i++)if(ff[i]==i){
		siz[fd(i)]++;int sz=__builtin_popcount(e[i]);
		if(siz[i]==sz)ans+=siz[i]*siz[i]-cnt[i];
		else a[{siz[i],sz,cnt[i]}]++;
		num-=sz;
	}
	a[{0,1,0}]+=num;
	// for(auto[t,v]:a){
		// auto[v1,v2,v3]=t;
		// cout<<v1<<" "<<v2<<" "<<v3<<" "<<v<<"\n";
	// }
	printf("%d\n",ans+dfs(a));
}

bool med;
int T;
signed main(){
	// freopen("factory.in","r",stdin);
	// freopen("factory.out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	for(int t=1;t<=T;t++){
		printf("Case #%lld: ",t);
		work();
	}
}