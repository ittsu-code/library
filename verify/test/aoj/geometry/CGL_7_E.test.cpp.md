---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../../../assets/css/copy-button.css" />


# :heavy_check_mark: test/aoj/geometry/CGL_7_E.test.cpp
<a href="../../../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/aoj/geometry/CGL_7_E.test.cpp">View this file on GitHub</a>
    - Last commit date: 2019-11-13 14:47:25 +0900


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_E">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_E</a>


## Depends On
* :warning: <a href="../../../../library/geometry/geometry.cpp.html">geometry/geometry.cpp</a>


## Code
{% raw %}
```cpp
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_E"
#include<bits/stdc++.h>
using namespace std;

#define call_from_test
#include "../../../geometry/geometry.cpp"
#undef call_from_test

#define ERROR "0.000001"

//intersectCC
signed main(){
  Circle c1,c2;
  cin>>c1>>c2;
  auto pp=getCrossPointCC(c1,c2);
  if(pp.size()==1u) pp.emplace_back(pp[0]);
  if(pp[1]<pp[0]) swap(pp[0],pp[1]);
  cout<<pp[0]<<" "<<pp[1]<<endl;
  return 0;
}

```
{% endraw %}

<a href="../../../../index.html">Back to top page</a>
