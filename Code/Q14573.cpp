#include<bits/stdc++.h>
// #include"haru.h"
using namespace std;
std::vector<long long> query(const std::vector<std::vector<int>> &U,
	const std::vector<std::vector<int>> &V);
 bool guess(const std::vector<int> &U,const std::vector<int> &V,long long x);

#define pb push_back
vector<vector<int>> U,V;
vector<int> e1,e2;
int n;
void add(int u){
	e1.clear(),e2.clear();
	for(int i=0;i<n;i++)if(i!=u)e1.pb(i),e2.pb(u);
	U.pb(e1),V.pb(e2);
}
vector<int> a;
bool vis[510];
void add(vector<int> id){
	for(int i=0;i<n;i++)vis[i]=0;
	for(int i:id)vis[i]=1;
	e1.clear(),e2.clear();
	int lst=-1,t=0,p=-1;
	for(int i=0;i<n;i++)if(!vis[i]){
		if(lst!=-1)e1.pb(lst),e2.pb(i);
		lst=i;
		t+=(!a[i]);
		if(p==-1&&t>id.size()+1)p=i;
	}
	e1.pb(p),e2.pb(id[0]);
	for(int i=1;i<id.size();i++)e1.pb(id[i-1]),e2.pb(id[i]);
}
int id[510];
vector<int> haru(int N){
mt19937 rnd(10);
	n=N;
	U.clear(),V.clear();
	for(int i=0;i<n;i++)add(i);
	e1.clear(),e2.clear();
	for(int i=0;i<n-1;i++)e1.pb(i),e2.pb(i+1);
	U.pb(e1),V.pb(e2);
	int k=U.size();
	vector<long long> ans=query(U,V);
	long long sum=ans[k-1];ans.pop_back();
	for(int i=0;i<n;i++)id[i]=i;
	sort(id,id+n,[&](int u,int v){return ans[u]<ans[v];});
	long long s=0;for(int i=0;i<n-2;i++)s+=ans[id[i]];
	long long v=(s-sum)/(n-3);
	// assert((s-sum)%(n-3)==0);
	// cout<<v<<"\n";
	// for(int i=0;i<n;i++)cout<<ans[i]<<" ";cout<<"\n";
	// for(int i=0;i<n;i++)cout<<id[i]<<" ";cout<<"\n";
	a.clear();a.resize(n,0);
	int p=n-3;while(p&&ans[id[p-1]]==ans[id[n-1]])p--;
	for(int i=0;i<p;i++)a[id[i]]=ans[id[i]]-v;
	for(int i=p;i<n;i++)a[id[i]]=0;
	long long v3=ans[id[n-1]]-v;
	if(v==2*v3){
		for(int i=p;i<n;i++)a[id[i]]=v3;
		return a;
	}
	// cout<<v<<" "<<v3<<"\n";
	// for(int i=0;i<n;i++)cout<<a[i]<<" ";cout<<"\n";
	vector<int> pos;
	for(int i=0;i<n;i++)if(!a[i])pos.pb(i);
	shuffle(pos.begin(),pos.end(),rnd);
	int all=pos.size();
	if(all<=5){
		bool fl=0;
		for(int i=0;i<all;i++){
			for(int j=i+1;j<all;j++){
				e1.clear(),e2.clear();
				int p1=-1,p2=-1,p3=-1;
				for(int i=0;i<n;i++)if(a[i]){
					if(p1==-1)p1=i;
					else if(p2==-1)p2=i;
					if(p3!=-1)e1.pb(p3),e2.pb(i);
					p3=i;
				}
				e1.pb(pos[i]),e2.pb(p1),e1.pb(pos[j]),e2.pb(p3);
				for(int k=0;k<all;k++)if(i!=k&&j!=k)e1.pb(pos[k]),e2.pb(p2);
				if(guess(e1,e2,sum-v3*(all-2))){
					fl=1;
					a[pos[i]]=a[pos[j]]=-1;
					for(int k=0;k<all;k++)if(i!=k&&j!=k)a[pos[k]]=v3;
					break;
				}
			}
			if(fl)break;
		}
	}
	else{
		int tmp[2];tmp[0]=tmp[1]=-1;
		for(int t=0;t<2;t++){
			pos.clear();
			for(int i=0;i<n;i++)if(!a[i]&&i!=tmp[0])pos.pb(i);
			shuffle(pos.begin(),pos.end(),rnd);
			while(pos.size()>1){
				int p=min(all/3-1,(int)pos.size()/2);
				vector<int> tmp;
				for(int i=0;i<p;i++)tmp.pb(pos[i]);
				add(tmp);
				// cout<<p<<" "<<pos.size()<<" s\n";
				// for(int u:tmp)cout<<u<<" ";cout<<"\n";
				// for(int i=0;i<n-1;i++)cout<<e1[i]<<" "<<e2[i]<<"\n";
				if(guess(e1,e2,sum-v3*p)){
					// cout<<"a\n";
				pos.erase(pos.begin(),pos.begin()+p);
				}
				else pos=tmp;
				// cout<<pos.size()<<"\n";
			}
			tmp[t]=pos[0];
			// cout<<t<<" "<<pos[0]<<"\n";
		}
		a[tmp[0]]=a[tmp[1]]=-1;
	}
	for(int i=0;i<n;i++)if(!a[i])a[i]=v3;
	return a;
}

