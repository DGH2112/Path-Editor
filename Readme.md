 Path Editor
=============

Author:   David Hoyle

Version:  1.0c

Date:     27 Jun 2018

Web Page: http://www.davidghoyle.co.uk/WordPress/?page_id=1265

## Overview

This application allows you to editor your system and user paths in a simple list format. In order for
you to edit the system path yopu will need to be an administrator.

## Usage

It will be no surprise to those of you who use RAD Studio that the design of this application is very
similar to that of the library Path Editor in RAD Studio. I think the way that’s handled is excellent,
therefore I borrowed the idea. Note: to change the system path you need to be either an administrator or
run the path editor as an administrator.

 * User Profiles: This aspect of the application needs some work however it provides a list of user
   profiles from which you can select view and / or  edit the user’s path. At the moment it looks for a
   read/write key Volatile Environment under the user profiles to detect user profiles. To me it seemed
   the obvious place to look for the user’s name but this is not the case as its only exists if the user
   is logged in. I’m looking at other ways of doing this.

 * Tabs: There are two tabs for editing paths. The first is the System Path and this will be read only
   unless you are an administrator or you run and application as the administrator. The second tab
   provide the User Path for the selected user profile but can be changed to other users if available
   (current logged on – see User Profiles above).

 * Path List: The path list is a read only list of the individual paths that make up either the system or
   user path. A greyed out path indicates that it is not a valid path on your system (environment
   variables are expanded). Double clicking on an item in the list will place it in the edit control.

 * Update: If the path information is changed, this button will become available in order for you to save
   the changes back to the specific path. Note: changes to the paths will NOT automatically be committed
   on closing the application – you need to Update the path to commit the changes.

 * Move: This method is only available if you have permissions to edit the system path and the user path
   and it allows you to select a path from the list and move it to the bottom of the other list, i.e.
   from the system path to the user path or the other way around.

 * Replace: This button allows you to replace the currently selected path in the list with the path in
   the path edit control.

 * Add: This buttons allows you to add the path in the edit control to the bottom of the path list.

 * Delete: This button will delete the selected path in the list.

 * Browse: Browse allows you to browse your system for a directory which will then be placed in the path
   edit control.

 * Up / Down: These buttons will move the selected path in the list up or down the order.

## Current Limitations

In order to edit the system path you will need to launch the application as an administrator.

## Binaries

You can download a binary of this project if you don't want to compile it
yourself from the web page above.