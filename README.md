# Algorithms
Here you can find algorithms and code related to the project

In the folder Algorithms you will find the current MATLAB/SIMULINK/C++ files for the project.

*Under the link https://mega.nz/folder/8bkSgKTC#Z9Gc_16WzOTBEaBSgeUETg you will find cloud with the BagFile of the project
*Under the link https://discord.gg/8c3nUPEz you will find the DISCORD server


IMPORTANT

Please, whenever you upload the new version of the code on the git repo, follow the coding guide and check that your code fits all rules!

Whenever you upload a renewed version of the document make sure you put related comments to the commit with short but detailed description of what has been changed!

All experimental coding must be done in other branches, please keep the main branch untouched!



# MAIN COMMANDS OF THE GIT 

* git add "file name" or . for all files in the folder

The command adds changes in the working directory to the staging area. It tells Git that you want to include updates to a particular file in the next commit. However, git add doesn't affect the repository significantly—changes are not recorded until you run git commit.
In conjunction with these commands, you'll also need git status to view the working directory and staging area state.
In review, git add is the first command in a chain of operations that directs Git to "save" a snapshot of the current project state, into the commit history. When used on its own, git add will promote pending changes from the working directory to the staging area.
The git status command is used to examine the current state of the repository and can be used to confirm a git add promotion.
The git reset command is used to undo a git add.
The git commit command is then used to Commit a snapshot of the staging directory to the repositories commit history.
git status- to check the status of the modified files


* git commit -m "comment of change"

The "commit" command is used to save your changes to the local repository.
Note that you have to explicitly tell Git which changes you want to include in a commit before running the "git commit" command.
This means that a file won't be automatically included in the next commit just because it was changed.
Instead, you need to use the "git add" command to mark the desired changes for inclusion.
Also note that in Git, a commit is not automatically transferred to the remote server.
Using the "git commit" command only saves a new commit object in the local Git repository.
Exchanging commits has to be performed manually and explicitly (with the "git fetch", "git pull", and "git push" commands).
Note: local git repository is you folder of files on your laptop.


* git push - to upload all changes on the server (To the GitHub repositiry)

git pull - take out the changes from the git repository (To update you file in local repo from GitHub repo)
Note: the changes will be taken as default from the master branch



