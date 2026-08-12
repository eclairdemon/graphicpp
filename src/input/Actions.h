#pragma once

enum AppState {
    IDLE,
    DRAGGING_NODE,
    DRAWING_EDGE
};

enum class Action {
    CREATE_NODE,
    DRAG_NODE,
    START_EDGE,
    DELETE_NODE,
    CANCEL
};