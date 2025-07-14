#include "message.h"
#include<bits/stdc++.h>
#define pb push_back
using namespace std;

// const int PACKET_SIZE = 31;
// const int CALLS_CNT_LIMIT = 100;
// 
// int calls_cnt;
// std::vector<std::vector<bool>> R;
// std::vector<bool> C(PACKET_SIZE);
// std::vector<bool> taint(const std::vector<bool>& A) {
  // std::vector<bool> B = A;
  // bool bit = 0;
  // for (int i = 0; i < PACKET_SIZE; i++)
    // if (C[i] == 1) {
      // B[i] = bit;
      // bit = !bit;
    // }
  // return B;
// }
// std::vector<bool> send_packet(std::vector<bool> A) {
  // calls_cnt++;
  // if (calls_cnt > CALLS_CNT_LIMIT)
    // printf("Too many calls"),exit(0);
  // if ((int)A.size() != PACKET_SIZE)
    // printf("Invalid argument"),exit(0);
// 
  // std::vector<bool> B = taint(A);
  // R.push_back(B);
  // return B;
// }

void send_message(std::vector<bool> M, std::vector<bool> C) {
	M.pb(0);while(M.size()<16*66)M.pb(1);
	reverse(M.begin(),M.end());
	vector<vector<bool>> a;a.resize(66);
	for(int i=0;i<66;i++)a[i].resize(31);
	for(int i=0;i<31;i++)if(!C[i]){
		int d=0;
		for(int j=i+1;;j++)if(!C[j%31]){
			d=j-i;
			break;
		}
		a[d-1][i]=1;
		for(int j=d;j<66;j++)a[j][i]=M.back(),M.pop_back();
	}
	for(int i=0;i<66;i++)send_packet(a[i]);
}
std::vector<bool> receive_message(std::vector<std::vector<bool>> R) {
	// for(int i=0;i<66;i++){
		// for(int j=0;j<31;j++)cout<<R[i][j]<<" ";cout<<"\n";
	// }
	vector<int> e(31);
	for(int i=0;i<=30;i++){
		int p=0;
		for(int j=0;j<66;j++)if(R[j][i]){p=j+1;break;}
		e[i]=(i+p)%31;
	}
	vector<int> st;
	for(int i=0;i<=30;i++){
		vector<int> vis(31,0);st.clear();
		int u=i;
		while(!vis[u]){
			st.pb(u);vis[u]=1;
			u=e[u];
		}
		if(u==i&&st.size()==16)break;
	}
	vector<bool> res;
	sort(st.begin(),st.end());
	for(int i:st){
		int p=0;
		for(int j=0;j<66;j++)if(R[j][i]){p=j+1;break;}
		for(int j=p;j<66;j++)res.pb(R[j][i]);
	}
	for(int i=res.size()-1;~i;i--){
		if(!res[i]){
			while(res.size()>i)res.pop_back();
			break;
		}
	}
	return res;
}

// void quit(const char* message) {
  // printf("%s\n", message);
  // exit(0);
// }
// 
// void run_scenario() {
  // R.clear();
  // calls_cnt = 0;
// 
  // int S;
  // assert(1 == scanf("%d", &S));
  // std::vector<bool> M(S);
  // for (int i = 0; i < S; i++) {
    // int bit;
    // assert(1 == scanf("%d", &bit));
    // assert((bit == 0) || (bit == 1));
    // M[i] = bit;
  // }
// 
  // for (int i = 0; i < PACKET_SIZE; i++) {
    // int bit;
    // assert(1 == scanf("%d", &bit));
    // assert((bit == 0) || (bit == 1));
    // C[i] = bit;
  // }
// 
  // send_message(M, C);
  // std::vector<bool> D = receive_message(R);
// 
  // int K = (int)R.size();
  // int L = (int)D.size();
  // printf("%d %d\n", K, L);
  // for (int i = 0; i < L; i++)
    // printf("%s%d", (i == 0 ? "" : " "), (D[i] ? 1 : 0));
  // printf("\n");
// }
// 
// int main() {
  // int T;
  // assert(1 == scanf("%d", &T));
  // for (int i = 1; i <= T; i++)
    // run_scenario();
// }
// 