//
// Created by yongpu on 2020/1/11.
//

#ifndef WEBSERVER_V7_0_NOCOPYABLE_HPP
#define WEBSERVER_V7_0_NOCOPYABLE_HPP


class noncopyable {
protected:
    noncopyable() {}

    ~noncopyable() {}

private:
    noncopyable(const noncopyable &);

    const noncopyable &operator=(const noncopyable &);
};

#endif //WEBSERVER_V7_0_NOCOPYABLE_HPP
