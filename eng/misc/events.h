#include <vector>
#include <functional>
#include <algorithm>
#include <iostream>

template<typename Signature>
class Event;

// Partial specialization to extract return type and arguments
template<typename Ret, typename... Args>
class Event<Ret(Args...)> {
private:
    std::vector<std::function<Ret(Args...)>> handlers;

public:
    void subscribe(std::function<Ret(Args...)> handler) {
        handlers.push_back(handler);
    }

    void unsubscribe(std::function<Ret(Args...)> handler) {
        handlers.erase(
            std::remove(handlers.begin(), handlers.end(), handler),
            handlers.end()
        );
    }

    // Invoke all handlers
    void invoke(Args... args) {
        for (auto& handler : handlers) {
            handler(args...);
        }
    }

    // Operator overloads for syntactic sugar
    Event& operator+=(std::function<Ret(Args...)> handler) {
        subscribe(handler);
        return *this;
    }

    Event& operator-=(std::function<Ret(Args...)> handler) {
        unsubscribe(handler);
        return *this;
    }
    
    // Optional: Support lambdas/functors directly without explicit std::function cast
    template<typename F>
    Event& operator+=(F&& f) {
        handlers.emplace_back(std::forward<F>(f));
        return *this;
    }
};   