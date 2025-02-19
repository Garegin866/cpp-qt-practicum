#pragma once

#include <deque>

template<class T, class Comp>
std::deque<T> Merge(const std::deque<T>& half1, const std::deque<T>& half2, const Comp& comparator) {
    std::deque<T> result;
    int i = 0;
    int j = 0;

    while (i < half1.size() && j < half2.size()) {
        if (comparator(half1[i], half2[j])) {
            result.push_back(half1[i++]);
        } else {
            result.push_back(half2[j++]);
        }
    }

    while (i < half1.size()) {
        result.push_back(half1[i++]);
    }

    while (j < half2.size()) {
        result.push_back(half2[j++]);
    }

    return result;
}

template<class T, class Comp>
std::deque<T> MergeSort(const std::deque<T>& src, const Comp& comparator) {
    if (src.size() <= 1) {
        return src;
    }

    int mid = src.size() / 2;

    std::deque<T> half1(src.begin(), src.begin() + mid);
    std::deque<T> half2(src.begin() + mid, src.end());

    half1 = MergeSort(half1, comparator);
    half2 = MergeSort(half2, comparator);

    return Merge(half1, half2, comparator);
}
