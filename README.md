# Looper
A smart looper pedal as VST plugin.

## Outline

## Project Vision and Mission
### Vision

During the recent years lots of musicians switched from the analog world to the digital world.
For instance, many guitar players use models of amplifiers and pedals instead of their
real world counter parts. The same holds for keyboard players as the digital approach offers a manifold selection of realistic models of the most acknowledged hardware. Some musicians may prefer the sound and feel of analog gear, while others may find that digital technology offers greater flexibility and versatility.

[Looping](https://youtu.be/oc0yCiCvy6Y?t=144) is often used as a creative tool in music production, allowing a musician to build up layers of sound and create complex compositions by layering loops on top of each other. It can be used live, in performance, to create a backing track or to improvise over a repeating groove.

However, aside from different, and quite complex, live performance options in some DAWs or inside specific plugins, there seems to be no simple and universal solution to transfer a simple looper pedal to the digital world. Basic analog looper pedals are most commonly operated on using only one button. However, there seems to be no software solution that enable looping using only one MIDI foot step.

Thus, the vision of this project is to provide a universally applicable looper VST plugin that can be
used with only one foot step. It is supposed to be placed on the master channel of the DAW such that any performances - whether it is vocals, MIDI drum pads, guitar or keys - is captured.

### Mission
To realize the key point, simple usage, the operation is implemented using patterns of button presses of the single foot step. For instance pressing once starts recording, pressing twice pauses and holding the button resets the recorded audio. 

### Technologies
To simplify the development and deployment the [JUCE](https://juce.com/) framework is used.
To further facilitate deployment and getting started as a contributor [CMAKE](https://cmake.org/) is used to build the application. JUCE enables building on all common platforms as well as deploying to them.

### Roadmap
TODO

### Release Features
The features of the first release include the ability to assign a MIDI command to the application and to perform looping with it.
#### Post-Release Features
- A feasable UI
- Audio export
- BPM detection
- Audio normalising and automatic loudness improving

## Build instructions
Usual build using cmake, working directory should be root of this repo.
`mkdir build`
`cd build`
`cmake --`
`cmake --build . `
Executables will be at `build/Plugin/Looper/Looper_artefacts/`

## License
TODO

## Credits
The cmake build environment is based on the [prototype repository](https://github.com/eyalamirmusic/JUCECmakeRepoPrototype) by [eyalamirmusic](https://github.com/eyalamirmusic/JUCECmakeRepoPrototype/commits?author=eyalamirmusic).
