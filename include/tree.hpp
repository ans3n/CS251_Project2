#pragma once
#include "cstring"
#include "sstream"
#include "string"
#include "exception"
#include "vector"
#include "queue"

namespace cs251
{
    typedef int handle;

    class invalid_handle : public std::runtime_error {
    public: invalid_handle() : std::runtime_error("Invalid handle!") {} };
    class recycled_node : public std::runtime_error {
    public: recycled_node() : std::runtime_error("Node is recycled!") {} };

    template<typename tree_node_data>
    class tree_node {
        //Friend class grant private access to another class.
        template<typename tnd>
        friend class tree;

        //TODO: You may add private members/methods here.

        /**
         * The handle of current node, should be the index of current node within the vector array in tree.
         */
        handle m_handle = -1;
        /**
         * Whether the node is recycled.
         */
        bool m_recycled = true;
        /**
         * The content of the node.
         */
        tree_node_data m_data = {};
        /**
         * The handle of the parent node.
         */
        handle m_parentHandle = -1;
        /**
         * List of handles to all children.
         */
        std::vector<handle> m_childrenHandles{};

    public:
        /**
         * \brief Retrieve the data for this node.
         * \return The modifiable reference to the node's data.
         */
        tree_node_data& ref_data();
        /**
         * \brief Check if the node is recycled.
         * \return Whether this node is recycled or not.
         */
        bool is_recycled() const;
        /**
         * \brief Get the handle of this node.
         * \return The handle of this node.
         */
        handle get_handle() const;
        /**
         * \brief Get the handle of this node's parent.
         * \return The handle of this node's parent.
         */
        handle get_parent_handle() const;
        /**
         * \brief Get the list of handles of this node's children.
         * \return The list of handles of this node's children.
         */
        const std::vector<handle>& peek_children_handles() const;
    };

    template<typename tree_node_data>
    class tree
    {
    public:
        /**
         * \brief The constructor of the tree class. You should allocate the root node here.
         */
        tree();
        /**
         * \brief Allocate a new node as root from pool or creating a new one.
         * \return The handle of the new node.
         */
        handle allocate(handle parentHandle);
        /**
         * \brief Remove (recycle) a node. Remove all descendent nodes.
         * \param handle The handle of the target node to be removed.
         */
        void remove(handle handle);
        /**
         * \brief Attach a node to another node as its child.
         * \param targetHandle The handle of the target node as child.
         * \param parentHandle The handle of the parent node.
         */
        void set_parent(handle targetHandle, handle parentHandle);
        /**
         * \brief Return the constant reference to the list of nodes.
         * \return Constant reference to the list of nodes.
         */
        const std::vector<tree_node<tree_node_data>>& peek_nodes() const;
        /**
         * \brief Retrieve the node with its handle.
         * \param handle The handle of the target node.
         * \return The reference to the node.
         */
        tree_node<tree_node_data>& ref_node(handle handle);
    private:
        //TODO: You may add private members/methods here.

        /**
         * The storage for all nodes.
         */
        std::vector<tree_node<tree_node_data>> m_nodes {};
        /**
         * The pool that keep track of the recycled nodes.
         */
        std::queue<handle> m_node_pool {};
    };

    template <typename tree_node_data>
    tree_node_data& tree_node<tree_node_data>::ref_data()
    {
        if (is_recycled()) {
            throw recycled_node();
        }
        return m_data;
    }

    template <typename tree_node_data>
    bool tree_node<tree_node_data>::is_recycled() const
    {
        return m_recycled;
    }

    template <typename tree_node_data>
    handle tree_node<tree_node_data>::get_handle() const
    {
        return m_handle;
    }

    template <typename tree_node_data>
    handle tree_node<tree_node_data>::get_parent_handle() const
    {
        if (is_recycled()) {
            throw recycled_node();
        }
        return m_parentHandle;
    }

    template <typename tree_node_data>
    const std::vector<handle>& tree_node<tree_node_data>::peek_children_handles() const
    {
        if (is_recycled()) {
            throw recycled_node();
        }
        return m_childrenHandles;
    }

