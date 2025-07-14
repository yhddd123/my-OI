#include<bits/stdc++.h>
#define mod 1000000007
using namespace std;
const int maxn=200010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n;
string c[maxn],s;
int tree[maxn][30],cnt;
int fail[maxn],ed[maxn];
void insert(string c,int num){
	int len=c.size(),nd=0;
	for(int i=0;i<len;i++){
		if(!tree[nd][c[i]-'a'+1])tree[nd][c[i]-'a'+1]=++cnt;
		nd=tree[nd][c[i]-'a'+1];
	}
	ed[nd]=num;
}
queue<int> q;
void build(){
	for(int i=1;i<=26;i++){
		if(tree[0][i])q.push(tree[0][i]);
	}
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=1;i<=26;i++){
			if(tree[u][i]){
				fail[tree[u][i]]=tree[fail[u]][i];
				q.push(tree[u][i]);
			}
			else tree[u][i]=tree[fail[u]][i];
		}
	}
}
struct nd{
	int num,id;
}ans[maxn];
bool cmp(nd u,nd v){
	if(u.num==v.num)return u.id<v.id;
	return u.num>v.num;
}
void query(string c){
	int len=c.size(),nd=0;
	for(int i=0;i<len;i++){
		nd=tree[nd][c[i]-'a'+1];
		for(int j=nd;j;j=fail[j]){
			ans[ed[j]].num++;
		}
	}
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	while(~scanf("%d",&n)){
		if(!n)return 0;
		for(int i=0;i<=cnt;i++){
			ed[i]=0;fail[i]=0;
			for(int j=1;j<=26;j++)tree[i][j]=0;
		}
		cnt=0;
		for(int i=1;i<=n;i++){
			cin>>c[i];
			ans[i].num=0;
			ans[i].id=i;
			insert(c[i],i);
		}
		build();
		cin>>s;query(s);
		sort(ans+1,ans+n+1,cmp);
		printf("%d\n",ans[1].num);
		cout<<c[ans[1].id]<<"\n";
		for(int i=2;i<=n;i++){
			if(ans[i].num==ans[i-1].num)cout<<c[ans[i].id]<<"\n";
			else break;
		}
	}
}
