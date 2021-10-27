#include "pvz.hpp"

#include <bits/stdc++.h>

using namespace std;

template<typename T, typename U> constexpr size_t offsetOf(U T::*member)
{
    return (char*)&((T*)nullptr->*member) - (char*)nullptr;
}

int main() {
    //cout << offsetOf(&pvz::LawnApp::mBoard) << endl;
    cout << "asdf" << endl;
}
