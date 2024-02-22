#include "file_size_max_heap.hpp"
using namespace cs251;

void file_size_max_heap::push(const size_t fileSize, const handle handle)
{
    file_size_max_heap_node newNode;
    newNode.m_handle = handle;
    newNode.m_value = fileSize;
    m_nodes.push_back(newNode);

    //heapify up for max heap
    size_t current = m_nodeSize;
    while (current > 0) {
        size_t parent = (current - 1) / 2;
        if (m_nodes[current].m_value > m_nodes[parent].m_value) {
            //maxheap: swap if the current node has a larger value than its parent
            std::swap(m_nodes[current], m_nodes[parent]);
            current = parent;
        } else {
            // already in position
            break;
        }
    }

    m_nodeSize++;
}

handle file_size_max_heap::top() const
{
	if (m_nodeSize == 0) {
        throw heap_empty();
    }

    return m_nodes[0].m_handle;
}

void file_size_max_heap::remove(const handle handle)
{
    size_t location = -1;

    for (int i = 0; i < m_nodes.size(); i++) {
        if (m_nodes[i].m_handle == handle) {
            location = i;
            break;
        }
    }

    if (location == -1) {
        throw invalid_handle();
    }

    m_nodes[location] = m_nodes.back();
    m_nodes.pop_back();
    m_nodeSize--;

    size_t current = location;
    bool sorted = false;

    while (!sorted) {
        //heapify
        size_t largestIndex = current;
        size_t leftIndex = 2 * current + 1;
        size_t rightIndex = 2 * current + 2;

        if (leftIndex < m_nodeSize && m_nodes[leftIndex].m_value > m_nodes[largestIndex].m_value) {
            largestIndex = leftIndex;
        }

        if (rightIndex < m_nodeSize && m_nodes[rightIndex].m_value > m_nodes[largestIndex].m_value) {
            largestIndex = rightIndex;
        }

        if (largestIndex != current) {
            //swap if the current node has a smaller value than its children
            std::swap(m_nodes[current], m_nodes[largestIndex]);
            current = largestIndex;
            sorted = false;
        } else {
            sorted = true;
        }
    }
}
