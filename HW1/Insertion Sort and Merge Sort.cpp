#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
using namespace chrono;

// =========================
// 印出前10個排序結果
// =========================
void PrintArray(const vector<int>& arr)
{
    int limit = min((int)arr.size(), 10);
    for (int i = 0; i < limit; i++)
        cout << arr[i] << " ";
    cout << "..." << endl;
}

// =========================
// Insertion Sort
// =========================
void InsertionSort(vector<int>& arr)
{
    for (int i = 1; i < arr.size(); i++)
    {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

// =========================
// Merge
// =========================
void Merge(vector<int>& arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];

    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int iIndex = 0, jIndex = 0;
    int k = left;

    while (iIndex < n1 && jIndex < n2)
    {
        if (L[iIndex] <= R[jIndex])
            arr[k++] = L[iIndex++];
        else
            arr[k++] = R[jIndex++];
    }

    while (iIndex < n1)
        arr[k++] = L[iIndex++];

    while (jIndex < n2)
        arr[k++] = R[jIndex++];
}

// =========================
// Merge Sort
// =========================
void MergeSort(vector<int>& arr, int left, int right)
{
    if (left < right)
    {
        int mid = (left + right) / 2;

        MergeSort(arr, left, mid);
        MergeSort(arr, mid + 1, right);

        Merge(arr, left, mid, right);
    }
}

// =========================
// 測試 Insertion Sort
// =========================
void TestInsertion(const vector<int>& arr)
{
    double total = 0;
    vector<int> result;

    for (int i = 0; i < 3; i++)
    {
        vector<int> copy = arr;

        auto start = high_resolution_clock::now();

        InsertionSort(copy);

        auto end = high_resolution_clock::now();

        total += duration<double, milli>(end - start).count();

        if (i == 0) result = copy; // 存第一次結果來印
    }

    cout << "Sorted Result: ";
    PrintArray(result);

    cout << "Insertion Avg: ";
    cout << fixed;
    cout.precision(3);
    cout << (total / 3) << " ms" << endl;
}

// =========================
// 測試 Merge Sort
// =========================
void TestMerge(const vector<int>& arr)
{
    double total = 0;
    vector<int> result;

    for (int i = 0; i < 3; i++)
    {
        vector<int> copy = arr;

        auto start = high_resolution_clock::now();

        MergeSort(copy, 0, copy.size() - 1);

        auto end = high_resolution_clock::now();

        total += duration<double, milli>(end - start).count();

        if (i == 0) result = copy; // 存第一次結果來印
    }

    cout << "Sorted Result: ";
    PrintArray(result);

    cout << "Merge Avg: ";
    cout << fixed;
    cout.precision(3);
    cout << (total / 3) << " ms" << endl;
}

// =========================
// Best Case（已排序）
// =========================
vector<int> GenerateBestCase(int n)
{
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        arr[i] = i + 1;
    return arr;
}

// =========================
// Worst Case（反排序）
// =========================
vector<int> GenerateWorstCase(int n)
{
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        arr[i] = n - i;
    return arr;
}

// =========================
// Main
// =========================
int main()
{
    vector<int> best100 = GenerateBestCase(100);
    vector<int> worst100 = GenerateWorstCase(100);

    vector<int> best10000 = GenerateBestCase(10000);
    vector<int> worst10000 = GenerateWorstCase(10000);

    cout << "=== Insertion Sort ===" << endl;

    cout << "Best Case n = 100" << endl;
    TestInsertion(best100);

    cout << "\nBest Case n = 10000" << endl;
    TestInsertion(best10000);

    cout << "\nWorst Case n = 100" << endl;
    TestInsertion(worst100);

    cout << "\nWorst Case n = 10000" << endl;
    TestInsertion(worst10000);

    cout << "\n=== Merge Sort ===" << endl;

    cout << "Best Case n = 100" << endl;
    TestMerge(best100);

    cout << "\nBest Case n = 10000" << endl;
    TestMerge(best10000);

    cout << "\nWorst Case n = 100" << endl;
    TestMerge(worst100);

    cout << "\nWorst Case n = 10000" << endl;
    TestMerge(worst10000);

    return 0;
}
