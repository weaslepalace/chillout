# chillout
A handy utility to remind me to chill out, and take a break sometimes

_This is a work in progress, and shouldn't be used by anybody for any reason._

This is a little utility that I've been idly working on since July, 2020. I started it as a pandemic project to help keep my skills sharp while unemployed, while also serving as a platform to level up my C++. I've also always wanted to learn GTK+, and what better way than a simple application such as this.

## What it does
The problem here is that like most engineers, I get too caught up in 'the flow'. Normally this is a good thing; being in a flow state while writing code, or laying out a PCB is one of my favorite things in life. It however is not a good thing when I find myself having been in a flow for four or more hours while neglecting my own health and comfort. I can easily forget to eat, go to the bathroom, or even move my body beyond my typing fingers. After breaking out of an hours long flow, I feel like hot garbage, and even after fullfiling my needs I find it difficult to get back to work. This can actually damage my productivity.
So that's why I started writing this app. Sure, there are other apps out there that remind you to take a break, but do any of them work? It's so easy to just close the pop-up and keep working. So I wanted to take a more extreme approach. When a timer expires, the app will fire a message over dbus to lock your screen. So big deal, I can just unlock my screen, right? Nope. The app will continue to send dbus messages to the gnome screensaver for the duration of the break (which is programmable), so the screen will stay locked, forcing me to get up and do some yoga or something.
A simple control panel lets me configure the time and duration of the breaks, and shows how long I have until the next break. There are still some kinks to work out with this.
## License
MIT. Nothing fancy here.

## Contributing
Maybe I'd accept a pull request? Not sure. This is really just a personal project to sharpen my skills, so I'm not really taking it seriously.
