#pragma once
#include <raylib.h>
#include <unordered_map>
#include <iostream>
#include <cassert>

#include "Actions.h"

struct Chord {
    int key = KEY_NULL;
    int mouse_button = -1;
    bool shift = 0;
    bool ctrl = 0;
    bool alt = 0;
};

class InputManager {
private:
    std::unordered_map<Action, Chord> binds;

    bool matchMods(const Chord& chord) const {
        bool s = !chord.shift or (IsKeyDown(KEY_LEFT_SHIFT) or IsKeyDown(KEY_RIGHT_SHIFT));
        bool c = !chord.ctrl or (IsKeyDown(KEY_LEFT_CONTROL) or IsKeyDown(KEY_RIGHT_CONTROL));
        bool a = !chord.alt or (IsKeyDown(KEY_LEFT_ALT) or IsKeyDown(KEY_RIGHT_ALT));
        return s and c and a;
    }

public:
    InputManager() {
        binds[Action::CREATE_NODE] = { KEY_NULL, MOUSE_BUTTON_LEFT, 0,0,0};
        binds[Action::DRAG_NODE]   = { KEY_NULL, MOUSE_BUTTON_LEFT, 0,1,0};
        binds[Action::START_EDGE]  = { KEY_NULL, MOUSE_BUTTON_LEFT, 0,0,0};
        binds[Action::DELETE_NODE] = { KEY_NULL, MOUSE_BUTTON_RIGHT, 0,0,0};
    }

    /**
     * @brief Set a keybind
     * 
     * @param action The action corresponding to the keybind
     * @param chord The chord of the keybind
     */
    void setBinding(Action action, Chord chord) {
        binds[action] = chord;
    }


    /**
     * @brief Check if an action was PRESSED this frame.
     */
    bool isActionPressed(Action action) const {
        auto it = binds.find(action);
        assert(it != binds.end());

        const auto& chord = it->second;
        if(!matchMods(chord)) return false;
        if(chord.mouse_button != -1 and IsMouseButtonPressed(chord.mouse_button)) return 1;
        if(chord.key != KEY_NULL and IsKeyPressed(chord.key)) return true;

        return false;
    }


    /**
     * @brief Check if an action is HELD DOWN
     */
    bool isActionDown(Action action) const {
        auto it = binds.find(action);
        assert(it != binds.end());

        const auto& chord = it->second;
        if(!matchMods(chord)) return false;
        if(chord.mouse_button != -1 and IsMouseButtonDown(chord.mouse_button)) return 1;
        if(chord.key != KEY_NULL and IsKeyDown(chord.key)) return true;

        return false;
    }

    
    /**
     * @brief Check if an action is RELEASED this frame.
     */
    bool isActionReleased(Action action) const {
        auto it = binds.find(action);
        assert(it != binds.end());

        const auto& chord = it->second;
        if(!matchMods(chord)) return false;
        if(chord.mouse_button != -1 and IsMouseButtonReleased(chord.mouse_button)) return 1;
        if(chord.key != KEY_NULL and IsKeyReleased(chord.key)) return true;

        return false;
    }
};