// #define ll long long
// namespace Interactive_Lib{
// bool used_query;int cnt_query,cnt_guess,cnt_fail,max_query,max_guess;
// vector<int> a,b,E[505];int n,T;ll dp[505],ans;bool vis[505];
// void Wrong_Answer(int o){
	// cout<<"Wrong Answer ["<<o<<"]"<<endl;
	// exit(1);
// }
// void dfs(int u,int fa){
	// vis[u]=true;dp[u]=a[u];
	// for(int v:E[u]) if(v!=fa&&!vis[v]){
		// dfs(v,u);ans=max(ans,dp[v]+dp[u]);dp[u]=max(dp[u],dp[v]+a[u]);
	// }
// }
// vector<ll> query(const vector<vector<int>> &U,const vector<vector<int>> &V){
	// if(used_query) Wrong_Answer(1);
	// used_query=true;
	// if(U.size()!=V.size()||U.size()>2000) Wrong_Answer(2);
	// cnt_query=U.size();
	// vector<ll> R(cnt_query);
	// for(int t=0;t<cnt_query;t++){
		// if(U[t].size()!=n-1||V[t].size()!=n-1) Wrong_Answer(3);
		// for(int i=0;i<n;i++) E[i].clear(),vis[i]=false;
		// for(int i=0;i<n-1;i++){
			// if(U[t][i]<0||n<=U[t][i]||V[t][i]<0||n<=V[t][i]) Wrong_Answer(4);
			// E[U[t][i]].push_back(V[t][i]);
			// E[V[t][i]].push_back(U[t][i]);
		// }
		// ans=0;dfs(0,-1);
		// for(int i=0;i<n;i++) if(!vis[i]) Wrong_Answer(5);
		// R[t]=ans;
	// }
	// return R;
// }
// bool guess(const vector<int> &U,const vector<int> &V,ll x){
	// if(++cnt_guess>2000) Wrong_Answer(6);
	// if(U.size()!=n-1||V.size()!=n-1) Wrong_Answer(7);
	// for(int i=0;i<n;i++) E[i].clear(),vis[i]=false;
	// for(int i=0;i<n-1;i++){
		// if(U[i]<0||n<=U[i]||V[i]<0||n<=V[i]) Wrong_Answer(8);
		// E[U[i]].push_back(V[i]);
		// E[V[i]].push_back(U[i]);
	// }
	// ans=0;dfs(0,-1);
	// for(int i=0;i<n;i++) if(!vis[i]) Wrong_Answer(9);
	// return ans==x;
// }
// void main(){
	// cin>>T;max_query=0,max_guess=0;
	// while(T--){
		// used_query=cnt_query=cnt_guess=cnt_fail=0;
		// cin>>n;
		// a.resize(n);
		// for(int i=0;i<n;i++) cin>>a[i];
		// b=haru(n);
		// for(int i=0;i<n;i++)cout<<b[i]<<" ";cout<<"\n";
		// if(b.size()!=n) Wrong_Answer(10);
		// for(int i=0;i<n;i++){
			// if(b[i]==-1) cnt_fail++;
			// else if(a[i]!=b[i]) Wrong_Answer(11);
		// }
		// if(cnt_fail>2) Wrong_Answer(12);
		// max_query=max(max_query,cnt_query);
		// max_guess=max(max_guess,cnt_guess);
	// }
	// cout<<"AC with "<<max_query<<" query(s) and "<<max_guess<<" guess(es)."<<endl;
	// return;
// }
// }
// vector<ll> query(const vector<vector<int>> &U,const vector<vector<int>> &V){
	// return Interactive_Lib::query(U,V);
// }
// bool guess(const vector<int> &U,const vector<int> &V,ll x){
	// return Interactive_Lib::guess(U,V,x);
// }
// int main(){
	// Interactive_Lib::main();
	// return 0;
// }