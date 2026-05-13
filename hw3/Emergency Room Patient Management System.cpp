// Emergency Room Patient Management System (Max-Heap)

#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Patient
{
    string name; //name = 病人姓名
    int priority; // priority = 病情嚴重程度
};

class MaxHeap
{
private:
    vector<Patient> heap;

    // 交換兩個病人的位置
    void swapPatient(int a, int b)
    {
        Patient temp = heap[a];
        heap[a] = heap[b];
        heap[b] = temp;
    }

    // 往上移動(heapifyUp) 
    // 若 child priority > parent priority, 交換index 和 parent
    void heapifyUp(int index)
    {
        while (index > 1)
        {
            int parent = index / 2;

            if (heap[index].priority > heap[parent].priority)
            {
                swapPatient(index, parent);
                index = parent;
            }
            else
            {
                break;
            }
        }
    }

    // 往下移動(heapifyDown) 
    // 使用於Extract-Max 後, heap.size需減1
    // 比較左右節點, 找出最大child, 若child > parent則交換
    void heapifyDown(int index)
    {
        int size = heap.size() - 1;

        while (true)
        {
            int left = index * 2;
            int right = index * 2 + 1;
            int largest = index;

            //跟 left child 比較
            if (left <= size &&
                heap[left].priority > heap[largest].priority)
            {
                largest = left;
            }

            // 跟 right child 比較
            if (right <= size &&
                heap[right].priority > heap[largest].priority)
            {
                largest = right;
            }

            // index已經為最大值
            if (largest == index)
            {
                break;
            }

            swapPatient(index, largest);
            index = largest;
        }
    }

public:
    MaxHeap()
    {
        // 讓 heap 從 index 1 開始
        heap.push_back({ "dummy", -1 });
    }

    // Insert: 建立病人, push back到heap最後, 並呼叫heapifyUp
    void insert(string name, int priority)
    {
        Patient p;
        p.name = name;
        p.priority = priority;

        heap.push_back(p);

        int index = heap.size() - 1;

        heapifyUp(index);
    }

    // Extract-Max: 移除 priority 最大的病人
    void extractMax()
    {
        if (heap.size() <= 1)
        {
            cout << "[E] Heap is empty" << endl;
            return;
        }

        Patient maxPatient = heap[1];

        cout << "[E] Extract: "
            << maxPatient.name
            << "("
            << maxPatient.priority
            << ")"
            << endl;

        int lastIndex = heap.size() - 1;

        // 最後元素移到 root
        heap[1] = heap[lastIndex];

        // 移除最後一個元素
        heap.pop_back();

        // 使用heapifyDown修正 heap 次序
        if (heap.size() > 1)
        {
            heapifyDown(1);
        }
    }

    // Update priority
    void update(int index, int newPriority)
    {
        int size = heap.size() - 1;

        if (index < 1 || index > size)
        {
            cout << "[U] Invalid index" << endl;
            return;
        }

        int oldPriority = heap[index].priority;

        heap[index].priority = newPriority;

        // priority 增加, 表示可能比 parent 大, 要做heapifyUp
        if (newPriority > oldPriority)
        {
            heapifyUp(index);
        }
        // priority 減少, 表示可能比 child 小, 要做heapifyDown
        else if (newPriority < oldPriority)
        {
            heapifyDown(index);
        }
    }

    // Show heap
    void show()
    {
        cout << "[S] Current Heap: [";

        for (int i = 1; i < heap.size(); i++)
        {
            cout << "("
                << heap[i].name
                << ", "
                << heap[i].priority
                << ")";

            if (i != heap.size() - 1)
            {
                cout << ", ";
            }
        }

        cout << "]" << endl;
    }
};

// 輸出 I、E、U、S的結果
int main()
{
    MaxHeap er;

    char command;

    while (cin >> command)
    {
        if (command == 'I')
        {
            string name;
            int priority;

            cin >> name >> priority;

            er.insert(name, priority);
        }
        else if (command == 'E')
        {
            er.extractMax();
        }
        else if (command == 'U')
        {
            int index;
            int newPriority;

            cin >> index >> newPriority;

            er.update(index, newPriority);
        }
        else if (command == 'S')
        {
            er.show();
        }
        else if (command == 'Q')
        {
            break;
        }
    }

    return 0;
}
