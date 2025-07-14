#include<bits/stdc++.h>
using namespace std;
const long long inf = 1e18;
const int mininf = 1e9 + 7;
#define int long long
#define pb emplace_back
const int MAX = 3e3 + 10;

int b[MAX];
int n;

mt19937 Rnd(1),Rnd2(time(0));

int Tim;

int judge(vector <int> ans){
	for(int i:ans)printf("%lld ",i);printf("\n");fflush(stdout);
	// ++Tim;
	// if(ans[0] == 1){
		// for(int i = 1; i <= n; i++){
			// if(ans[i] != b[i])	return 0;
		// }
		// return 1;
	// }else{
		// int cnt = 0;
		// for(int i = 1; i <= n; i++){
			// if(ans[i] == b[i])	cnt++;	
		// }
		// return cnt;
	// }
	int x;cin>>x;
	return x;
}
#define pb push_back
#define pii pair<int,int>
#define fi first
#define se second
const int maxn=1010;
int ans[maxn];
#define mid (l+r>>1)
#define ls nd<<1
#define rs nd<<1|1
vector<int> tree[maxn<<2];
vector<int> id[maxn];
int pl[maxn<<2],pr[maxn<<2];
void build(int nd,int l,int r,int dep){
	pl[nd]=l,pr[nd]=r;id[dep].pb(nd);
	if(l==r)return ;
	build(ls,l,mid,dep+1),build(rs,mid+1,r,dep+1);
}
bool vis[maxn];
void dfs(int dep){
	if(!id[dep].size())return ;
	for(int nd:id[dep]){
		int l=pl[nd],r=pr[nd];
		// cout<<dep<<" "<<l<<" "<<r<<" "<<nd<<endl;
		// for(int i:tree[nd])cout<<i<<" ";cout<<"\n";
		if(l==r){
			ans[l]=tree[nd].front();
		}
	}
	while(1){
		bool fl=0;
		for(int nd:id[dep]){
			int l=pl[nd],r=pr[nd];
			// cout<<l<<" "<<r<<" "<<tree[nd].size()<<" "<<tree[ls].size()<<" "<<tree[rs].size()<<" a\n";
			if(l==r)continue;
			if(tree[ls].size()==mid-l+1){
				while(tree[nd].size()){
					tree[rs].pb(tree[nd].back());
					tree[nd].pop_back();
				}
				continue;
			}
			if(tree[rs].size()==r-mid){
				while(tree[nd].size()){
					tree[ls].pb(tree[nd].back());
					tree[nd].pop_back();
				}
				continue;
			}
			fl=1;
		}
		if(!fl)break;
		vector<int> que(n+1);que[0]=0;
		fl=0;pii p={0,0};
		int pos=0;
		for(int nd:id[dep]){
			int l=pl[nd],r=pr[nd];
			if(l==r){
				int x=tree[nd].back()==1?2:1;
				que[l]=x;
				continue;
			}
			if(!tree[nd].size()){
				for(int i=l;i<=mid;i++)que[i]=tree[rs].back();
				for(int i=mid+1;i<=r;i++)que[i]=tree[ls].back();
				continue;
			}
			if(fl){
				for(int i=l;i<=mid;i++)que[i]=p.fi;
				for(int i=mid+1;i<=r;i++)que[i]=p.fi;
				continue;
			}
			shuffle(tree[nd].begin(),tree[nd].end(),Rnd);
			int u=tree[nd].back();tree[nd].pop_back();
			int v=tree[nd].back();tree[nd].pop_back();
			for(int i=l;i<=mid;i++)que[i]=u;
			for(int i=mid+1;i<=r;i++)que[i]=v;
			p={u,v};fl=1;pos=nd;
		}
		int val=judge(que);
		// cout<<p.fi<<" "<<p.se<<" "<<pos<<" "<<val<<"\n";
		// for(int i:tree[1])cout<<i<<" ";cout<<"\n";
		if(!val){
			int nd=pos;
			tree[ls].pb(p.se),tree[rs].pb(p.fi);
			continue;
		}
		if(val==2){
			int nd=pos;
			tree[ls].pb(p.fi),tree[rs].pb(p.se);
			continue;
		}
		if(dep==1&&tree[1].size()==n-2){
			tree[pos].pb(p.fi),tree[pos].pb(p.se);
			continue;
		}
		else{
			int nd=pos,x=1,l=pl[nd],r=pr[nd];
			if(tree[ls].size()){
				for(int i=mid+1;i<=r;i++)que[i]=tree[ls].back();
				int val=judge(que);
				if(val==1){
					tree[ls].pb(p.fi),tree[ls].pb(p.se);
				}
				else{
					tree[rs].pb(p.fi),tree[rs].pb(p.se);
				}
				continue;
			}
			if(tree[rs].size()){
				for(int i=l;i<=mid;i++)que[i]=tree[rs].back();
				int val=judge(que);
				if(val==1){
					tree[rs].pb(p.fi),tree[rs].pb(p.se);
				}
				else{
					tree[ls].pb(p.fi),tree[ls].pb(p.se);
				}
				continue;
			}
			for(int i:tree[nd])vis[i]=1;
			for(int i:tree[ls])vis[i]=1;
			for(int i:tree[rs])vis[i]=1;
			vis[p.fi]=vis[p.se]=1;
			while(vis[x])x++;
			for(int i:tree[nd])vis[i]=0;
			for(int i:tree[ls])vis[i]=0;
			for(int i:tree[rs])vis[i]=0;
			vis[p.fi]=vis[p.se]=0;
			for(int i=mid+1;i<=r;i++)que[i]=x;
			int val=judge(que);
			if(val==1){
				tree[ls].pb(p.fi),tree[ls].pb(p.se);
			}
			else{
				tree[rs].pb(p.fi),tree[rs].pb(p.se);
			}
		}
	}
	// cout<<dep<<"\n";
	dfs(dep+1);
}

void solve(){
	cin >> n;
	if(n == 1){
		cout << "1 1";
		return ;
	}
	for(int i = 1; i <= n; i++){
		b[i] = i;
	}
	
	shuffle(b + 1, b + n + 1, Rnd2);
	// for(int i = 1; i <= n; i++){
		// cin >> b[i];
	// }
	// for(int i = 1; i <= n; i++)	cout << b[i] << ' ';cout << '\n';fflush(stdout);
	for(int i=1;i<=n;i++)tree[1].pb(i);
	build(1,1,n,1);
	dfs(1);
	vector<int> a(n+1);
	a[0]=1;for(int i=1;i<=n;i++)a[i]=ans[i];
	printf("1 ");for(int i=1;i<=n;i++)printf("%lld ",ans[i]);fflush(stdout);
	// if(judge(a))cout<<"ac\n";
	// else cout<<"wa\n";
	// cout<<Tim<<"\n";
}

signed main(){
	int t = 1;
	while(t--)	solve();
	return 0;
}