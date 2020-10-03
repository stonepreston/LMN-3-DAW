#include "AvailablePluginParametersListView.h"
#include <app_navigation/app_navigation.h>
#include "ModifierView.h"
AvailablePluginParametersListView::AvailablePluginParametersListView(tracktion_engine::AudioTrack::Ptr t,
                                                                     tracktion_engine::Plugin::Ptr p,
                                                                     juce::Identifier modifier,
                                                                     app_services::MidiCommandManager& mcm)
    : track(t),
      plugin(p),
      modifierIdentifier(modifier),
      midiCommandManager(mcm),
      viewModel(track, plugin),
      titledList(viewModel.getItemNames(), "Select Parameter", ListTitle::IconType::FONT_AUDIO, fontaudio::Modsine)
{

    viewModel.itemListState.addListener(this);

    midiCommandManager.addListener(this);

    addAndMakeVisible(titledList);

    juce::Timer::callAfterDelay(1, [this](){titledList.getListView().getListBox().scrollToEnsureRowIsOnscreen(viewModel.itemListState.getSelectedItemIndex());});

}

AvailablePluginParametersListView::~AvailablePluginParametersListView()
{

    viewModel.itemListState.removeListener(this);
    midiCommandManager.removeListener(this);

}

void AvailablePluginParametersListView::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

}

void AvailablePluginParametersListView::resized()
{

    titledList.setBounds(getLocalBounds());

}

void AvailablePluginParametersListView::encoder1Increased()
{

    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.itemListState.setSelectedItemIndex(viewModel.itemListState.getSelectedItemIndex() + 1);

}

void AvailablePluginParametersListView::encoder1Decreased()
{

    if (isShowing())
        if (midiCommandManager.getFocusedComponent() == this)
            viewModel.itemListState.setSelectedItemIndex(viewModel.itemListState.getSelectedItemIndex() - 1);

}
void AvailablePluginParametersListView::encoder1ButtonReleased()
{

    if (isShowing()) {

        if (midiCommandManager.getFocusedComponent() == this)
        {



            if (auto stackNavigationController = findParentComponentOfClass<app_navigation::StackNavigationController>())
            {

                if (auto modifier = dynamic_cast<tracktion_engine::LFOModifier*>(viewModel.addModifierToSelectedParameter(modifierIdentifier)))
                {

                    stackNavigationController->push(new ModifierView(modifier, midiCommandManager));
                    midiCommandManager.setFocusedComponent(stackNavigationController->getTopComponent());

                }

            }

        }

    }

}

void AvailablePluginParametersListView::selectedIndexChanged(int newIndex)
{

    titledList.getListView().getListBox().selectRow(newIndex);
    sendLookAndFeelChange();

}