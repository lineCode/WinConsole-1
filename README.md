# WinConsole
A simple C++ utility for manipulation of the Windows console (e.g. colors)

All functions are in the con:: namespace. For example:

    con::setTitle("Title here");
	
	std::cout << con::Color::BLUE << "Blue text.";
	
It currently can:

* Set title.
* Set cursor position.
* Set foreground/background colors (inline or otherwise).
* Clear the console.

