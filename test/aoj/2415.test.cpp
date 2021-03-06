#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2415"

#include<bits/stdc++.h>
using namespace std;

#define call_from_test
#include "../../tools/fastio.cpp"
#include "../../datastructure/skewheap.cpp"
#include "../../algorithm/optimalbinarytree.cpp"
#undef call_from_test

signed main(){
  using ll = long long;
  int n;
  cin>>n;
  vector<ll> ws(n);
  for(int i=0;i<n;i++) cin>>ws[i];
  cout<<optimalbinarytree(ws)<<endl;
  return 0;
}
