#include <iostream>
#include <cassert>

#include "nodeTest.h"

void NodeTest::test() {
        // Create a root node with a name and initial transformation matrix (identity matrix)
        Node root_node("RootNode", glm::mat4(1.0f));

        // Test the object name
        std::cout << "\tTesting Object Name..." << std::endl;
        assert(root_node.get_object_name() == "RootNode");
        root_node.set_object_name("UpdatedRootNode");
        assert(root_node.get_object_name() == "UpdatedRootNode");

        // Test the object ID
        std::cout << "\tTesting Object ID..." << std::endl;
        unsigned int root_id = root_node.get_object_id();
        assert(root_id == 2); // The first object now gets ID 2 as per the updated logic

        // Create a child node with a different transformation matrix
        Node child_node("ChildNode", glm::mat4(2.0f));
        assert(child_node.get_object_name() == "ChildNode");

        // Add the child node to the root node
        root_node.add_child(&child_node);
        assert(root_node.get_number_of_chilren() == 1);

        // Test if child is added correctly by finding it by name and ID
        std::cout << "\tTesting Find By Name..." << std::endl;
        std::vector<Node*> children_by_name = root_node.find_by_name("ChildNode");
        assert(children_by_name.size() == 1);
        assert(children_by_name[0]->get_object_name() == "ChildNode");

        std::cout << "\tTesting Find By ID..." << std::endl;
        Node* found_node = root_node.find_by_id(child_node.get_object_id());
        assert(found_node != nullptr);
        assert(found_node->get_object_name() == "ChildNode");

        // Remove the child node and verify it's no longer in the children list
        std::cout << "\tTesting Remove Child..." << std::endl;
        root_node.remove_child(&child_node);
        assert(root_node.get_number_of_chilren() == 0);


    }
