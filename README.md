# Compiling
* To use FTGL, set the environment HAS_FTGL to something that isn't blank. You may also edit the source code
to open another font file for displaying the text.
* Requires GLFW2, GLTW, swisseph, and GLM

# Controls
* Shift+Up/Down: Scoot the camera 1 AU closer/farther
* Up/Down: Pan the camera up/down by 1 AU
* Left/Right: Pan the camera left/right by 1 AU
* Z: (Un)pause the date
* Escape: Quit the program
* Spacebar: pause
* A: Toggle the display of Earth's moon
* 0/1/2/3/4/5/6/7/8 + Left/Right: Adjust the datetime by the planet's planetary orbit. Here's the value table

KEY|Planet      |Date increment
---|------------|--------------
  0|Mercury     |87.969
  1|Venus       |224.698
  2|Earth/Sun   |365.256363051
  3|Mars        |686.971
  4|Jupiter     |4332.59
  5|Saturn      |10759.22
  6|Uranus      |30799.095
  7|Neptune     |60190.03
  8|Pluto       |89865.65

# Nitpicks
* None of the planets are to scale
* Decided to go with distance radii of 1AU between each planet
* Never figured out drag and drop, so had to be satisfied with adjusting the date through keybindings
* Haven't updated archaic API in planet in case I revist this program to include actually drawing the items in question to scale

# Sources
* http://cse.csusb.edu/tong/courses/cs520/notes/texture.php
*http://www.math.oregonstate.edu/home/programs/undergrad/CalculusQuestStudyGuides/vcalc/parsurf/parsurf.html
* select external library for text rendering (http://sourceforge.net/apps/mediawiki/ftgl/index.php?title=Main_Page)
* http://stackoverflow.com/questions/8024898/calculate-the-vertex-normals-of-a-sphere
* http://www.opengl.org/archives/resources/features/fontsurvey/
* http://web.archive.org/web/20110304035729/http://www.pitt.edu/~mwr12/compcorner/linuxstuff/ftgl.html
* http://leeboyge.blogspot.com/2011/03/compiling-ftgl-213rc5-on-windows-using.html
* http://ftp.gnome.org/pub/gnome/binaries/win32/dependencies/freetype-dev_2.4.2-1_win32.zip
* http://fooplot.com/plot/lvxlsasapl
