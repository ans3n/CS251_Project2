#include "filesystem.hpp"

#include <iostream>

using namespace cs251;

filesystem::filesystem(const size_t sizeLimit)
{
	//call tree() and set the size of some list to the passed in size limit??
}

handle filesystem::create_file(const size_t fileSize, const std::string& fileName)
{
	/*Exceptions*/
    //If the parentHandle doesn’t exist or isn’t a directory, throw invalid_handle.
    //  code: if the parent handle is in the m_node pool or is recycled or isn't in the directory pool, throw

    //If the fileName contains a ‘/’ character, throw invalid_name
    if (fileName.find('/') != -1) {
        throw invalid_name();
    }

    //If adding the file would exceed the file system capacity, throw exceeds_size.
    //  if greater than sizeLimit, throw

    //If an object with the same name already exists in the directory, throw file_exists
    //  search through entire directory or using .find() method if can, if found, throw

    //create a file as a child of the directory pointed to by the root directory
    //Instantiate the file with the given size and name.
}

handle filesystem::create_directory(const std::string& directoryName)
{
    /*Exceptions*/
    //If the parentHandle doesn’t exist or isn’t a directory, throw invalid_handle.
    //  code: if the parent handle is in the m_node pool or is recycled or isn't in the directory pool, throw

    //If the fileName contains a ‘/’ character, throw invalid_name
    if (directoryName.find('/') != -1) {
        throw invalid_name();
    }

    //If an object with the same name already exists in the directory, throw directory_exists
    //  code: run a loop through entire directory and compare each element, if found throw

    //Create a new directory as a child of the directory pointed to by the root directory
    //Instantiate the directory with the given name.

}

handle filesystem::create_link(const handle targetHandle, const std::string& linkName)
{
    /*Exceptions*/
    //If either the parentHandle or the targetHandle do not exist, throw invalid_handle.
    //  code: if is not in the handle vector or is recycled

    //If the parentHandle isn’t a directory, throw invalid_handle.
    // code: if parentHandle isn't in the directory list - need to check if recycled?

    //If the linkName contains a ‘/’ character, throw invalid_name.
    if (linkName.find("/") != -1) {
        throw invalid_name();
    }

    //If an object with the same name already exists in the directory, throw link_exists
    //  code: if the object exists, throw

    //Create a new link as a child of the directory pointed to by the root directory
    //Instantiate the link with the given name and have it point to targetHandle
}

bool filesystem::remove(const handle targetHandle)
{
	// If the targetHandle doesn’t exist, throw invalid_handle
    //  code: search through node vector to see if targetHandle isn't there or if it's recycled, then throw

    bool removed = false;

    //Delete the file, directory, or link indicated by targetHandle.
    // If the target is a directory, remove only if it's empty
    // If the target is a link, only remove the link, not the object it points to.
    // return true if the target is removed, and false otherwise

    return removed;
}

handle filesystem::create_file(const size_t fileSize, const std::string& fileName, const handle parentHandle)
{
    /*Exceptions*/
    //If the parentHandle doesn’t exist or isn’t a directory, throw invalid_handle.
    //  code: if the parent handle is in the m_node pool or is recycled or isn't in the directory pool, throw

    //If the fileName contains a ‘/’ character, throw invalid_name
    if (fileName.find('/') != -1) {
        throw invalid_name();
    }

    //If adding the file would exceed the file system capacity, throw exceeds_size.
    //  if greater than sizeLimit, throw

    //If an object with the same name already exists in the directory, throw file_exists
    //  search through entire directory or using .find() method if can, if found, throw

    //create a file as a child of the directory pointed to by the parent handle
    //Instantiate the file with the given size and name.
}

handle filesystem::create_directory(const std::string& directoryName, const handle parentHandle)
{
    /*Exceptions*/
    //If the parentHandle doesn’t exist or isn’t a directory, throw invalid_handle.
    //  code: if the parent handle is in the m_node pool or is recycled or isn't in the directory pool, throw

    //If the fileName contains a ‘/’ character, throw invalid_name
    if (directoryName.find('/') != -1) {
        throw invalid_name();
    }

    //If an object with the same name already exists in the directory, throw directory_exists
    //  code: run a loop through entire directory and compare each element, if found throw

    //Create a new directory as a child of the directory pointed to by the parentHandle directory
    //Instantiate the directory with the given name.
}

