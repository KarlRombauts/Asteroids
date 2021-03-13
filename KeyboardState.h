#ifndef UNTITLED_KEYBOARDSTATE_H
#define UNTITLED_KEYBOARDSTATE_H


#include <set>
#include <iostream>

class KeyboardState {
private:
    std::set<char> pressedKeys;
public:
    void setPressedKey(char key) {
        pressedKeys.insert(key);

        for(auto key: pressedKeys) {
            std::cout << key;
        }
        std::cout << std::endl;
    }

    bool isKeyPressed(unsigned char key) {
        return pressedKeys.find(key) != pressedKeys.end();
    }

    void releaseKey(unsigned char key) {
        pressedKeys.erase(key);

        for(auto key: pressedKeys) {
            std::cout << key;
        }
        std::cout << std::endl;
    }
};


#endif //UNTITLED_KEYBOARDSTATE_H
