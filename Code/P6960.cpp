#include<bits/stdc++.h>
using namespace std;
const int maxn=5010;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
int n,a[maxn],b[maxn];
int p[maxn],len;
vector<int> e[maxn],nw;
char opt;
bool ask(int u,int v){
	cout<<"? "<<u<<" "<<v<<"\n";
	fflush(stdout);
	cin>>opt;
	return (opt=='>');
}
void solve(){
	cin>>n;
	for(int i=1;i<=n/2;i++)p[i]=i;
	random_shuffle(p+1,p+n/2+1);
	for(int i=1;i<=(n+1)/2;i++)e[1].push_back(i);
	len=1;
	for(int i=1;i<=n/2;i++){
		int l=1,r=len,ans=0;
		while(l<=r){
			int mid=l+r>>1;
			if(ask(p[i],e[mid].front())==true){
				l=mid+1;
				ans=mid;
			}
			else r=mid-1;
		}
		int cnt=0;
		if(!ans){
			for(int &j:e[1]){
				bool res=ask(p[i],j);
				cnt+=res;
				if(res)nw.push_back(j),j=0;
			}
			for(int j=len;j>1;j--)e[j+1]=e[j];
			e[2].clear();
			for(int j:e[1])if(j)e[2].push_back(j);
			e[1]=nw;nw.clear();len++;
			a[p[i]]=cnt*2;
		}
		else{
			for(int &j:e[ans]){
				bool res=ask(p[i],j);
				cnt+=res;
				if(res)nw.push_back(j),j=0;
			}
			if(cnt<e[ans].size()){
				for(int j=len;j>ans;j--)e[j+1]=e[j];
				e[ans+1].clear();
				for(int j:e[ans])if(j)e[ans+1].push_back(j);
				e[ans]=nw;nw.clear();len++;
				for(int j=1;j<ans;j++)cnt+=e[j].size();
				a[p[i]]=cnt*2;
			}
			else{
				cnt=0;e[ans]=nw;nw.clear();
				if(ans==len&&!(n&1))a[p[i]]=n;
				else{
					for(int &j:e[ans+1]){
						bool res=ask(p[i],j);
						cnt+=res;
						if(res)nw.push_back(j),j=0;
					}
					for(int j=len;j>ans+1;j--)e[j+1]=e[j];
					e[ans+2].clear();
					for(int j:e[ans+1])if(j)e[ans+2].push_back(j);
					e[ans+1]=nw;nw.clear();len++;
					for(int j=1;j<=ans;j++)cnt+=e[j].size();
					a[p[i]]=cnt*2;
				}
			}
		}
	}
	for(int i=1;i<=len;i++)b[e[i].front()]=i*2-1;
	cout<<"! ";
	for(int i=1;i<=n/2;i++)cout<<a[i]<<" ";
	for(int i=1;i<=(n+1)/2;i++)cout<<b[i]<<" ";
	cout<<"\n";
	fflush(stdout);
}
signed main(){
	solve();
}
