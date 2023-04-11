#include <iostream>
#include <vector>
#include <cassert>
#include <string>

// Vertex with index I has  parent [(I - 1) / 2] and childer 2I + 1  and 2I + 2
// This implementation of queue is based on a binary heap
class PriorityQueue{
private:
    std::vector<int> buffer;
    void swap (int parent_index, int children_index) {
        auto temporary = buffer[parent_index];
        buffer[parent_index] = buffer[children_index];
        buffer[children_index] = temporary;
    } 

    int getParentIndex(int index){
        return (index - 1) / 2;
    }

    void siftUp(int index) {
        while (index > 0 && buffer[getParentIndex(index)] <  buffer[index]) {
            swap(getParentIndex(index), index);
            index = getParentIndex(index);
        }
    }
    void siftDown(int index) {
        while (true) {
            int left  = (2 * index) + 1;
            int right = (2 * index) + 2;
            int largest = index;
            if (left < buffer.size() && buffer[index] < buffer[left]) {
                largest  = left;
            }
            if (right < buffer.size() && buffer[largest] < buffer[right]) {    /*Attract attention. Must compare with largest */
                largest  = right;
            }
            if (largest == index) return;
            swap(index, largest);
            index = largest;
        }
    }
public:
    void insert(int elem) {
        int index = buffer.size();
        buffer.push_back(elem);
        siftUp(index);
    }

    void printTree(int index = 0, int space = 0) {
        if(index >= buffer.size()) return;
        printTree(index * 2 + 1,space + 2);
        int sp = space;
                while (sp) {
            std::cout << " ";
            sp--;
        }
        std::cout << buffer[index] << std::endl;
        printTree(index * 2 + 2,space + 2);
    }

    int extractMax() {
        assert(!buffer.empty());
        int result = buffer[0];
        buffer[0] = buffer.back();
        buffer.pop_back();
        if (!buffer.empty()) {
            siftDown(0);
        }
        return result;
    }
    int getSize() {
        return buffer.size();
    }
};


void readCommandStepic(PriorityQueue& queue) {
    int count;
    int priority;
    std::string command;
    std::cin >> count;
    while (std::cin >> command) {
        if (command == "Insert") {
            std::cin >> priority;
            queue.insert(priority);
        } else if (command == "ExtractMax") {
            if(queue.getSize()) {
                queue.printTree();
                std::cout << queue.extractMax() << " " << queue.getSize() <<std::endl;
            }
        }
    }
}   


int main() {
    PriorityQueue queue;
    readCommandStepic(queue);
    return 0;

}