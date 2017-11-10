FIFO - first in first out
Uses the standard template library deque. The page replacement algorithm implemented will pop the page from front when the deque is full, then push the page new onto the back of the deque.

LRU - least recently used
A struct was created which holds the page number as an int and an int which holds the the time of when it was last referenced. An array of these structs was created as the page table. The algortihm implemented iterates through the full table to find the page number with the smallest time, which would be the oldest or least recenlty used, and removes it from the table. Then all of the pages after it are moved down by one spot in the array to fill in the gap created. Then the last spot in the array is filled with the new page with the current time.

LFU - least frequently used
A struct was created which holds the page number as an int and an int which holds a count of everytime that the page number is called. An array of these structs was created as the page table. The algortihm implemented iterates through the full table to find the page number with smallest count of requests and removes it from the table. Then all of the pages after it are moved down by one spot in the array to fill in the gap created. Then the last spot in the array is filled with the new page with a count of 0.

Rand - random
A basic int array is created which holds the all of the page numbers. The algorithm will randomly select a number between 0 and tableSize-1. The number that is selected is the index in the array where the page is removed. Then all of the pages after it are moved down to fill in the array and then the last spot is filled with the new page.
This algorithm could be used because it would be fair, since any page can be replaced. It also is a much simpler implementation than the other algorithms. However, it would not be the best in an actual implementation because it could randomly replace a page that is currently in use.

Improvement of the algorithms:
Based on these results, lru had the best hit rate, followed by fifo, rand, and then lfu. These results were based on the testfile, which used a sequence of random numbers. In an actual implementation the data would be read off the disk in chunks, requests would be given sequentially, and would be stored in RAM.
All of the algorithms could be improved by borrowing aspects from either LFU or LRU. LFU could be improved by also adding a clock variable similar to LRU, then it would find all the pages with the least requests, and then remove the page with the oldest clock request time out of these pages. Similarly, LRU could also be improved by adding a frequency counter and then finding a certain amount of the oldest pages, perhaps based on the table size, i.e. 5 of the oldest pages in a page table of size 100. Then from the group of oldest pages check the frequency of their access and remove the least frequenly used from this group of pages. FIFO could be improved by adding a frequeny variable to it, and skipping any page at the front if it has a certain number of references, i.e. 5 requests minimum is required to be skipped. The first page has 5 references, so it's skipped, second page has 6 requests, so skipped, and then the third page has 1 reference, so it's removed. RAND could be improved by using a clock variable, selecting a random group of pages from the page table, then from the group remove the page which was not accessed in a long time is removed. These would all increase the difficulty of the implementations, but would improve the hit rates.

Raw Results:
tableSize	fifo	lru		lfu		rand
10			5075	5075	5079	5073
50			4865	4865	4885	4853
51			4859	4859	4883	4849
100			4591	4591	4663	4598
101			4585	4585	4660	4560
150			4289	4289	4399	4296
151			4281	4281	4392	4303
200			4000	4000	4178	4049
201			3999	3999	4175	4040
250			3758	3758	3954	3777
251			3756	3756	3950	3765
300			3496	3496	3728	3557
301			3481	3481	3724	3534
350			3249	3245	3492	3344
351			3249	3247	3490	3301
400			3026	3021	3258	3060
401			3020	3016	3255	3082
450			2832	2828	3022	2895
451			2824	2821	3019	2874
500			2616	2609	2802	2673

Average Values for Ranges:
tableSize	fifo	lru		lfu		rand
10-50		4970	4970	4982	4963
51-100		4725	4725	4773	4723.5
101-150		4437	4437	4529.5	4428
151-200		4140.5	4140.5	4285	4176
201-250		3878.5	3878.5	4064.5	3908.5
251-300		3626	3626	3839	3661
301-350		3365	3363	3608	3439
351-400		3137.5	3134	3374	3180.5
401-450		2926	2922	3138.5	2988.5
451-500		2720	2715	2910.5	2773.5

5123 Requests
hit rate=1-(faults/requests)
tableSize	fifo			lru				lfu				rand
10-50		0.02986531329	0.02986531329	0.02752293578	0.03123170018
51-100		0.07768885419	0.07768885419	0.06831934413	0.07798165138
101-150		0.1339059145	0.1339059145	0.1158500878	0.1356626976
151-200		0.1917821589	0.1917821589	0.1635760297	0.1848526254
201-250		0.2429240679	0.2429240679	0.2066172165	0.2370681241
251-300		0.2922115948	0.2922115948	0.2506343939	0.2853796604
301-350		0.3431583057	0.3435487019	0.295725161		0.3287136443
351-400		0.3875658794	0.3882490728	0.3414015225	0.3791723599
401-450		0.428850283		0.4296310755	0.3873706812	0.4166504002
451-500		0.469061097		0.4700370876	0.431875854		0.4586179973
