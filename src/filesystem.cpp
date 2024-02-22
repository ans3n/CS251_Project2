#include "filesystem.hpp"

#include <iostream>

using namespace cs251;

filesystem::filesystem(const size_t sizeLimit)
{
    m_sizeLimit = sizeLimit;
    m_currentSize = 0;
}

handle filesystem::create_file(const size_t fileSize, const std::string& fileName)
{
	/*Exceptions*/
    //If the parentHandle doesn’t exist or isn’t a directory, throw invalid_handle.
    if (!exist(0)) {
        throw invalid_handle();
    }

    if (fileName.find('/') != -1) {
        throw invalid_name();
    }

    if (m_currentSize + fileSize > m_sizeLimit) {
        throw exceeds_size();
    }

    auto& childrens = m_fileSystemNodes.ref_node(0).peek_children_handles();
    for (int i = 0; i < childrens.size(); i++) {
        if (fileName.compare(m_fileSystemNodes.ref_node(childrens[i]).ref_data().m_name) == 0) {
            throw file_exists();
        }
    }

    //create a file as a child of the directory pointed to by the root directory
    handle newFile_handle = m_fileSystemNodes.allocate(0);
    auto& createdNode = m_fileSystemNodes.ref_node(newFile_handle);
    createdNode.ref_data().m_type = node_type::File;
    createdNode.ref_data().m_name = fileName;
    m_currentSize++;

    return newFile_handle;
}

handle filesystem::create_directory(const std::string& directoryName)
{
    /*Exceptions*/
    //If the parentHandle doesn’t exist or isn’t a directory, throw invalid_handle.
    if (!exist(0)) {
        throw invalid_handle();
    }

    if (directoryName.find('/') != -1) {
        throw invalid_name();
    }

    //If an object with the same name already exists in the directory, throw directory_exists
    //  code: run a loop through entire directory and compare each element, if found throw
    auto& childrens = m_fileSystemNodes.ref_node(0).peek_children_handles();
    for (int i = 0; i < childrens.size(); i++) {
        if (directoryName.compare(m_fileSystemNodes.ref_node(childrens[i]).ref_data().m_name) == 0) {                 //check if using get_name() is right
            throw directory_exists();
        }
    }

    //Create a new directory as a child of the directory pointed to by the root directory
    //Instantiate the directory with the given name
    handle newDirectory_handle = m_fileSystemNodes.allocate(0);
    auto& createdDirectory = m_fileSystemNodes.ref_node(newDirectory_handle);
    createdDirectory.ref_data().m_type = node_type::Directory;
    createdDirectory.ref_data().m_name = directoryName;

    return newDirectory_handle;
}

handle filesystem::create_link(const handle targetHandle, const std::string& linkName)
{
    /*Exceptions*/
    //If the parentHandle doesn’t exist or isn’t a directory, throw invalid_handle.
    if (!exist(0) || !exist(targetHandle)) {
        throw invalid_handle();
    }

    //If the parentHandle isn’t a directory, throw invalid_handle.
    // code: if parentHandle isn't in the directory list - need to check if recycled?

    //If the linkName contains a ‘/’ character, throw invalid_name.
    if (linkName.find("/") != -1) {
        throw invalid_name();
    }

    //If an object with the same name already exists in the directory, throw link_exists
    auto& childrens = m_fileSystemNodes.ref_node(0).peek_children_handles();
    for (int i = 0; i < childrens.size(); i++) {
        if (linkName.compare(m_fileSystemNodes.ref_node(childrens[i]).ref_data().m_name) == 0) {
            throw link_exists();
        }
    }

    //Create a new link as a child of the directory pointed to by the root directory
    //Instantiate the link with the given name and have it point to targetHandle
    handle newLink_handle = m_fileSystemNodes.allocate(0);
    auto& createdLink = m_fileSystemNodes.ref_node(newLink_handle);
    createdLink.ref_data().m_type = node_type::Link;
    createdLink.ref_data().m_name = linkName;
    createdLink.ref_data().m_linkedHandle = targetHandle;

    return newLink_handle;
}

bool filesystem::remove(const handle targetHandle)
{
	// If the targetHandle doesn’t exist, throw invalid_handle
    if (!exist(targetHandle)) {
        throw invalid_handle();
    }

    bool removed = false;

    if (m_fileSystemNodes.ref_node(targetHandle).ref_data().m_type == node_type::Directory) {
        if (m_fileSystemNodes.ref_node(targetHandle).peek_children_handles().empty()) {
            m_fileSystemNodes.remove(targetHandle);
            removed = true;
        }
    } else if (m_fileSystemNodes.ref_node(targetHandle).ref_data().m_type == node_type::Link) {
        m_fileSystemNodes.remove(m_fileSystemNodes.ref_node(targetHandle).ref_data().m_linkedHandle);
        removed = true;
    } else {
        //file
        m_fileSystemNodes.remove(targetHandle);
        m_currentSize--;
        removed = true;
    }

    return removed;
}

