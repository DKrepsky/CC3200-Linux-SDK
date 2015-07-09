# USAGE

### Pre-requisites
- Eclipse CDT (https://eclipse.org/cdt/)
- GNU ARM Eclipse Plug-ins (http://sourceforge.net/projects/gnuarmeclipse/)
- udev rules to get hardware access.
- COM port client (minicom, putty, etc.).
- OpenOCD (latest version). (sudo apt-get install openocd)

For detailed instructions on how to setup the development environment please read one of the following tutorials:
- https://gist.github.com/dariuskl/086823c781bfb61af361
- http://www.achanceofbrainshowers.com/blog/tech/2014/8/19/cc3200-development-under-linux/


### Using the SDK

For now, just clone this repository into the same directory of eclipse (say /opt/cc3200) and try to
import a demo as a template.

If the sdk isn't in the same directory of eclipse, set the CC3200SDK variable for "linked resources" 
and "build variables", in project->preferences, to the current sdk path.


