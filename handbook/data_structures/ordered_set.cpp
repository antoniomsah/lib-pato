/**
 * Ordered set (0-indexed)
 *
 * It has the same properties and functions of the regular set
 * Two more functions with complexity O(log|s|):
 * find_by_order(k) - iterator to the element with index k
 * order_of_key(k) - index of the element k in the set
 **/
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <class T>
using ord_set = tree<T, null_type, less<T>, rb_tree_tag,
	tree_order_statistics_node_update>;