handle filesystem::create_file(const size_t fileSize, const std::string& fileName, const handle parentHandle)
{
    /*Exceptions*/
    //If the parentHandle doesn’t exist or isn’t a directory, throw invalid_handle.
    if (!exist(parentHandle)) {
        throw invalid_handle();
    }

    if (fileName.find('/') != -1) {
        throw invalid_name();
    }

    if (m_currentSize + fileSize > m_sizeLimit) {
        throw exceeds_size();
    }

    auto& childrens = m_fileSystemNodes.ref_node(parentHandle).peek_children_handles();
    for (int i = 0; i < childrens.size(); i++) {
        if (fileName.compare(m_fileSystemNodes.ref_node(childrens[i]).ref_data().m_name) == 0) {        //check if using get_name() is right
            throw file_exists();
        }
    }

    //create a file as a child of the directory pointed to by the root directory
    handle newFile_handle = m_fileSystemNodes.allocate(parentHandle);
    auto& createdNode = m_fileSystemNodes.ref_node(newFile_handle);
    createdNode.ref_data().m_type = node_type::File;
    createdNode.ref_data().m_name = fileName;
    m_currentSize++;

    return newFile_handle;
}

handle filesystem::create_directory(const std::string& directoryName, const handle parentHandle)
{
    /*Exceptions*/
    //If the parentHandle doesn’t exist or isn’t a directory, throw invalid_handle.
    if (!exist(parentHandle)) {
        throw invalid_handle();
    }

    if (directoryName.find('/') != -1) {
        throw invalid_name();
    }

    //If an object with the same name already exists in the directory, throw directory_exists
    //  code: run a loop through entire directory and compare each element, if found throw
    auto& childrens = m_fileSystemNodes.ref_node(parentHandle).peek_children_handles();
    for (int i = 0; i < childrens.size(); i++) {
        if (directoryName.compare(m_fileSystemNodes.ref_node(childrens[i]).ref_data().m_name) == 0) {                 //check if using get_name() is right
            throw directory_exists();
        }
    }

    //Create a new directory as a child of the directory pointed to by the root directory
    //Instantiate the directory with the given name
    handle newDirectory_handle = m_fileSystemNodes.allocate(parentHandle);
    auto& createdDirectory = m_fileSystemNodes.ref_node(newDirectory_handle);
    createdDirectory.ref_data().m_type = node_type::Directory;
    createdDirectory.ref_data().m_name = directoryName;

    return newDirectory_handle;
}

handle filesystem::create_link(const handle targetHandle, const std::string& linkName, const handle parentHandle)
{
    /*Exceptions*/
    //If the parentHandle doesn’t exist or isn’t a directory, throw invalid_handle.
    if (!exist(targetHandle) || !exist(parentHandle)) {
        throw invalid_handle();
    }

    //If the linkName contains a ‘/’ character, throw invalid_name.
    if (linkName.find("/") != -1) {
        throw invalid_name();
    }

    //If an object with the same name already exists in the directory, throw link_exists
    auto& childrens = m_fileSystemNodes.ref_node(parentHandle).peek_children_handles();
    for (int i = 0; i < childrens.size(); i++) {
        if (linkName.compare(m_fileSystemNodes.ref_node(childrens[i]).ref_data().m_name) == 0) {
            throw link_exists();
        }
    }

    //Create a new link as a child of the directory pointed to by the root directory
    //Instantiate the link with the given name and have it point to targetHandle
    handle newLink_handle = m_fileSystemNodes.allocate(parentHandle);
    auto& createdLink = m_fileSystemNodes.ref_node(newLink_handle);
    createdLink.ref_data().m_type = node_type::Link;
    createdLink.ref_data().m_name = linkName;
    createdLink.ref_data().m_linkedHandle = targetHandle;

    return newLink_handle;
}

std::string filesystem::get_absolute_path(const handle targetHandle)
{
    //If the targetHandle doesn’t exist, throw invalid_handle
    if (!exist(targetHandle)) {
        throw invalid_handle();
    }

    std::string absolutePath = "";
    handle currentHandle = targetHandle;

    while (currentHandle > 0) {
        absolutePath = "/" + m_fileSystemNodes.ref_node(currentHandle).ref_data().m_name + absolutePath;
        currentHandle = m_fileSystemNodes.ref_node(currentHandle).get_parent_handle();
    }

    return absolutePath;
}

std::string filesystem::get_name(const handle targetHandle)
{
    //If the targetHandle doesn’t exist, throw invalid_handle.
    if (!exist(targetHandle)) {
        throw invalid_handle();
    }

    return m_fileSystemNodes.ref_node(targetHandle).ref_data().m_name;
}

