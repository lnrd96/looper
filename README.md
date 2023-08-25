# Looper
> A simple looper pedal as VST plugin.

If you want to contribute check out the [wiki](https://github.com/lnrd96/looper/wiki) for techniqual documentation and hints.

# Download

## Outline
- [Project Vision and Mission 🚀](#project-vision-and-mission)
  - [Vision](#vision)
  - [Mission](#mission)
- [Technologies](#technologies)
- [Roadmap 🏁](#roadmap)
- [Future Features for Free Version💡](#future-features-for-free-version)
- [Future Features for Paid Version💡](#future-features-for-paid-version)
- [License](#license)
- [Credits](#credits)

## Project Vision and Mission
### Vision

During the recent years lots of musicians switched from the analog world to the digital world.
For instance, many guitar players use models of amplifiers and pedals instead of their
real world counter parts. The same holds for keyboard players as the digital approach offers a manifold selection of realistic models of the most acknowledged hardware.

[Looping](https://youtu.be/oc0yCiCvy6Y?t=144) is often used as a creative tool in music production, allowing a musician to build up layers of sound and create complex compositions by layering loops on top of each other. It can be used live, in performance, to create a backing track or to improvise over a repeating groove.

Some DAWs offer complex and proprietary approaches to looping. This PlugIn offers a simple and universal approach to looping by implementing the common behaviour of an analog looper pedal. It is controllab using one single single command, e.g. assigned to a footstep.

The Plugin is straight forward and can be placed on the master channel of a DAW such that any performance - whether it is vocals, drums, guitar or keys - is captured.

### Mission

## Usage
To realize the key point, simple usage, one can operate using only one button. One performs simple patterns with it. For instance pressing once starts recording, pressing twice pauses and pressing three times resets the recorded audio. 

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

## Future Features for free version
- A good looking UI
- Ability to undo last loop

## Future Features for paid version
- Audio export
- Undo Last Loop 
- Ability to mix loudness of layers selectively
- Ability to remove a layer selectively
- BPM detection, also tell the BPM to the host DAW
  - Such that the other plugins the user uses can adapt to it, e.g. Delay
- Smart adaption of loop cycle using beat detection
  - Such that the app automatically fixes the timing if the user did not set the loop perfectly

## License
TODO

## Credits
The cmake build environment is based on the [prototype repository](https://github.com/eyalamirmusic/JUCECmakeRepoPrototype) by [eyalamirmusic](https://github.com/eyalamirmusic/JUCECmakeRepoPrototype/commits?author=eyalamirmusic).
