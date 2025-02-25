#pragma once

#include <mcpelauncher/app_platform.h>
#include <game_window.h>

class Vec2;
class MinecraftGameWrapper;

class ClientAppPlatform : public LauncherAppPlatform {

private:
    static const char* TAG;

    std::shared_ptr<GameWindow> window;
    bool currentTextMutliline = false;
    std::string currentText;
    size_t currentTextPosition = 0;
    size_t currentTextPositionUTF = 0;
    size_t currentTextCopyPosition = 0;
    bool isShiftPressed = false;

public:
    static void** myVtable;
    static void initVtable(void* lib);

    ClientAppPlatform();

    void setWindow(std::shared_ptr<GameWindow> window) {
        this->window = std::move(window);
    }

    void hideMousePointer();
    void showMousePointer();

    void pickImage(mcpe::shared_ptr<ImagePickingCallback>);
    void pickImageOld(ImagePickingCallback& callback);
    void pickFile(mcpe::shared_ptr<FilePickerSettings> callback);
    void pickFileOld(Legacy::Pre_1_8::FilePickerSettings& callback);
    bool supportsFilePicking() { return true; }

    void setFullscreenMode(int mode);

    void swapBuffers();

    void showKeyboard(mcpe::string const& text, int, bool, bool, bool, int, Vec2 const&);
    void showKeyboardLegacy_pre_1_13(mcpe::string const& text, int, bool, bool, bool, int, Vec2 const&);
    void showKeyboardLegacy(mcpe::string const& text, int, bool, bool, bool, Vec2 const&);
    void updateTextBoxText(mcpe::string const& text);
    void hideKeyboard();
    bool isKeyboardMultiline() const { return currentTextMutliline; }

    void update();

    enum DirectionKey {
        LeftKey, RightKey, HomeKey, EndKey
    };

    void onKeyboardText(MinecraftGameWrapper& game, std::string const& text);
    void onKeyboardDirectionKey(DirectionKey key);
    void onKeyboardShiftKey(bool shiftPressed);

    void copyCurrentText();

    bool supportsClipboard() const { return true; }

    void setClipboard(mcpe::string const& text);

    bool supportsMSAA() const { return true; }

};