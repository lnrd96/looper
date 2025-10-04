# Looper
> A simple looper pedal as VST plugin.


# Demo
Here will be a link to a YouTube video showing the app in usage.

# Download & Install
Here will be links to compiled executibles stored in this repository.

# Contributing
Here will be the link to the Wiki Page, which is relevant for contributers and where they are welcome and hooked.
If you want to contribute check out the [wiki](https://github.com/lnrd96/looper/wiki) for techniqual documentation and hints.

## Outline
- [Project Vision and Mission 🚀](#project-vision-and-mission)
  - [Vision](#vision)
  - [Mission](#mission)
- [Technologies](#technologies)
- [Roadmap 🏁](#roadmap)
- [Future Features 💡](#future-features-for-simple-version)
- [License](#license)
- [Credits](#credits)

## Project Vision and Mission
### Vision

During the recent years lots of musicians switched from the analog world to the digital world.
For instance, many guitar players use models of amplifiers and pedals instead of their
real world counter parts. The same holds for keyboard players as the digital approach offers a manifold selection of realistic models of the most acknowledged hardware.

[Looping](https://youtu.be/oc0yCiCvy6Y?t=144) is often used as a creative tool in music production, allowing a musician to build up layers of sound and create complex compositions by layering loops on top of each other. It can be used live, in performance, to create a backing track or to improvise over a repeating groove.

This PlugIn offers a simple approach to looping by implementing the common behaviour of an analog looper pedal. It is controllab using one single oot step or other MIDI buttons.

The vision of this plugin is to provide a universally applicable looper VST plugin that can be
used straight forward. 

The Plugin can be placed on the master channel of the DAW of choice such that any performances - whether it is vocals, drums, guitar or keys - is captured.

### Mission

## Usage
To realize the key point, simple usage, one can operate using only one button. One performs simple patterns with it. For instance pressing once starts recording, pressing twice pauses and pressing three times resets the recorded audio. Also the software architecture foolows the KISS approach while being open for extensions. Check out the Wiki documentation on the software architecture.

## Technologies
To simplify the development and deployment the [JUCE](https://juce.com/) framework is used.
To further facilitate deployment and getting started as a contributor [CMAKE](https://cmake.org/) is used to build the application. The combination of JUCE and CMAKE enables building on all common platforms as well as deploying to them.

## Roadmap
To get to the first stable version where a MIDI command to control the plugin can be assigned and looping can be performed.

- [x] Build and Debug setup works
- [x] Architecture is set up and documented
- [x] Looping logic is implemented based on the application state
- [x] Front-End is listener of Back-End
- [x] MIDI command to use can be set by the user
  - [x] It can be set via the DAW. The control button is exposed to the DAW
- [x] Application states are set according to MIDI input
- [x] Looping can be performed
- [ ] Smooth transition between loop end and beginning

## Future Features for simple version
- A good looking UI
- Ability to undo last loop
- Possibility to tell the BPM of the looo s.t. the duration is adapted to be in time according to it

## Future Features for smart version
- Record every layer individually instead of overdubbing the audio memory
  - Such that every layer's loudness can be adjusted
  - Such that every layer can be muted individually
  - Such that a layer can be removed
- BPM detection
  - Such that the host DAW can adapt to the BPM
- Smart adaption of loop cycle
  - Such that the app automatically fixes the timing if the user did not set the loop perfectly
  - depends on BPM detection

## License
TODO

## Credits
The cmake build environment is based on the [prototype repository](https://github.com/eyalamirmusic/JUCECmakeRepoPrototype) by [eyalamirmusic](https://github.com/eyalamirmusic/JUCECmakeRepoPrototype/commits?author=eyalamirmusic).
Looking forward to list all contributors here.