    template <typename tree_node_data>
    tree<tree_node_data>::tree()
    {
        tree_node<tree_node_data> rootNode;
        //root node is a new node thus not recycled
        rootNode.m_recycled = false;

        //root node is newly created so no data
        rootNode.m_data = {};

        //root node by default is handle 0
        rootNode.m_handle = 0;
        m_nodes.push_back(rootNode);
    }

    template <typename tree_node_data>
    handle tree<tree_node_data>::allocate(handle parentHandle)
    {
        if (parentHandle < 0 || parentHandle >= m_nodes.size()) {
            throw invalid_handle();
        }
        if (m_nodes[parentHandle].is_recycled()) {
            throw recycled_node();
        }

        tree_node<tree_node_data> newNode;
        handle newHandle = 0;
        if (!m_node_pool.empty()) {
            newNode.m_handle = m_node_pool.front();
            m_node_pool.pop();
            newNode = m_nodes[newNode.m_handle];
        } else {
            newNode.m_handle = m_nodes.size();
            m_nodes.push_back(newNode);
        }

        newHandle = newNode.m_handle;
        m_nodes[newHandle].m_recycled = false;

        //set changed handles
        m_nodes[newHandle].m_handle = newHandle;
        m_nodes[newHandle].m_parentHandle = parentHandle;

        //push onto vector
        m_nodes[parentHandle].m_childrenHandles.push_back(newHandle);

        return newNode.m_handle;
    }

    template <typename tree_node_data>
    void tree<tree_node_data>::remove(const handle targetHandle)
    {
        if (targetHandle <= 0 || targetHandle >= m_nodes.size()) {
            throw invalid_handle();
        }
        if (m_nodes[targetHandle].is_recycled()) {
            throw recycled_node();
        }

        // Recurse through the node's children
        auto& childrenHandles = m_nodes[targetHandle].m_childrenHandles;
        while (!childrenHandles.empty()) {
            remove(childrenHandles.front());
        }

        handle parentHandle = m_nodes[targetHandle].m_parentHandle;
        // Get all children of the handle's parent
        auto& parentChildrenHandles = m_nodes[parentHandle].m_childrenHandles;

        // Iterate over the parent's children vector
        for (auto iterator = parentChildrenHandles.begin(); iterator != parentChildrenHandles.end(); iterator++) {
            if (*iterator == targetHandle) {
                // Erase the handle from the parent's children vector
                parentChildrenHandles.erase(iterator);
                break;
            }
        }

        //push the target node itself to recycled
        m_nodes[targetHandle].m_parentHandle = -1;
        m_nodes[targetHandle].m_recycled = true;
        m_nodes[targetHandle].m_data = {};

        m_node_pool.push(targetHandle);

    }

    template <typename tree_node_data>
    void tree<tree_node_data>::set_parent(const handle targetHandle, const handle parentHandle)
    {
        if (targetHandle <= 0 || targetHandle >= m_nodes.size() || parentHandle < 0 || parentHandle >= m_nodes.size()) {
            throw invalid_handle();
        }
        if (m_nodes[targetHandle].is_recycled() || m_nodes[parentHandle].is_recycled()) {
            throw recycled_node();
        }

        handle targetParentHandle = m_nodes[targetHandle].m_parentHandle;
        //remove target handle from original parent's children
        //get all children of the handle's parent
        auto& targetParentChildrens = m_nodes[targetParentHandle].m_childrenHandles;

        for (auto iterator = targetParentChildrens.begin(); iterator != targetParentChildrens.end(); iterator++) {
            if (*iterator == targetHandle) {
                // Erase the handle from the parent's children vector
                targetParentChildrens.erase(iterator);
                break;
            }
        }

        // Set the parent of the node represented by targetHandle to the node represented by parentHandle
        m_nodes[targetHandle].m_parentHandle = parentHandle;
        //add target handle as part of the target parent's children
        m_nodes[parentHandle].m_childrenHandles.push_back(targetHandle);
    }

    template <typename tree_node_data>
    const std::vector<tree_node<tree_node_data>>& tree<tree_node_data>::peek_nodes() const
    {
        return m_nodes;
    }

    template <typename tree_node_data>
    tree_node<tree_node_data>& tree<tree_node_data>::ref_node(handle handle)
    {
        if (handle < 0 || handle >= m_nodes.size()) {
            throw invalid_handle();
        }
        return m_nodes[handle];
    }
}
