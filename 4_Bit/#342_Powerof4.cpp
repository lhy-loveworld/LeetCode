//#342
//Easy
//Arthor: lhy-loveworld
//Method: 
//Complexity: Time O(1); Space O(1)

class Solution {
public:
    bool isPowerOfFour(int num) {
        return (num & 0xAAAAAAAA) == 0 && (num & (num - 1)) == 0 && num != 0;
    }
};