# Assignment 4
Nick Chapman

### Abstract
The Particle Interface program is simply a command-line interface which is meant to catalog various particles into various .csv files. The files can be opened one at a time by name almost like a DOS system. Use the commands "help" and "exit" to get help and close the program respectively. All of the commands like open, close, push, pop, pick, delete, etc. all operate on the *currently opened table*. If there is no file opened--or is a file opened when there needs to be none--then the program will give you an alert. It should be quite intuitive and work like a simple library. I will make sure to provide screenshots here of the program working so you can see it. Some things I think would be cool would be to make tables of all the fermions, bosons, and maybe a standard standard model, and a hypothetical standard model.

### Welcome
Upon opening the program, you should be greeted with this screen to know it's working:
![Fig. 0, The Welcome Screen](./screenshots/welcome.jpg)

### Getting Help
If you need to view the commands again, always type `help` and you will be met with the following menu:
![Fig. 1, The help menu](./screenshots/help.jpg)
### Opening a File
The process of opening a file consists of first creating a new table (.csv) file, and then opening it. Begin by typing:
		`new <FILE-NAME>`
		where `<FILENAME>` is the name of your file, including sub-paths. However, due note that I have not implemented a measure to create a directory if there is not one. This of course implies that you need to create a directory before creating a table into it.
		

Verify that the table was created by checking first if you received any error messages, and further by looking in the directory in file explorer. This just created the empty file, however. If you try and do anything besides opening and pushing a first entry it will give you the message `Empty table.` Type the following commands:
		`open <FILE-NAME>`
		`push`
		where `<FILE-NAME>` is the same path as whatever path you created it with. The `push` command with prompt you for various values.
		**When entering the charge for a particle, it will be counted as *thirds* the magnitude of an electron. Therefore, entering 1 will store $\frac{1}{3}$ and entering 3 stores 1. When entering the spin for a particle it is measured in increments of $\frac{1}{2}$, so entering 2 becomes 1 and 1 becomes $\frac{1}{2}$.

![Fig. 2, the process of creating, opening, adding to, and saving a table.](./screenshots/new-open-push-save.jpg)
### Saving a File
Remember: after you are done making changes to your table--and even if youre not yet--type the `save` command. It doesn't require any arguments and it simply saves it to where the file is understood to be kept.

If you type a file name after the `save` command while a file is open, it will save-as the file data to a new table with the same name. If it is the same name as the file opened, or another file, it will simply overwrite it.

![Fig. 3, performing a save-as operation to duplicate a file into another with a different name](./screenshots/save-as.jpg)

### Conclusion
There are a few more commands that I don't think need to be covered here. `ls` simply works like it does in POSIX and `clear` does too. `delete` is used to delete tables and will ask you for confirmation before proceeding. `push, pop, and pick` work as documented also.

Boom! You're now a master at my extremely niche and quite impractical Particle Library Interface. Thank you for your patience Professor Seunarine, because I know I am like two days late. I think I could have turned it in on time if I started last Monday but thats my fault lol.