void filesystem::rename(const handle targetHandle, const std::string& newName)
{
	//If the targetHandle doesn’t exist, throw invalid_handle.
    if (!exist(targetHandle)) {
        throw invalid_handle();
    }

    if (newName.find("/") != -1) {
        throw invalid_name();
    }

    //If a file/directory/symlink with newName already exists, throw name_exists
    auto& childrens = m_fileSystemNodes.ref_node(targetHandle).peek_children_handles();
    for (int i = 0; i < childrens.size(); i++) {
        if (newName.compare(m_fileSystemNodes.ref_node(childrens[i]).ref_data().m_name) == 0) {
            throw name_exists();
        }
    }

    //Rename the file/directory/symlink referred to by targetHandle to newName
    m_fileSystemNodes.ref_node(targetHandle).ref_data().m_name = newName;
}

bool filesystem::exist(const handle targetHandle)
{
    bool found = false;

    try {
        found = m_fileSystemNodes.ref_node(targetHandle).is_recycled();
    } catch (invalid_handle()) {
        return false;
    }

    return found;
}

handle filesystem::get_handle(const std::string& absolutePath)
{
    std::vector<std::string> pathElements;
    size_t start = 1;
    size_t slashLocation = absolutePath.find("/", 1);
    while (slashLocation != std::string::npos) {
        pathElements.push_back(absolutePath.substr(start, slashLocation - 1));
        start = slashLocation + 1;
        slashLocation = absolutePath.find("/", start);
    }
    pathElements.push_back(absolutePath.substr(start, absolutePath.length() - 1));

    handle current = 0;
    bool found = false;
    auto& rootChildrens = m_fileSystemNodes.ref_node(current).peek_children_handles();
    for (int i = 0; i < rootChildrens.size(); i++) {
        if (m_fileSystemNodes.ref_node(rootChildrens[i]).ref_data().m_name == pathElements[0]) {
            current = rootChildrens[i];
            found = true;
            break;
        }
    }

    if (pathElements.size() == 1) {
        return current;
    }
    if (!found) {
        throw invalid_path();
    }

    for (int i = 1; i < pathElements.size() - 1; i++) {
        found = false;

        if (m_fileSystemNodes.ref_node(current).ref_data().m_type == node_type::Link) {
            current = follow(current);
        }

        auto& childrens = m_fileSystemNodes.ref_node(current).peek_children_handles();

        //find the next thing in the current thing
        for (int j = 0; j < childrens.size(); j++) {
            if (m_fileSystemNodes.ref_node(childrens[j]).ref_data().m_name == pathElements[i]) {
                current = childrens[j];
                found = true;
                break;
            }
        }
        //found the last thing
        if (i == pathElements.size() - 1) {
            return current;
        }

        if (!found) {
            throw invalid_path();
        }
    }
}

handle filesystem::follow(const handle targetHandle)
{
    //If the targetHandle doesn’t exist, throw invalid_handle.
    if (!exist(targetHandle)) {
        throw invalid_handle();
    }

    if (m_fileSystemNodes.ref_node(targetHandle).ref_data().m_type == node_type::Link) {
        follow(m_fileSystemNodes.ref_node(targetHandle).ref_data().m_linkedHandle);
    }

    return m_fileSystemNodes.ref_node(targetHandle).get_handle();
}

handle filesystem::get_largest_file_handle() const
{
	//TODO: Remove following line and add your implementation here.
  throw std::logic_error("filesystem::" + std::string(__FUNCTION__) + " not implemented");
}

size_t filesystem::get_available_size() const
{
    return m_sizeLimit - m_currentSize;
}

size_t filesystem::get_file_size(const handle targetHandle)
{
	if (!exist(targetHandle)) {
        throw invalid_handle();
    }

    if (m_fileSystemNodes.ref_node(targetHandle).ref_data().m_type == node_type::Link) {
        get_file_size(m_fileSystemNodes.ref_node(targetHandle).ref_data().m_linkedHandle);
    }

    if (m_fileSystemNodes.ref_node(targetHandle).ref_data().m_type != node_type::File) {
        throw invalid_handle();
    }

    return m_fileSystemNodes.ref_node(targetHandle).ref_data().m_fileSize;
}

size_t filesystem::get_file_size(const std::string& absolutePath)
{
    if (!exist(get_handle(absolutePath))) {
        throw invalid_path();
    }

    if (m_fileSystemNodes.ref_node(get_handle(absolutePath)).ref_data().m_type == node_type::Link) {
        get_file_size(get_absolute_path(m_fileSystemNodes.ref_node(get_handle(absolutePath)).ref_data().m_linkedHandle));
    }

    if (m_fileSystemNodes.ref_node(get_handle(absolutePath)).ref_data().m_type != node_type::File) {
        throw invalid_handle();
    }

    return m_fileSystemNodes.ref_node(get_handle(absolutePath)).ref_data().m_fileSize;
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
