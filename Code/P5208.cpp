#include <bits/stdc++.h>
using namespace std;
// #include "shop.h"
int query(int *S, int nS, int *T, int nT);

const int maxn=100010;

int tmp[2][2];
int ask(int a,int b){
    tmp[0][0]=a,tmp[1][0]=b;
    return query(tmp[0],1,tmp[1],1);
}
int ask(int a,int b,int c){
    tmp[0][0]=a,tmp[1][0]=b,tmp[1][1]=c;
    return query(tmp[0],1,tmp[1],2);
}
int n,id[maxn];
int st[maxn],tp;
void find_price(int task_id, int N, int K, int ans[]) {
    n=N;for(int i=0;i<n;i++)id[i]=i;
    int x=0;
    if(task_id!=3){
        st[tp=1]=0;
        for(int i=1;i+1<n;i++){
            if(!ask(id[i],id[i+1]))swap(id[i],id[i+1]);
            if(!ask(st[tp],id[i],id[i+1]))ans[id[i]]=0;
            else st[++tp]=id[i+1],id[i+1]=id[i];
        }
        x=id[n-1];
        if(ask(st[tp],x))st[++tp]=x,x=0;
    }
    else{
        tp=0;for(int i=0;i<n;i++)st[++tp]=i;
        if(!ask(0,n-1))reverse(st+1,st+tp+1);
    }
    // for(int i=1;i<=tp;i++)cout<<st[i]<<" ";cout<<"\n";
    ans[st[tp]]=1;
    if(tp>1){
        int l=1,r=tp-1;
        while(l<r){
            int mid=l+r>>1;
            if(!ask(st[tp],st[mid],st[mid+1]))l=mid+1;
            else r=mid;
        }
        // cout<<x<<" "<<st[l]<<" "<<x<<"\n";
        for(int i=1;i<l;i++)ans[st[i]]=0;
        for(int i=l+1;i<tp;i++)ans[st[i]]=1;
        if(x){
            int y=st[l];
            if(!ask(x,y))swap(x,y);
            if(!ask(st[tp],x,y))ans[x]=0,ans[y]=(K==((tp-l+1)&1));
            else ans[y]=1,ans[x]=(K==((tp-l)&1));
        }
        else ans[st[l]]=(K==((tp-l+1)&1));
    }
    else if(x)ans[x]=(K==0);
    // for(int i=0;i<n;i++)cout<<ans[i];cout<<"\n";
}


// namespace Interactive_Library {

// 	#define assertf(k, A...) ({ (k) ? void() : quitf(0, A); })
// 	#define assert(k) assertf(k, "Assertion \"%s\" failed.", #k)
// 	#define quitf(x, A...) ({ printf("%.4lf ", (double) (x)); printf(A); puts(""); exit(0); })

// 	const int MAX_N = 100000;
// 	const int MAX_M = 1000000;

// 	int N, M, type, A[MAX_N], Cnt;
// 	int vis[MAX_N], timer;

// 	inline int Rand(int l, int r) { return rand() % (r - l + 1) + l; }

// 	int query(int *S, int nS, int *T, int nT) {
// 		Cnt += nS + nT;
// 		assertf(Cnt <= M, "Query limit exceeded.");

// 		int cnt1 = 0, cnt2 = 0;
// 		bool flag = 0;

// 		timer++;

// 		for (int i = 0; i < nS; ++i) {
// 			int x = S[i];
// 			if (x < 0 or x > N - 1 or vis[x] == timer) {
// 				flag = 1;
// 				goto END;
// 			}
// 			vis[x] = timer;
// 			cnt1 += A[x];
// 		}

// 		timer++;

// 		for (int i = 0; i < nT; ++i) {
// 			int x = T[i];
// 			if (x < 0 or x > N - 1 or vis[x] == timer) {
// 				flag = 1;
// 				goto END;
// 			}
// 			vis[x] = timer;
// 			cnt2 += A[x];
// 		}

// 		END: 
// 		assertf(flag == 0, "Invalid call to query");

// 		if (cnt1 != cnt2) return cnt1 < cnt2;
// 		return Rand(0, 1);
// 	}
//     mt19937 rnd(1);
// 	void __main__ () {
        
//         int T=10;

// 		for (int i = 0; i < T; ++i) {

// 			Cnt = 0;

//             N=10,M=100;

// 			// N = 100000;
// 			// M = 500100;


// 			int C = 0;
// 			for (int i = 0; i < N; ++i) {
// 				A[i] = rnd()&1;
// 				assert(0 <= A[i] and A[i] <= 1);
// 				C ^= A[i];
// 			}
//             for(int i=0;i<N;i++)cout<<A[i];cout<<"\n";

// 			static int ans[MAX_N];

// 			for (int i = 0; i < N; ++i) ans[i] = 0;
// 			find_price(type, N, C, ans);

// 			for (int i = 0; i < N; ++i) {
// 				assertf(A[i] == ans[i], "Your answer is incorrect.");
// 			}

// 			printf("Testcase #%d correct, total cost of queries: %d.\n", i + 1, Cnt);

// 		}

// 		quitf(1.0, "Correct Answer");
// 	}

// }

// int query(int *S, int nS, int *T, int nT) {
// 	return Interactive_Library::query(S, nS, T, nT);
// }

// int main() {
// 	// freopen("A.in","r",stdin);
// 	//freopen("shop.out","w",stdout);
// 	int T = 1;
// 	srand(T);
// 	Interactive_Library::__main__();
// }