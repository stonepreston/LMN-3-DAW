#pragma once
#include <juce_gui_extra/juce_gui_extra.h>
#include "Themes.h"
#include "SettingsContentComponent.h"
class SettingsView : public juce::Component,
                     public juce::ApplicationCommandTarget
{
public:
    SettingsView(juce::AudioDeviceManager& deviceManager, Themes& themes);

    void paint(juce::Graphics&) override;
    void resized() override;

    ApplicationCommandTarget* getNextCommandTarget() override;
    void getAllCommands(juce::Array<juce::CommandID>& commands) override;
    void getCommandInfo (juce::CommandID commandID, juce::ApplicationCommandInfo& result) override;
    bool perform (const InvocationInfo &info) override;
    
private:
    Themes& themes;
    juce::ApplicationCommandManager commandManager;

    juce::Viewport settingsViewport;
    SettingsContentComponent settingsContentComponent;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SettingsView)
};
