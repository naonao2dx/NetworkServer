//
// Created by Nao on 2018/03/04.
//

#ifndef WEBSERVER_SINGLETON_H
#define WEBSERVER_SINGLETON_H


#include <memory>

template <typename T> class Singleton {
protected:
    Singleton() {};

public:
    virtual ~Singleton() {};

    Singleton(Singleton const&) = delete;
    Singleton& operator=(Singleton const&) = delete;

public:
    static std::shared_ptr<T> getInstance() {
        auto retPtr = pInstance.lock();
        if (!retPtr) {
            retPtr = std::shared_ptr<T>(new T{});
            pInstance = std::weak_ptr<T>(retPtr);
            return retPtr;
        }
        return pInstance.lock();
    }

private:
    static std::weak_ptr<T> pInstance;
};

template <typename T> std::weak_ptr<T> Singleton<T>::pInstance;

#endif //WEBSERVER_SINGLETON_H
