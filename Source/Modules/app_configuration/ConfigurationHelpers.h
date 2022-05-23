#pragma once
#include <juce_core/juce_core.h>
#include <tracktion_engine/tracktion_engine.h>

class ConfigurationHelpers {
public:
    static inline const juce::String ROOT_DIRECTORY_NAME = "LMN-3";
    static inline const juce::String SAMPLES_DIRECTORY_NAME = "samples";
    static inline const juce::String DRUM_KITS_DIRECTORY_NAME = "drum_kits";
    static juce::File getSamplesDirectory();
    static juce::File getDrumKitsDirectory();
    static juce::File getTempSamplesDirectory(tracktion_engine::Engine& engine);
    static juce::File getTempDrumKitsDirectory(tracktion_engine::Engine& engine);
    static void initSamples(tracktion_engine::Engine& engine);
    static bool getShowTitleBar(juce::File& configFile);

private:
    static bool writeBinarySamplesToDirectory(const juce::File &destDir,
                                              juce::StringRef filename,
                                              const char *data,
                                              int dataSizeInBytes);

    static void initBinarySamples(const juce::File &tempSynthDir, const juce::File &tempDrumDir);
    static void initUserSamples(const juce::File& userSynthSampleDir, const juce::File& userDrumDir,
                                const juce::File &tempSynthDir, const juce::File &tempDrumDir);
    static juce::File createTempDirectory(tracktion_engine::Engine& engine, const juce::String &folderName);

};
