# Brazilian ICPC Summer School &ndash; Days 6 and 7

The 2019 edition of the [Brazilian ICPC Summer School](http://maratona.ic.unicamp.br/MaratonaVerao2019/) took place in Campinas between Jan 21st and Feb 2nd, and I was one of the instructors for the Brazilian Finals class.
Each day of activities comprised a five-hour contest in the morning and three and a half hours of lectures in the afternoon.

This repository is intended to centralize all resources (slides, problems, solutions, etc.) pertaining to Days 6 and 7, in which my classes took place.
For the other days, please refer to [Summer School &ndash; Day-by-day](http://maratona.ic.unicamp.br/MaratonaVerao2019/daybyday.html).

Day 6 started with an ICPC-style contest in the morning, which was followed by a lecture in the afternoon.
The first half of the lecture was reserved for discussion of the contest, while the second half centered around disjoint-set union (including rollback, partial persistence and also the more general "small-to-large" technique).

Day 7 started with a thematic contest in the morning, with problems involving disjoint-set union as well as game theory.
The first half of the lecture was reserved for discussion of the contest problems involving disjoint-set union, some of which required interesting tricks.
The second half focused on game theory (including acyclic games, Nim and the Sprague-Grundy theorem), and also covered the remaining problems from the contest.

## Resources
| Day | Lecture (in Portuguese) | Contest | Scoreboard |
| --- | ------- | ------- | ---------- |
| Day 6 &ndash; Jan 28th | [Video](https://www.youtube.com/watch?v=ARgMteH_K7A), [Slides](https://files.johnjq.com/slides/summer/union-find.pdf) | [Contest](http://maratona.ic.unicamp.br/MaratonaVerao2019/contests-b/20190128.pdf) | [Scoreboard](https://vjudge.net/contest/280563#rank) |
| Day 7 &ndash; Jan 29th | [Video](https://www.youtube.com/watch?v=5kk_5HcwqOg), [Slides](https://files.johnjq.com/slides/summer/game-theory.pdf) | [Contest](http://maratona.ic.unicamp.br/MaratonaVerao2019/contests-b/20190129.pdf) | [Scoreboard](https://vjudge.net/contest/281335#rank) |

## Problems from Day 6 (Jan 28th)
| Problem | Solution(s) |
| ------- | ----------- |
| [A &ndash; Keep Them Separated](https://open.kattis.com/problems/keepthemseparated) | [Solution 1 (safe)](day1/keepthemseparated.cpp), [Solution 2 (hackable)](day1/keepthemseparated_unsafer.cpp) |
| [B &ndash; The Values You Can Make](https://codeforces.com/contest/687/problem/C) | [Solution](day1/CF-687C.cpp) |
| [C &ndash; Roads](http://www.codah.club/tasks.php?lang=uk&show_task=5000001394) | [Solution](day1/APIO-roads.cpp) |
| [D &ndash; Journey](https://codeforces.com/contest/839/problem/C) | [Solution](day1/CF-839C.cpp) |
| [E &ndash; Alyona and mex](https://codeforces.com/contest/739/problem/A) | [Solution](day1/CF-739A.cpp) |
| [F &ndash; Dima and Bacteria](https://codeforces.com/contest/400/problem/D) | [Solution](day1/CF-400D.cpp) |
| [G &ndash; Remainders Game](https://codeforces.com/contest/687/problem/B) | [Solution](day1/CF-687B.cpp) |
| [H &ndash; Sonya and Queries](https://codeforces.com/contest/713/problem/A) | [Solution](day1/CF-713A.cpp) |
| [I &ndash; Cloud of Hashtags](https://codeforces.com/contest/777/problem/D) | [Solution](day1/CF-777D.cpp) |
| [J &ndash; A Story with Strings](https://www.codechef.com/problems/SSTORY) | [Solution](day1/codechef-SSTORY.cpp) |

## Problems from Day 7 (Jan 29th)
| Problem | Solution(s) |
| ------- | ----------- |
| [A &ndash; Learning Languages](https://codeforces.com/contest/277/problem/A) | [Solution](day2/CF-277A.cpp) |
| [B &ndash; Marbles](https://codeforces.com/gym/101908/problem/B) | [Solution](day2/GYM-101908B.cpp) |
| [C &ndash; Win or Freeze](https://codeforces.com/contest/150/problem/A) | [Solution 1 (dynamic programming)](day2/CF-150A.cpp), [Solution 2 (ad hoc)](day2/CF-150A-faster.cpp) |
| [D &ndash; Points](https://codeforces.com/gym/102078/problem/B) | [Solution](day2/seletiva-pontos.cpp) |
| [E &ndash; Mahmoud and a Dictionary](https://codeforces.com/contest/766/problem/D) | [Solution](day2/CF-766D.cpp) |
| [F &ndash; Strange Food Chain](https://www.spoj.com/problems/CHAIN/en/) | [Solution](day2/SPOJ-CHAIN.cpp) |
| [G &ndash; Lieges of Legendre](https://codeforces.com/contest/603/problem/C) | [Solution](day2/CF-603C.cpp) |
| [H &ndash; Soteros](https://codeforces.com/gym/101962/problem/J) | [Solution](day2/GYM-101962J.cpp) |
| [I &ndash; Coins Game](https://www.spoj.com/problems/MCOINS/en/) | [Solution](day2/SPOJ-MCOINS.cpp) |
| [J &ndash; Galaksija](https://open.kattis.com/problems/galaksija) | [Solution](day2/COCI15_galaksija.cpp) |
| [K &ndash; Pictionary](https://codeforces.com/gym/102078/problem/A) | [Solution 1 (slower)](day2/COCI18_pictionary.cpp), [Solution 2 (faster)](day2/COCI18_pictionary_faster.cpp) |
