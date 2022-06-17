//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : Zac Gonzalez
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description :
//============================================================================

#include <iostream>
#include <time.h>
#include <vector>

#include "CSVparser.hpp"

using namespace std;

    //============================================================================
    // Global definitions visible to all methods and classes
    //============================================================================


// Forward Declarations
    double strToDouble(std::string str, char ch);

    // Define a Structure to Hold Bid Information
    struct Bid {
        std::string bidId;
        std::string title;
        std::string fund;
        double amount;
        Bid() {
            amount = 0.0;
        }
    };

    // Internal Structure for Tree Node
    struct Node {
        Bid bid;
        Node* left;
        Node* right;


        // Default Constructor
        Node() {
            left = nullptr;
            right = nullptr;
        }

        // Initialize with a Given Bid
        Node(Bid aBid) : Node() {
            this->bid = aBid;

        }
    };

    //============================================================================
    // Binary Search Tree class definition
    //============================================================================

    /**
     * Define a Class Containing Data Members and Methods to
     * Implement a Binary Search Tree
     */
    class BinarySearchTree {

    private:
        Node* root;

        void addNode(Node* node, Bid bid);
        void inOrder(Node* node);
        Node* removeNode(Node* node, std::string bidId);

    public:
        BinarySearchTree();
        virtual ~BinarySearchTree();
        void InOrder();
        void Insert(Bid bid);
        void Remove(std::string bidId);
        Bid Search(std::string bidId);
    };

    /**
     * Default Constructor
     */
    BinarySearchTree::BinarySearchTree() {
        // Initialize Housekeeping Variables
        root = nullptr;
    }

    /**
     * Destructor
     */
    BinarySearchTree::~BinarySearchTree() {
        // Recurse From Root Deleting Every Node
    }

    /**
     * Traverse the Tree in Order
     */
    void BinarySearchTree::InOrder() {
        this->inOrder(root);

    }
    /**
     * Insert a Bid
     */
    void BinarySearchTree::Insert(Bid bid) {
        // Implement Inserting a Bid Into the Tree
        if (root == nullptr) {
            root = new Node(bid);
        }
        else {
            //If Root Isn't Null Then Adds The Bid to the Tree
            this->addNode(root, bid);
        }
    }

    /**
     * Remove a Bid
     */
    void BinarySearchTree::Remove(std::string bidId) {
        // Implement Removing a Bid From the Tree
        this->removeNode(root, bidId);


    }

    /**
     * Search For a Bid
     */
    Bid BinarySearchTree::Search(std::string bidId) {
        // Implement Searching the Tree For a Bid
        // Start Searching From the Root
        Node* current = root;

        // Keep Looping Downwards Until Bottom Reached or Bid is Found
        while (current != nullptr) {
            // If Current Node Matches, Return it
            if (current->bid.bidId.compare(bidId) == 0) {
                return current->bid;
            }
            // If Bid is Smaller Than Current Then Traverse Left
            if (bidId.compare(current->bid.bidId) < 0) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }

        // If While Loop is Exited Without Finding a Match, an Empty Bid is Created and Returned
        Bid bid;
        return bid;
    }

    /**
     * Add a Bid to Some Node (Recursive)
     *
     * @param Node Current Node in Tree
     * @param Bid Bid to be Added
     */

    void BinarySearchTree::addNode(Node* node, Bid bid) {
        // Implement Inserting a Bid Into the Tree
        // If Node is Larger Than the Bid, Add to Left Subtree
        if (node->bid.bidId.compare(bid.bidId) > 0) {
            if (node->left == nullptr) {
                // If Left Node is Null Then it Adds the New Node Here
                node->left = new Node(bid);
            }
            else {
                // Recursively Calls Addnode Until Bottom is Reached
                this->addNode(node->left, bid);
            }
        }
        // Add to Right Subtree
        else {
            if (node->right == nullptr) {
                // If Right Node is Null Then it Adds the New Node Here
                node->right = new Node(bid);
            }
            else {
                // Recursively Calls Addnode Until Bottom is Reached
                this->addNode(node->right, bid);
            }
        }
    }


    // Displays Bids in Order
    void BinarySearchTree::inOrder(Node* node) {
        if (node != nullptr) {
            inOrder(node->left);
            std::cout << node->bid.bidId
                << ": "
                << node->bid.title << " | "
                << node->bid.amount << " | "
                << node->bid.fund << std::endl;
            inOrder(node->right);
        }
    }

    Node* BinarySearchTree::removeNode(Node* node, std::string bidId) {
        // If This Node is Null Then Return (Avoid Crash)
        if (node == nullptr) {
            return node;
        }

        // Recurse Down Left Subtree
        if (bidId.compare(node->bid.bidId) < 0) {
            node->left = removeNode(node->left, bidId);
        }
        else if (bidId.compare(node->bid.bidId) > 0) {
            node->right = removeNode(node->right, bidId);
        }
        else {
            // No Children as This is a Leaf Node
            if ((node->left == nullptr) && (node->right == nullptr)) {
                delete node;
                node = nullptr;
            }
            // One Child to the Left
            else if ((node->left != nullptr) && (node->right == nullptr)) {
                Node* temp = node;
                node = node->left;
                delete temp;
            }
            // One Child to the Right
            else if ((node->left == nullptr) && (node->right != nullptr)) {
                Node* temp = node;
                node = node->right;
                delete temp;
            }
            // Two Children
            else {
                Node* temp = node;
                node = node->right;
                while (temp->left != nullptr) {
                    temp = temp->left;

                }
                node->bid = temp->bid;
                node->right = removeNode(node->right, temp->bid.bidId);

            }
        }
        return node;
    }

    //============================================================================
    // Static Methods Used for Testing
    //============================================================================

    /**
     * Display the Bid Information to the Console (std::out)
     *
     * @param Bid Struct Containing the Bid Info
     */

    void displayBid(Bid bid) {
        std::cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
            << bid.fund << std::endl;
        return;
    }

    /**
     * Load a CSV File Containing Bids Into a Container
     *
     * @param csvPath The Path to the CSV File to Load
     * @return a Container Holding all the Bids Read
     */
    void loadBids(std::string csvPath, BinarySearchTree* bst) {
        std::cout << "Loading CSV file " << csvPath << std::endl;

            // Initialize the CSV Parser Using the Given Path
            csv::Parser file = csv::Parser(csvPath);
    
        // Read and Display Header Row - Optional
        std::vector<std::string> header = file.getHeader();
        for (auto const& c : header) {
            std::cout << c << " | ";
        }
        std::cout << "" << std::endl;

        try {
            // Loop to Read Rows of a CSV File
            for (unsigned int i = 0; i < file.rowCount(); i++) {

                // Create a Data Structure and Add to the Collection of Bids
                Bid bid;
                bid.bidId = file[i][1];
                bid.title = file[i][0];
                bid.fund = file[i][8];
                bid.amount = strToDouble(file[i][4], '$');

                //std::cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << std::endl;

                // Push this Bid to the End
                bst->Insert(bid);
            }
        }
        catch (csv::Error& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    /**
     * Simple C Function to Convert a String to a Double
     * After Stripping Out Unwanted Char
     *
     * credit: http://stackoverflow.com/a/24875936
     *
     * @param ch The Character to Strip Out
     */
    double strToDouble(std::string str, char ch) {
        str.erase(remove(str.begin(), str.end(), ch), str.end());
        return atof(str.c_str());
    }

    /**
     *  main() Method
     */
    int main(int argc, char* argv[]) {

        // Process Command Line Arguments
        std::string csvPath, bidKey;
        switch (argc) {
        case 2:
            csvPath = argv[1];
            bidKey = "98109";
            break;
        case 3:
            csvPath = argv[1];
            bidKey = argv[2];
            break;
        default:
            csvPath = "C:\Binary Search Tree\BinarySearchTree\eBid_Monthly_Sales.csv";
            bidKey = "98109";
        }

        // Define a Timer Variable
        clock_t ticks;

        // Define a Binary Search Tree to Hold All Bids
        BinarySearchTree* bst = new BinarySearchTree();

        Bid bid;

        int choice = 0;
        while (choice != 5) {
            std::cout << "Menu:" << std::endl;
            std::cout << "  1. Load Bids" << std::endl;
            std::cout << "  2. Display All Bids" << std::endl;
            std::cout << "  3. Find Bid" << std::endl;
            std::cout << "  4. Remove Bid" << std::endl;
            std::cout << "  5. Exit" << std::endl;
            std::cout << "Enter choice: ";
            std::cin >> choice;

            switch (choice) {

            case 1:
                bst = new BinarySearchTree();

                // Initialize a Timer Variable Before Loading Bids
                ticks = clock();

                // Complete the Method Call to Load the Bids
                loadBids(csvPath, bst);

                //cout << bst->Size() << " bids read" << endl;

                // Calculate Elapsed Time and Display Result
                ticks = clock() - ticks; // Current Clock Ticks Minus Starting Clock Ticks
                std::cout << "time: " << ticks << " clock ticks" << std::endl;
                std::cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << std::endl;
                break;

            case 2:
                bst->InOrder();
                break;

            case 3:
                ticks = clock();

                bid = bst->Search(bidKey);

                ticks = clock() - ticks; // Current Clock Ticks Minus Starting Clock Ticks

                if (!bid.bidId.empty()) {
                    displayBid(bid);
                }
                else {
                    std::cout << "Bid Id " << bidKey << " not found." << std::endl;
                }

                std::cout << "time: " << ticks << " clock ticks" << std::endl;
                std::cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << std::endl;

                break;

            case 4:
                bst->Remove(bidKey);
                break;
            }
        }

        std::cout << "Good bye." << std::endl;

        return 0;
    }
