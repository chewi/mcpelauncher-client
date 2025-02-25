#pragma once

#include "../minecraft_game_wrapper.h"
#include <minecraft/legacy/MinecraftGame.h>
#include <minecraft/legacy/App.h>

class MinecraftGameAppWrapper_Pre_1_13 : public MinecraftGameDefaultAppWrapper {

private:
    Legacy::Pre_1_13::MinecraftGame* const game;

    static Legacy::Pre_1_13::MinecraftGame* createInstance(int argc, char** argv) {
        return (Legacy::Pre_1_13::MinecraftGame*) new MinecraftGame(argc, argv);
    }

public:
    explicit MinecraftGameAppWrapper_Pre_1_13(Legacy::Pre_1_13::MinecraftGame* game) : MinecraftGameDefaultAppWrapper(game), game(game) {}
    MinecraftGameAppWrapper_Pre_1_13(int argc, char** argv) : MinecraftGameAppWrapper_Pre_1_13(createInstance(argc, argv)) {}

    ~MinecraftGameAppWrapper_Pre_1_13() { delete game; }

    MinecraftGame* getWrapped() override { return (MinecraftGame*) game; }

    OptionsRef getPrimaryUserOptions() override {
        return ((MinecraftGame*) game)->getPrimaryUserOptions();
    }
    void setTextboxText(mcpe::string const& text, int u) override {
        ((MinecraftGame*) game)->setTextboxText(text, u);
    }
    void leaveGame() override {
        MinecraftGameDefaultWrapper::doLeaveGame((MinecraftGame*) game);
    }

};

class MinecraftGameAppWrapper_Pre_1_8 : public MinecraftGameAppWrapper_Pre_1_13 {

public:
    using MinecraftGameAppWrapper_Pre_1_13::MinecraftGameAppWrapper_Pre_1_13;

    void quit(mcpe::string const &cat, mcpe::string const &name) override {
        ((Legacy::Pre_1_8::App*) getWrapped())->quit();
    }

};

class MinecraftGameAppWrapper_Pre_1_2_10 : public MinecraftGameAppWrapper_Pre_1_8 {

public:
    using MinecraftGameAppWrapper_Pre_1_8::MinecraftGameAppWrapper_Pre_1_8;

    void setTextboxText(mcpe::string const &text, int u) override {
        ((Legacy::Pre_1_2_10::MinecraftGame*) getWrapped())->setTextboxText(text);
    }

};

class MinecraftGameAppWrapper_Pre_1_2 : public MinecraftGameAppWrapper_Pre_1_2_10 {

public:
    using MinecraftGameAppWrapper_Pre_1_2_10::MinecraftGameAppWrapper_Pre_1_2_10;

    OptionsRef getPrimaryUserOptions() override {
        return ((Legacy::Pre_1_2::MinecraftGame*) getWrapped())->getOptions();
    }

};

class MinecraftGameAppWrapper_Pre_1_1 : public MinecraftGameDefaultAppWrapper {

private:
    using MinecraftClient = Legacy::Pre_1_1::MinecraftClient;

    MinecraftClient* const game;

    static MinecraftClient* createInstance(int argc, char** argv) {
        return new MinecraftClient(argc, argv);
    }

public:
    explicit MinecraftGameAppWrapper_Pre_1_1(MinecraftClient* game) : MinecraftGameDefaultAppWrapper(game), game(game) {}
    MinecraftGameAppWrapper_Pre_1_1(int argc, char** argv) : MinecraftGameAppWrapper_Pre_1_1(createInstance(argc, argv)) {}

    ~MinecraftGameAppWrapper_Pre_1_1() { delete game; }

    void quit(mcpe::string const &cat, mcpe::string const &name) override {
        ((Legacy::Pre_1_8::App*) getWrapped())->quit();
    }

    MinecraftGame* getWrapped() override { return (MinecraftGame*) game; }

    OptionsRef getPrimaryUserOptions() override {
        return game->getOptions();
    }
    void setTextboxText(mcpe::string const& text, int u) override {
        game->setTextboxText(text);
    }

    void leaveGame() override {}

};

class MinecraftGameAppWrapper_Pre_0_14_2 : public MinecraftGameAppWrapper_Pre_1_1 {

public:
    using MinecraftGameAppWrapper_Pre_1_1::MinecraftGameAppWrapper_Pre_1_1;

    void setRenderingSize(int w, int h) override {
    }

    void setUISizeAndScale(int w, int h, float s) override {
        ((Legacy::Pre_0_15::App*) getWrapped())->setSize(w, h, s);
    }
};
