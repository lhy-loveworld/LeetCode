//#167. Two Sum II - Input array is sorted
//Easy
//https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/?tab=Description
//Method: Two pointers or hash
//        This code use two pointers
//Arthor: lhy-loveworld
//Complexity: Space: O(N); Time: O(N)


class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int i = 0;
        int j = numbers.size() - 1;
        vector<int> r;
        while (numbers[i]+numbers[j] != target) {
            if (numbers[i]+numbers[j] < target) i++;
            else j--;
        }
        r.push_back(i+1);
        r.push_back(j+1);
        return r;
    }
};
