Terminal-File-explorer
This application operates in two modes.

1) Normal Mode :
Firstly it displays the contents of the directory in which applications has started. Hereby the user can traverse into any directory by pressing enter and the application will list down its contents. If user presses enter key on file, it will open in the user's default application with respect to that file.

Features : The application has the following features and key bindings.

1. Scrolling: User can scroll up and down through UP and DOWN arrow keys if the content doesn't fit.

2. Back and Front: User can go to previously visited directory by LEFT arrow key. User can simultaneously go in the forward       direction by pressing RIGHT arrow key.

3. BACKSPACE key : Go to the parent directory.

4. H key: Go to home directory from where the application has started.

2) Command Mode :

The application enters command mode by pressing ":" key.

The application exits the command by pressing "ESC" key.

The application supports following commands.

- COPY
- MOVE 
- RENAME
- CREATE
- DELETE
- GOTO 
- SEARCH
- SNAPSHOT
(Snapshot: user can store the state of the current working directory in a dump file)
User can quit application by pressing "p" key from normal mode.

KNOWN BUGS

1. Search command only displays the search result and not the interactive search allowing user to press enter or scroll.
2. Horizonatal overflow or text wrap is not handled.
