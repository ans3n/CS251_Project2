#include "file_size_max_heap.hpp"
using namespace cs251;

void file_size_max_heap::push(const size_t fileSize, const handle handle)
{
    file_size_max_heap_node newNode;
    newNode.m_handle = handle;
    newNode.m_value = fileSize;
    m_nodes.push_back(newNode);

    //heapify up for max heap
    size_t currentIndex = m_nodeSize;
    while (currentIndex > 0) {
        size_t parentIndex = (currentIndex - 1) / 2;
        if (m_nodes[currentIndex].m_value > m_nodes[parentIndex].m_value) {
            // Swap nodes if the current node has a larger value than its parent
            std::swap(m_nodes[currentIndex], m_nodes[parentIndex]);
            currentIndex = parentIndex;
        } else {
            // already in position
            break;
        }
    }

    m_nodeSize++;
}

handle file_size_max_heap::top() const
{
	//TODO: Remove following line and add your implementation here.
	throw std::logic_error("file_size_max_heap::" + std::string(__FUNCTION__) + " not implemented");
}

void file_size_max_heap::remove(const handle handle)
{

}
