#ifndef __NODE_H__
#define __NODE_H__

#include <iostream>

/*
 * This is a info system for all inherited object
 *
 * */
class info_system {
    private:
    std::string info = NULL;
    
    public:
    info_system();
    info_system(const char *);
    virtual const char *get_info() const;
    virtual ~info_system();

};

class node : info_system {
    private:

    public:
};

#endif
