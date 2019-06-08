CS300 A Team Project: The Island of Frupal Game

Developers: Elyse, Jessica, John, Leior and Max


Overview:
This is a text based game in which the treasure seeker (displayed as the '&' symbol)
can move around on the island of frupal in search of the Jewels ofAntioch. Each step 
potetially reveals more of the island and potentially increases their amount of gold
which can be used to buy tools to help surmount obstacles found on the island.
Beware, moving around depletes your energy and if you run out then the game is over!


Build instructions:
This program was designed to run on a linux machine but may comply with any machine 
that supports linux style coloring and the system "clear" command

To build just run the command: make
This will create the frupal_main executable in the same directory

To play just run the ./frupal_main executable.
To play with non-default configurations run: ./frupal_main <config_file>
(where "<config_file>" indicates the name of the config file to load 
note: In addition to any custom configuration files the directory must also contain a 
compatible default config file named defaultConfig.txt

A quick option to build and immediately begin a default game: make itso


Playing the game:
The available options in each stage of the game will always be printed on the screan.
each command consists of a single charachter, often an index as shown in the menu
that is printed on the screen.

It is possible to modify configurations from the "Options" menu, though once the game
has started (my selecting the "Play" command from the main menu only some of the 
configuration options will be available.

Custom tools, obstacles, starting conditions, and levels of difficulty may be loaded
from config files and/or modified in the game's Options menu and saved.

For instructions on what actions can be performed, as well as any output from the
previous action please carefully read the text that is printed on the screan.


Enjoy!

