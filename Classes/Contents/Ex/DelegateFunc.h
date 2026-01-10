#pragma once
#include <vector>
#include <functional>
#include <iostream>

// 가변 인자를 받는 Action 템플릿 클래스
template <typename T, typename... Args>
class DelegateFunc {
public:
    // 콜백 추가
    void addCallback(std::function<T(Args...)> callback) {
        callbacks.push_back(callback);
    }

    // 콜백 제거 (콜백 함수 자체로 제거)
    void removeCallback(std::function<T(Args...)> callbackToRemove) {
        // 콜백 리스트에서 제거할 콜백을 찾아 제거
        callbacks.erase(
            std::remove_if(callbacks.begin(), callbacks.end(),
                [&callbackToRemove](const std::function<bool(Args...)>& callback) {
                    // 콜백을 비교할 수 없으므로 target_type()으로 비교
                    return callback.target_type() == callbackToRemove.target_type();
                }),
            callbacks.end());
    }

    // 인자가 있는 경우의 invoke
    template <typename... CallArgs>
    typename std::enable_if<(sizeof...(CallArgs) > 0)>::type invoke(CallArgs... args) {
        for (auto& callback : callbacks) {
            if (callback) {
                callback(args...);  // 가변 인자를 사용하여 콜백 호출
            }
        }
    }

    // 인자가 없는 경우의 invoke
    template <typename... CallArgs = Args>
    typename std::enable_if<(sizeof...(CallArgs) == 0)>::type invoke() {
        for (auto& callback : callbacks) {
            if (callback) {
                callback();  // 인자 없이 콜백 호출
            }
        }
    }

    //// 모든 콜백 호출
    //void invoke(Args... args) {
    //    for (auto& callback : callbacks) {
    //        if (callback) {
    //            callback(args...);  // 가변 인자를 사용하여 콜백 호출
    //        }
    //    }
    //}

private:
    std::vector<std::function<T(Args...)>> callbacks;  // 콜백 리스트
};