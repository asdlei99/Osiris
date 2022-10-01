#pragma once

#include <cstdint>

#ifdef _WIN32
#include <Windows.h>
#else
#include <SDL2/SDL.h>
#endif

#include "EventListener.h"

struct DemoPlaybackParameters;
class matrix3x4;
struct ModelRenderInfo;
struct SoundInfo;
struct UserCmd;
struct ViewSetup;

namespace csgo { enum class FrameStage; }

class GlobalContext {
public:
    bool createMoveHook(float inputSampleTime, UserCmd* cmd);
    void doPostScreenEffectsHook(void* param);
    float getViewModelFovHook();
    void drawModelExecuteHook(void* ctx, void* state, const ModelRenderInfo& info, matrix3x4* customBoneToWorld);
    bool svCheatsGetBoolHook(void* _this, std::uintptr_t returnAddress);
    void frameStageNotifyHook(csgo::FrameStage stage);
    bool shouldDrawFogHook(std::uintptr_t returnAddress);
    bool shouldDrawViewModelHook();
    void lockCursorHook();
    void setDrawColorHook(int r, int g, int b, int a, std::uintptr_t returnAddress);
    void overrideViewHook(ViewSetup* setup);
    int dispatchSoundHook(SoundInfo& soundInfo);
    void render2dEffectsPreHudHook(void* viewSetup);
    const DemoPlaybackParameters* getDemoPlaybackParametersHook(std::uintptr_t returnAddress);

#ifdef _WIN32
    LRESULT wndProcHook(HWND window, UINT msg, WPARAM wParam, LPARAM lParam);
    HRESULT presentHook(IDirect3DDevice9* device, const RECT* src, const RECT* dest, HWND windowOverride, const RGNDATA* dirtyRegion);
#else
    int pollEventHook(SDL_Event* event);
    void swapWindowHook(SDL_Window* window);
#endif

    std::optional<EventListener> gameEventListener;

private:
    void renderFrame();

    enum class State {
        NotInitialized,
        Initializing,
        Initialized
    };

    State state = State::NotInitialized;
};

inline std::optional<GlobalContext> globalContext;