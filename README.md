# MovieDataExplorer

Project for querying Film data files completed for CIS*2520 (Data Structures) at the University of Guelph.

The project parses data provided by IMDB and builds a BST tree for that data. Building the BST's takes some time
but after they are built they offer fast lookup of films or actors.

To use:
1.  Download name.basics.tsv.gz, title.basics.tsv.gz, and title.principals.tsv.gz, extract the contents of the
    3 files into the same directory.
2.  Download source files on a system with GNU make and gcc installed
3.  From the directory where files are located, type enter "make" in the terminal.
4.  To run the compiled project type "./MDE \<data files\>" where \<data files\> is the directory containing the
    extracted files downloaded from earlier.

The program will take some time to read the data and build the data structures. Once it's finished you will
be prompted with "> ". When you see the prompt, type "title \<some title\>" or "name \<some actor name\>" where
\<some title\> is the title of a film and \<some actor name\> is the name of an actor. The program will return
a list of some of the actors (because the data sets are incomplete) in the film you entered, or a list of
films the actor you entered appeared in.
