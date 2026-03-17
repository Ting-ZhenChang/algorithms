using System;
using System.Diagnostics;

class Program
{
    static void Main(string[] args)
    {
        // n=100
        int[] best100 = GenerateBestCase(100);
        int[] worst100 = GenerateWorstCase(100);

        // n=10000
        int[] best10000 = GenerateBestCase(10000);
        int[] worst10000 = GenerateWorstCase(10000);

        Console.WriteLine("=== Insertion Sort ===");
        
        Console.Write("Best Case n = 100 ");
        TestInsertion(best100);
        Console.Write("Best Case n = 10000 ");
        TestInsertion(best10000);
        Console.Write("Worst Case n = 100 ");
        TestInsertion(worst100);
        Console.Write("Worst Case n = 10000 ");
        TestInsertion(worst10000);

        Console.WriteLine("\n=== Merge Sort ===");

        Console.Write("Best Case n = 100 ");
        TestMerge(best100);
        Console.Write("Best Case n = 10000 ");
        TestMerge(best10000);
        Console.Write("Worst Case n = 100 ");
        TestMerge(worst100);
        Console.Write("Worst Case n = 10000 ");
        TestMerge(worst10000);

    }

    // =========================
    // Insertion Sort（插入排序）
    // =========================
    static void InsertionSort(int[] arr)
    {
        // 從第二個元素開始
        for (int i = 1; i < arr.Length; i++)
        {
            int key = arr[i];   // 要插入的數
            int j = i - 1;

            // 把比 key 大的數往右移
            while (j >= 0 && arr[j] > key)
            {
                arr[j + 1] = arr[j];
                j--;
            }

            // 把 key 放到正確位置
            arr[j + 1] = key;
        }
    }

    // =========================
    // Merge Sort（合併排序）
    // =========================
    static void MergeSort(int[] arr, int left, int right)
    {
        if (left < right)
        {
            int mid = (left + right) / 2;

            // 左半部排序
            MergeSort(arr, left, mid);

            // 右半部排序
            MergeSort(arr, mid + 1, right);

            // 合併
            Merge(arr, left, mid, right);
        }
    }

    static void Merge(int[] arr, int left, int mid, int right)
    {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        int[] L = new int[n1];
        int[] R = new int[n2];

        // 複製資料到暫存陣列
        for (int i = 0; i < n1; i++)
            L[i] = arr[left + i];

        for (int j = 0; j < n2; j++)
            R[j] = arr[mid + 1 + j];

        int iIndex = 0, jIndex = 0;
        int k = left;

        // 比較兩邊大小並合併
        while (iIndex < n1 && jIndex < n2)
        {
            if (L[iIndex] <= R[jIndex])
            {
                arr[k] = L[iIndex];
                iIndex++;
            }
            else
            {
                arr[k] = R[jIndex];
                jIndex++;
            }
            k++;
        }

        // 剩下的直接補上
        while (iIndex < n1)
        {
            arr[k] = L[iIndex];
            iIndex++;
            k++;
        }

        while (jIndex < n2)
        {
            arr[k] = R[jIndex];
            jIndex++;
            k++;
        }
    }

    // =========================
    // 測試 Insertion Sort（取平均）
    // =========================
    static void TestInsertion(int[] arr)
    {
        double total = 0; // 用小數點紀錄總時間

        for (int i = 0; i < 3; i++) // 跑三次
        {
            int[] copy = (int[])arr.Clone(); // 複製資料（避免被改掉）

            Stopwatch sw = new Stopwatch();
            sw.Start(); // 開始計時

            InsertionSort(copy); // 執行排序

            sw.Stop(); // 停止計時

            total += sw.Elapsed.TotalMilliseconds; //顯示小數ms
        }

        // 輸出平均時間
        Console.WriteLine("Insertion Avg: " + (total / 3).ToString("F3") + " ms");  //輸出固定三位小數
    }

    // =========================
    // 測試 Merge Sort（取平均）
    // =========================
    static void TestMerge(int[] arr)
    {
        double total = 0;

        for (int i = 0; i < 3; i++)
        {
            int[] copy = (int[])arr.Clone();

            Stopwatch sw = new Stopwatch();
            sw.Start();

            MergeSort(copy, 0, copy.Length - 1);

            sw.Stop();

            total += sw.Elapsed.TotalMilliseconds; //顯示小數ms
        }

        Console.WriteLine("Merge Avg: " + (total / 3).ToString("F3") + " ms");  //輸出固定三位小數
    }

    // =========================
    // 產生 Best Case（已排序）
    // =========================
    static int[] GenerateBestCase(int n)
    {
        int[] arr = new int[n];

        for (int i = 0; i < n; i++)
        {
            arr[i] = i + 1;
        }

        return arr;
    }

    // =========================
    // 產生 Worst Case（反排序）
    // =========================
    static int[] GenerateWorstCase(int n)
    {
        int[] arr = new int[n];

        for (int i = 0; i < n; i++)
        {
            arr[i] = n - i;
        }

        return arr;
    }
}
