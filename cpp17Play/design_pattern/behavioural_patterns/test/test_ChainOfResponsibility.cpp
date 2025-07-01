#include <functional>
#include <string>
#include <utility>
#include <vector>

#include <gtest/gtest.h>

#include "../ChainOfResponsibility.hpp"


using namespace cpp17Play;

class HelpRequest {
public:
    std::string helpMessage;
};

class AbstractComponentWidget : public AbstractHandler<HelpRequest> {
    std::string _text;
    AbstractHandler<HelpRequest>* _container{nullptr};

public:
    explicit AbstractComponentWidget(const std::string& text) : _text(text) {}

    void showText() {}

    void handle(HelpRequest& request) override {
        if (_container != nullptr) {
            _container->handle(request);
        } else {
            showText();
        }
    }

    void setNext(AbstractHandler<HelpRequest>& handler) override {
        _container = &handler;
    }
};

class ComponentWidget : public AbstractComponentWidget {
    std::vector<AbstractComponentWidget> _children;

public:
    ComponentWidget() : AbstractComponentWidget("Component") {
        _children.clear();
    }

    void add(AbstractComponentWidget&& child) {
        _children.emplace_back(std::move(child));
    }
};

class ButtonWidget : public ComponentWidget {
public:
    void showButtonHelp(std::string& helpText) {
        helpText += "/Button";
    }

    void handle(HelpRequest& request) override {
        showButtonHelp(request.helpMessage);
    }
};

class ContainerWidget : public ComponentWidget {
    int _data;
public:
    void showContainerHelp(std::string& helpText) {
        helpText += "/Panel";
    }

    void handle(HelpRequest& request) override {
        showContainerHelp(request.helpMessage);
        ComponentWidget::handle(request);
    }
};

class WindowWidget : public ComponentWidget {
    std::string _windowTitle;

public:
    explicit WindowWidget(const std::string& title = "Window Title") : _windowTitle(title) {}

    void showWindowHelp(std::string& helpText) {
        helpText += "/Window";
    }

    void handle(HelpRequest& request) override {
        showWindowHelp(request.helpMessage);
        ComponentWidget::handle(request);
    }
};

TEST(ChainOfResponsibilityTest, GIVEN_ChainOfResponsibilityMockWidgets_WHEN_HandlingRequest_THEN_Successfully_Spread_Responsibilities) {
    HelpRequest helpRequest;
    helpRequest.helpMessage = "HELP";

    WindowWidget window;
    ContainerWidget container;
    ButtonWidget button;

    container.setNext(button);
    container.add(std::move(button));

    window.setNext(container);
    window.add(std::move(container));

    window.handle(helpRequest);
    EXPECT_EQ(helpRequest.helpMessage, "HELP/Window/Panel/Button");
}
