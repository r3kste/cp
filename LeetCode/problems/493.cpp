#include <bits/stdc++.h>
using namespace std;

class Solution {
  private:
    long long merge(vector<int> &nums, int left, int mid, int right) {
        // arr[left..=mid] and arr[mid+1..=right]
        int idx1 = left;
        int idx2 = mid + 1;

        long long cnt = 0;

        for (idx1 = left; idx1 <= mid; idx1++) {
            while (idx2 <= right && nums[idx1] > 2LL * nums[idx2]) {
                idx2++;
            }
            cnt += (idx2 - (mid + 1));
        }

        idx1 = left;
        idx2 = mid + 1;

        vector<int> temp(right - left + 1);
        int idx = 0;

        while (idx1 <= mid && idx2 <= right) {
            if (nums[idx1] < nums[idx2]) {
                temp[idx++] = nums[idx1++];
            } else {
                temp[idx++] = nums[idx2++];
            }
        }

        while (idx1 <= mid) {
            temp[idx++] = nums[idx1++];
        }

        while (idx2 <= right) {
            temp[idx++] = nums[idx2++];
        }

        for (int i = 0; i < temp.size(); i++) {
            nums[left + i] = temp[i];
        }

        return cnt;
    }

    long long merge_sort(vector<int> &nums, int left, int right) {
        if (left >= right) {
            return 0;
        }

        long long cnt = 0;

        int mid = (left + right) / 2;
        cnt += merge_sort(nums, left, mid);
        cnt += merge_sort(nums, mid + 1, right);
        cnt += merge(nums, left, mid, right);

        return cnt;
    }

  public:
    int reversePairs(vector<int> &nums) {
        return merge_sort(nums, 0, nums.size() - 1);
    }
};
