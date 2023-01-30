#ifndef NODE_HPP
# define NODE_HPP

# include <iostream>

#define RED 1
#define BLACK 0

template <class T>
class node {

    public:
        typedef node*   node_pointeur;
        typedef T*      data_pointeur;

        node_pointeur   parent;
        node_pointeur   left;
        node_pointeur   right;
        data_pointeur   data;
        int             color;
        node_pointeur   nil_node;

        node_pointeur   min;
        node_pointeur   max;

        node() : parent(NULL), left(NULL), right(NULL), data(NULL), color(RED), nil_node(NULL), min(NULL), max(NULL) {};
        node(const node& data) { *this = data; };
        ~node() {};

        node& operator=(const node& newdata) {
            if (this != &newdata) {
                parent = newdata.parent;
                left = newdata.left;
                right = newdata.right;
                data = newdata.data;
                color = newdata.color;
                nil_node = newdata.nil_node;
                min = newdata.min;
                max = newdata.max;
            }
            return *this;
        };
};

template<typename T>
struct tmpnode {
    int             color;
    struct tmpnode* parent;
    struct tmpnode* left;
    struct tmpnode* right;
    T              data;
};

#endif
