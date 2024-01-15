#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> twoSum(std::vector<int>& nums, int target) {
    std::vector<int> result;
    std::sort(nums.begin(), nums.end());

    int left = 0;
    int right = nums.size() - 1;

    while (left < right) {
        int currentSum = nums[left] + nums[right];

        if (currentSum == target) {
            result.push_back(left);
            result.push_back(right);
            return result;
        } else if (currentSum < target) {
            left++;
        } else {
            right--;
        }
    }

    // If no solution is found, return an empty vector
    return {};
}

int main() {
    // Example 1
    std::vector<int> nums1 = {2, 7, 11, 15};
    int target1 = 9;
    std::vector<int> result1 = twoSum(nums1, target1);

    std::cout << "Example 1 Output: [" << result1[0] << ", " << result1[1] << "]\n";

    // Example 2
    std::vector<int> nums2 = {3, 2, 4};
    int target2 = 6;
    std::vector<int> result2 = twoSum(nums2, target2);

    std::cout << "Example 2 Output: [" << result2[0] << ", " << result2[1] << "]\n";

    return 0;
}