handle filesystem::create_link(const handle targetHandle, const std::string& linkName, const handle parentHandle)
{
    /*Exceptions*/
    //If either the parentHandle or the targetHandle do not exist, throw invalid_handle.
    //  code: if is not in the handle vector or is recycled

    //If the parentHandle isn’t a directory, throw invalid_handle.
    // code: if parentHandle isn't in the directory list - need to check if recycled?

    //If the linkName contains a ‘/’ character, throw invalid_name.
    if (linkName.find("/") != -1) {
        throw invalid_name();
    }

    //If an object with the same name already exists in the directory, throw link_exists
    //  code: if the object exists, throw

    //Create a new link as a child of the directory pointed to by the parent handle
    //Instantiate the link with the given name and have it point to targetHandle
}

std::string filesystem::get_absolute_path(const handle targetHandle)
{
    //If the targetHandle doesn’t exist, throw invalid_handle


}

std::string filesystem::get_name(const handle targetHandle)
{
	//TODO: Remove following line and add your implementation here.
  throw std::logic_error("filesystem::" + std::string(__FUNCTION__) + " not implemented");
}

void filesystem::rename(const handle targetHandle, const std::string& newName)
{
	//If the targetHandle doesn’t exist, throw invalid_handle.

    //If the newName contains a ‘/’ character, throw invalid_name.
    if (newName.find("/") != -1) {
        throw invalid_name();
    }

    //If a file/directory/symlink with newName already exists, throw name_exists

    //Rename the file/directory/symlink referred to by targetHandle to newName.
}

bool filesystem::exist(const handle targetHandle)
{
	//if target Handle exists in m_node and it doesn't exist in m_node_pool, return true
}

handle filesystem::get_handle(const std::string& absolutePath)
{
	//TODO: Remove following line and add your implementation here.
  throw std::logic_error("filesystem::" + std::string(__FUNCTION__) + " not implemented");
}

handle filesystem::follow(const handle targetHandle)
{
	//TODO: Remove following line and add your implementation here.
  throw std::logic_error("filesystem::" + std::string(__FUNCTION__) + " not implemented");
}

handle filesystem::get_largest_file_handle() const
{
	//TODO: Remove following line and add your implementation here.
  throw std::logic_error("filesystem::" + std::string(__FUNCTION__) + " not implemented");
}

size_t filesystem::get_available_size() const
{
	//TODO: Remove following line and add your implementation here.
  throw std::logic_error("filesystem::" + std::string(__FUNCTION__) + " not implemented");
}

size_t filesystem::get_file_size(const handle targetHandle)
{
	//TODO: Remove following line and add your implementation here.
  throw std::logic_error("filesystem::" + std::string(__FUNCTION__) + " not implemented");
}

size_t filesystem::get_file_size(const std::string& absolutePath)
{
	//TODO: Remove following line and add your implementation here.
  throw std::logic_error("filesystem::" + std::string(__FUNCTION__) + " not implemented");
}

std::string filesystem::print_layout()
{
	std::stringstream ss{};
	const auto& node = m_fileSystemNodes.ref_node(0);
	for (const auto& childHandle : node.peek_children_handles()) {
		print_traverse(0, ss, childHandle);
	}
	return ss.str();
}

void filesystem::print_traverse(const size_t level, std::stringstream& ss, const handle targetHandle)
{
	auto& node = m_fileSystemNodes.ref_node(targetHandle);
	std::stringstream indentation{};
	for (auto i = level; i > 0; i--)
	{
		indentation << "\t";
	}
	std::string type{};
	switch (node.ref_data().m_type)
	{
	case node_type::Directory: type = "[D]"; break;
	case node_type::Link: type = "[L]"; break;
	case node_type::File: type = "[F]"; break;
	}
	ss << indentation.str() << type << node.ref_data().m_name;
	if (node.ref_data().m_type == node_type::Link)
	{
		try {
			const auto path = get_absolute_path(follow(node.get_handle()));
			ss << " [->" << path << "]";
		}
		catch (const std::exception& e)
		{
			ss << " [invalid]";
		}
	}
	else if (node.ref_data().m_type == node_type::File)
	{
		ss << " (size = " << std::to_string(node.ref_data().m_fileSize) << ")";
	}
	ss << std::endl;
	for (const auto& childHandle : node.peek_children_handles())
	{
		print_traverse(level + 1, ss, childHandle);
	}
}
