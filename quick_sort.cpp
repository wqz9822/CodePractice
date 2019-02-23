#include <iostream>
#include <vector>

using namespace std;

int partition(vector<int>& nums, int l, int h) {
    int mid = (l + h) / 2;
    const int pivot = nums[mid];
    cout << "pivot: " << pivot << endl;
    swap(nums[mid], nums.back());
    size_t sorted = 0;
    for(size_t i = 0; i < nums.size(); ++i){
        if (nums[i] <= pivot) {
            swap(nums[i], nums[sorted]);
            sorted++;
        }
    } 
    return sorted;
}   

void quicksort(vector<int>& nums, int l, int h) {
    if(l < h) {
        int pivot = partition(nums, l, h);
        quicksort(nums, l, pivot-1);
        quicksort(nums, pivot+1, h);
    }
}

void print_nums(const vector<int>& nums) {
    for(const auto& n : nums) {
        cout << n << ", ";
    }
    cout << endl;
}


int main(int argc, char** argv) {
    vector<int> nums {2 ,3, 1, 5, -1, 0, 4};
    print_nums(nums);
    quicksort(nums, 0, nums.size());
    print_nums(nums);
	return 0;
}
