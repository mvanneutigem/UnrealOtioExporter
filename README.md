# UnrealOtioExporter
Otio exporter option, plugin for the movie render queue.
Currently only windows is supported, but could easily be extended if you compile opentimelineio for your target platform and add the dependencies.

To use this plugin simply add it to your project and compile the project.
Now you should have this option available in the movie render queue.
![Screenshot](docs/screenshot.png)
Use the first field to specify the name of the otio file.
Use the second field to specify which file extensions to use as references in the otio file, this is useful if you're outputting multiple extensions (e.g. jpeg and mov) but only want e.g. the mov file referenced.