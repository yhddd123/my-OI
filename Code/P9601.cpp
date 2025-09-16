#include<bits/stdc++.h>
#define pb push_back
using namespace std;
// #include "longesttrip.h"
std::vector<int> longest_trip(int N, int D);
bool are_connected(std::vector<int> A, std::vector<int> B);

vector<int> longest_trip(int n,int D){
    vector<int> id1={0},id2={1};
    for(int i=2;i+1<n;i+=2){
        bool fl1=are_connected({i},{i+1});
        bool fl2=are_connected({i},{id1.back()});
        bool fl3=are_connected({i},{id2.back()});
        if(!fl1){
            if(!fl2&&!fl3){
                id1.pb(i+1);
                reverse(id2.begin(),id2.end());
                for(int u:id2)id1.pb(u);
                id2={i};
            }
            else if(fl2&&!fl3)id1.pb(i),id2.pb(i+1);
            else if(fl3&&!fl2)id1.pb(i+1),id2.pb(i);
            else{
                id1.pb(i);
                reverse(id2.begin(),id2.end());
                for(int u:id2)id1.pb(u);
                id2={i+1};
            }
        }
        else{
            if(!fl2&&!fl3){
                reverse(id2.begin(),id2.end());
                for(int u:id2)id1.pb(u);
                id2={i,i+1};
            }
            else if(fl2)id1.pb(i),id1.pb(i+1);
            else id2.pb(i),id2.pb(i+1);
        }
    }
    if(n&1){
        if(are_connected({n-1},{id1.back()}))id1.pb(n-1);
        else if(are_connected({n-1},{id2.back()}))id2.pb(n-1);
        else{
            reverse(id2.begin(),id2.end());
            for(int u:id2)id1.pb(u);
            id2={n-1};
        }
    }
    // cout<<id1.size()<<" "<<id2.size()<<" a\n";
    // for(int u:id1)cout<<u<<" ";cout<<"\n";
    // for(int u:id2)cout<<u<<" ";cout<<"\n";
    if(!are_connected(id1,id2))return (id1.size()>id2.size())?id1:id2;
    if(are_connected({id1[0]},{id2[0]})){
        reverse(id1.begin(),id1.end());
        for(int u:id2)id1.pb(u);
        return id1;
    }
    if(are_connected({id1[0]},{id2.back()})){
        for(int u:id1)id2.pb(u);
        return id2;
    }
    if(are_connected({id1.back()},{id2[0]})){
        for(int u:id2)id1.pb(u);
        return id1;
    }
    int l=0,r=(int)id1.size()-2,res=-1;
    while(l<=r){
        int mid=l+r>>1;
        vector<int> tmp=id1;tmp.resize(mid+1);
        if(!are_connected(tmp,id2))res=mid,l=mid+1;
        else r=mid-1;
    }
    int p=res+1;
    l=0,r=(int)id2.size()-2,res=-1;
    while(l<=r){
        int mid=l+r>>1;
        vector<int> tmp=id2;tmp.resize(mid+1);
        if(!are_connected(tmp,{id1[p]}))res=mid,l=mid+1;
        else r=mid-1;
    }
    int q=res+1;
    vector<int> ans;
    for(int i=p+1;i<id1.size();i++)ans.pb(id1[i]);
    for(int i=0;i<=p;i++)ans.pb(id1[i]);
    for(int i=q;i<id2.size();i++)ans.pb(id2[i]);
    for(int i=0;i<q;i++)ans.pb(id2[i]);
    return ans;
}

// static inline constexpr int maxNumberOfCalls = 32640;
// static inline constexpr int maxTotalNumberOfCalls = 150000;
// static inline constexpr int maxTotalNumberOfLandmarksInCalls = 1500000;
// static int call_counter = 0;
// static int total_call_counter = 0;
// static int landmark_counter = 0;

// static int C, N, D;
// static std::vector<std::vector<int>> U;
// static std::vector<bool> present;

// static inline void protocol_violation(std::string message)
// {
//     printf("Protocol Violation: %s\n", message.c_str());
//     exit(0);
// }

// bool are_connected(std::vector<int> A, std::vector<int> B)
// {
//     ++call_counter;
//     ++total_call_counter;
//     if (call_counter > maxNumberOfCalls || total_call_counter > maxTotalNumberOfCalls)
//     {
//         protocol_violation("too many calls");
//     }

//     int nA = A.size(), nB = B.size();
//     landmark_counter += nA + nB;
//     if (landmark_counter > maxTotalNumberOfLandmarksInCalls)
//     {
//         protocol_violation("too many elements");
//     }

//     if (nA == 0 || nB == 0)
//     {
//         protocol_violation("invalid array");
//     }
//     for (int i = 0; i < nA; ++i)
//     {
//         if (A[i] < 0 || N <= A[i])
//         {
//             protocol_violation("invalid array");
//         }
//         if (present[A[i]])
//         {
//             protocol_violation("invalid array");
//         }
//         present[A[i]] = true;
//     }
//     for (int i = 0; i < nA; ++i)
//     {
//         present[A[i]] = false;
//     }
//     for (int i = 0; i < nB; ++i)
//     {
//         if (B[i] < 0 || N <= B[i])
//         {
//             protocol_violation("invalid array");
//         }
//         if (present[B[i]])
//         {
//             protocol_violation("invalid array");
//         }
//         present[B[i]] = true;
//     }
//     for (int i = 0; i < nB; ++i)
//     {
//         present[B[i]] = false;
//     }

//     for (int i = 0; i < nA; ++i)
//     {
//         for (int j = 0; j < nB; ++j)
//         {
//             if (A[i] == B[j])
//             {
//                 protocol_violation("non-disjoint arrays");
//             }
//         }
//     }

//     for (int i = 0; i < nA; ++i)
//     {
//         for (int j = 0; j < nB; ++j)
//         {
//             if (U[std::max(A[i], B[j])][std::min(A[i], B[j])] == 1)
//             {
//                 return true;
//             }
//         }
//     }

//     return false;
// }

// int main()
// {
//     freopen("A.in", "r", stdin);
//     assert(1 == scanf("%d", &C));
//     int maximumCalls = 0;
//     for (int c = 0; c < C; ++c)
//     {
//         call_counter = 0;
//         assert(2 == scanf("%d %d", &N, &D));

//         present.assign(N, false);
//         U.resize(N);
//         for (int i = 1; i < N; ++i)
//         {
//             U[i].resize(i);
//             for (int j = 0; j < i; ++j)
//             {
//                 assert(1 == scanf("%d", &U[i][j]));
//             }
//         }

//         for (int i = 2; i < N; ++i)
//         {
//             for (int j = 1; j < i; ++j)
//             {
//                 for (int k = 0; k < j; ++k)
//                 {
//                     if (U[i][j] + U[i][k] + U[j][k] < D)
//                     {
//                         printf("Insufficient Density\n");
//                         exit(0);
//                     }
//                 }
//             }
//         }

//         std::vector<int> t = longest_trip(N, D);
//         int l = t.size();
//         printf("%d\n", l);
//         for (int i = 0; i < l; ++i)
//         {
//             printf(i == 0 ? "%d" : " %d", t[i]);
//         }
//         printf("\n");
//         printf("%d\n", call_counter);

//         maximumCalls = std::max(maximumCalls, call_counter);
//         call_counter = 0;
//     }
//     printf("%d\n", maximumCalls);

//     return 0;
// }
