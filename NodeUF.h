#ifndef WET2_NODEUF_H
#define WET2_NODEUF_H

template <typename G>
class NodeUF {
public:
    int rank; // how many players joined before me
    NodeUF* parent;
    std::shared_ptr<G> group;

    NodeUF():rank(0), parent(nullptr), group(nullptr){};

    ~NodeUF(){
        parent = nullptr;
    }

    void setGroup(std::shared_ptr<G> newGroup){
        group=newGroup;
    }

    void setParent(NodeUF* node) {
        parent=node;
    }
    NodeUF* findRoot(NodeUF* node){
        if(parent!= nullptr){
            return findRoot(parent);
        }
        return this;
    }
};


#endif //WET2_NODEUF_H
