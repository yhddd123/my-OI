#include <bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#include "sequence.h"
using namespace std;

bool Query (vector <char> T);

vector<char> Solve(int L,int R,double K){
	vector<char> ans,que;
	pair<int,char> num[3];
	for(char op='a';op<='c';op++){
		int l=1,r=R,res=0;
		while(l<=r){
			int mid=l+r>>1;
			que.clear();for(int i=1;i<=mid;i++)que.pb(op);
			if(Query(que))l=mid+1,res=mid;
			else r=mid-1;
		}
		num[op-'a']={res,op};
	}
	// cout<<num[0].fi<<" "<<num[1].fi<<" "<<num[2].fi<<"\n";
	sort(num,num+3);
	for(int i=1;i<=num[0].fi;i++)ans.pb(num[0].se);
	for(int op=1;op<=2;op++){
		auto it=ans.begin();
		for(int i=1;i<=num[op].fi;i++){
			it=ans.insert(it,num[op].se);
			// cout<<i<<" "<<(*it)<<"\n";
			if(Query(ans))it++;
			else it=ans.erase(it),it++,i--;
		}
	}
	// for(char op:ans)cout<<op;cout<<"\n";
	return ans;
}

// namespace ABCDEFG {
	// const int MAXN=4010;
	// int n,L,R,cnt,fir[3],nx[MAXN][3];
	// double k;
	// vector <char> s,res;
	// char tmp[MAXN];
	// void WrongAnswer (int id) {
		// printf("Wrong Answer %d\n",id);
		// exit(0);
	// }
	// void Accepted () {
		// printf("Accepted %d\n",cnt);
		// exit(0);
	// }
	// bool Query (vector <char> T) {
		// int m=T.size();
		// if (m>R) {WrongAnswer(0);}    // T is too long
		// if (++cnt>(int)(k*(double)n)) {WrongAnswer(1);}    // Query too many times
		// for (int i=0;i<m;i++) {
			// if (T[i]<'a'||T[i]>'c') {WrongAnswer(2);}    // T is invalid
		// }
		// if (!m) {return 1;}
		// int pos=fir[T[0]-'a'];
		// for (int i=1;i<m;i++) {pos=nx[pos][T[i]-'a'];}
		// return (pos<n);
	// }
	// int main () {
		// scanf("%d%d%d",&n,&L,&R);
		// scanf("%lf",&k);
		// scanf("%s",tmp+1);
		// s.resize(n);
		// for (int i=0;i<n;i++) {s[i]=tmp[i+1];}
		// nx[n-1][0]=nx[n-1][1]=nx[n-1][2]=nx[n][0]=nx[n][1]=nx[n][2]=n;
		// fir[0]=fir[1]=fir[2]=n;
		// fir[s[n-1]-'a']=n-1;
		// for (int i=n-2;i>=0;i--) {
			// for (int j=0;j<=2;j++) {nx[i][j]=nx[i+1][j];}
			// nx[i][s[i+1]-'a']=i+1;
			// fir[s[i]-'a']=i;
		// }
		// cnt=0;
		// res=Solve(L,R,k);
		// if (res.size()!=s.size()) {WrongAnswer(3);}    // Your answer is not right
		// for (int i=0;i<n;i++) {
			// if (res[i]!=s[i]) {WrongAnswer(4);}    // Your answer is not right
		// }
		// Accepted();
		// return 0;
	// }
// }
// 
// bool Query (vector <char> T) {return ABCDEFG::Query(T);}
// int main () {return ABCDEFG::main();}
