//#4. Median of Two Sorted Arrays
//Hard
//Method: two methods
//Complexity: Time O(logN) O(log(M+N)); Space O(1)

class Solution {
public:
	//Method 1: binary search in the shorter vector, and we can determine its position using the expected position at the other vector
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.size() < nums2.size())
            swap(nums1, nums2);
        if (nums2.empty()) {
            if (nums1.size() % 2) return nums1[nums1.size() / 2];
            return (nums1[nums1.size() / 2 - 1] + nums1[nums1.size() / 2]) / 2.0;
        }
        int l = 0, h = nums2.size() - 1, t = (nums1.size() + nums2.size()) / 2, p = 0;
        while (l <= h) {
            p = (l + h) / 2;
            if (nums1[t - p - 1] > nums2[p]) l = p + 1;
            else if (t - p < nums1.size() && nums1[t - p] < nums2[p]) h = p - 1;
            else break;
        }
        double res = nums2[p];
        if (l > h) {
            int r = (nums1[t - p - 1] > nums2[p]) ? t - p - 1 : t - p;
            res = nums1[r];
            if ((nums1.size() + nums2.size()) % 2 == 0) {
                if (r == 0 || nums1[r - 1] < nums2[h]) return (res + nums2[h]) / 2.0;
                return (res + nums1[r - 1]) / 2.0;
            }
            return res;
        }
        if ((nums1.size() + nums2.size()) % 2 == 0) return (res + max(nums2[p - 1], nums1[t - p - 1])) / 2.0;
        return res;
    }

    //Method 2: binary search two vectors in a round-robbin pattern
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.empty() || nums2.empty()) {
            if (nums1.empty()) swap(nums1, nums2);
            if (nums1.size() % 2) return nums1[nums1.size() / 2];
            return (nums1[nums1.size() / 2 - 1] + nums1[nums1.size() / 2]) / 2.0;
        }
        int l1 = 0, l2 = 0, h1 = nums1.size() - 1, h2 = nums2.size() - 1, target = (nums1.size() + nums2.size()) / 2, p1 = h1 / 2, p2 = 0;
        while (1) {
            if (nums1[p1] < nums2[l2]) {
                p2 = l2 - 1;
            } else {
                if (nums1[p1] >= nums2[h2]) {
                    p2 = h2;
                } else {
                    int h = h2, l = l2;
                    while (h != l) {
                        p2 = (h + l) / 2;
                        if (nums2[p2] > nums1[p1]) {
                            h = p2;
                        } else {
                            l = p2 + 1;
                        }
                    }
                    p2 = (nums2[l] <= nums1[p1]) ? l : l - 1;
                }
            }
            if (p1 + p2 + 1 == target) {
                if ((nums1.size() + nums2.size()) % 2) return nums1[p1];
                if (p1 == 0 || p2 != -1 && nums1[p1 - 1] < nums2[p2]) return (nums1[p1] + nums2[p2]) / 2.0;
                return (nums1[p1] + nums1[p1 - 1]) / 2.0;
            }
            if (p1 + p2 + 1 < target) {
                l1 = p2 + 1;
                l2 = p1 + 1;
                swap(h1, h2);
            } else {
                h1 = p2;
                h2 = p1 - 1;
                swap(l1, l2);
            }
            swap(nums1, nums2);
            p1 = (l1 + h1) / 2;
        }
    }
};