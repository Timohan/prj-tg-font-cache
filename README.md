# prj-tg-font-cache

prj-tg-font-cache (library) is my personal project to be as cache for prj-ttf-reader's glyphs.

There is 3 parts in the project:
* Library (prj-tg-font-cache itself), written in c++
* opengl-example, renders the glyphs results in opengl program, written in c++
* unit tests, some basic tests for library, written in c++

prj-tg-font-cache was done on ubuntu 24.04.

## prj-tg-font-cache

prj-ttf-reader library creates the glyphs and prj-tg-font-cache is as cache for those glyphs to avoid generating same glyphs over again.

### Development Environment

Required libraries:  
prj-ttf-reader from https://github.com/Timohan/prj-ttf-reader

### Build and Installation

cd lib  
make  
sudo make install

### Clean and Uninstallation

make clean  
sudo make uninstall

## opengl-example

opengl-example uses the prj-ttf-reader & prj-tg-font-cache library and draws the text in opengl.

### Development Environment

Required libraries: libglfw3-dev, libglew-dev, prj-ttf-reader  
Required internal libraries: prj-tg-font-cache library

### Build

cd example/opengl-example  
make

### Running the opengl-example

Usage: ./opengl-example -s <"text string"> -f <"path to ttf"> -z <"font size">

For example:
./opengl-example -s "text goes here" -f "/tmp/font.ttf" -z 25

./opengl-example -s "the quick brown fox jumps over the lazy dog." -f "<"path to fonts">/freefont/FreeSans.ttf" -z 40  
./opengl-example -s "ગુજરાતી યુનિકોડ ફોન્ટ સૂચી" -f "<"path to fonts">/samyak-fonts/Samyak-Gujarati.ttf" -z 20  

### Clean

make clean

## unit tests

Unit tests is very basic tests for only some functionalities in the
prj-tg-font-cache library.

### Build

cd test  
make

### Running the unit tests

./prj_tg_font_cache_test

## Example font rendering

FreeSans font:  
![FreeSans](md_images/FreeSans.png)  

Samyak-Gujarati font:  
![Samyak-Gujarati](md_images/Samyak-Gujarati.png)


