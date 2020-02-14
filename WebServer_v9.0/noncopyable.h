//
// Created by yongpu on 2/4/20.
//

#ifndef WEBSERVER_V9_0_NONCOPYABLE_H
#define WEBSERVER_V9_0_NONCOPYABLE_H

class noncopyable
{
protected:
    noncopyable() {}
    ~noncopyable() {}
private:
    noncopyable(const noncopyable&);
    const noncopyable& operator=(const noncopyable&);
};

#endif //WEBSERVER_V9_0_NONCOPYABLE_H
