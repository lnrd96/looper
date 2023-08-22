# Looper
> A simple looper pedal as VST plugin.

If you want to contribute check out the [wiki](https://github.com/lnrd96/looper/wiki) for techniqual documentation and hints.

## Outline
- [Project Vision and Mission 🚀](#project-vision-and-mission)
  - [Vision](#vision)
  - [Mission](#mission)
- [Technologies](#technologies)
- [Roadmap 🏁](#roadmap)
- [Future Ideas 💡](#future-ideas)
- [License](#license)
- [Credits](#credits)

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

## Technologies
To simplify the development and deployment the [JUCE](https://juce.com/) framework is used.
To further facilitate deployment and getting started as a contributor [CMAKE](https://cmake.org/) is used to build the application. JUCE enables building on all common platforms as well as deploying to them.

## Roadmap
To get to the first stable version where a MIDI command to control the plugin can be assigned and looping can be performed.

- [x] Build and Debug setup works
- [x] Architecture is set up and documented
- [x] Looping logic is implemented based on the application state
- [x] Front-End is listener of Back-End
- [ ] MIDI command to use can be set by the user
  - [ ] It can be set via the DAW. The control button is exposed to the DAW
- [x] Application states are set according to MIDI input
- [x] Looping can be performed

### Future Ideas 
- A good looking UI
- Smooth transition between loop end and beginning
- Audio export
- Ability to mix loudness of layers selectively
- Ability to remove a layer selectively
- BPM detection
- Smart adaption of loop cycle using beat detection
  - Such that the app automatically fixes if the user did not set the loop perfectly in time

## License
TODO

## Credits
The cmake build environment is based on the [prototype repository](https://github.com/eyalamirmusic/JUCECmakeRepoPrototype) by [eyalamirmusic](https://github.com/eyalamirmusic/JUCECmakeRepoPrototype/commits?author=eyalamirmusic).
