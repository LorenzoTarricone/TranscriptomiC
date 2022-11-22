# Instructions to set up git and link it to your Qt project

## About git

Since some of you have never worked with git before, here is an overview of how it works: `https://www.geeksforgeeks.org/how-git-version-control-works/`

## Install git

If you have not already installed git on your computer, you will have to do so. It will be easiest to use the commandline to push and pull to and from the remote repository. 
You can install git through their official website : `https://git-scm.com/book/en/v2/Getting-Started-Installing-Git`

## SSH-keys

Since the repository is private, it will prompt for passwords whenever you are trying to make any changes. SSH keys are a very convinient way to get around that. The way it works is basically:
- you create a key on your private laptop using `ssh-keygen`
- add the key to the ssh-keys on your GitHub account
- then you can clone the repository using the ssh link and you will not be prompted for a password

### Generating ssh-keys
This is just a rough guide (for macOS, might differ for Windows or LinuX), I will link some more thorough explanations below. On your commandline/ terminal:
- go into your root directory with `cd ~`
- generate keys with `ssh-keygen -t rsa -C "your@email.address"` (insert the email address that is linked to your github)
- go into the `.ssh` directory in your machine with  and `cd .ssh`
- access the file `id_rsa.pub` using `cat` or `vi`
- copy the key that starts with 'ssh-rsa' and ends with your email address (if you never generated a key before or only with that email address, that might be the entire file)
- add that key to the github under https://github.com/settings/keys (you can label it too)

This link helps for macOS users: https://gist.github.com/ddeveloperr/9574740628637bc2a127

Windows: https://syntaxbytetutorials.com/add-a-github-ssh-key-on-windows/

GitHub documentation: https://docs.github.com/en/authentication/connecting-to-github-with-ssh/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent



## Creating a Qt project
To compile the code we will be using the Qt creator, which means that any compilation flags, linkers, etc. will be handled by the `.pro` file. We will set up a skeleton project on the github repository, so that you will simply have to clone the repository and **not create a new Qt project** yourselves.

## Cloning the repository
When cloning a repository, it will create a new folder with that name, so first cd into the folder where you want the project to be ('CSE201' or something). Then, execute the command `git clone git@github.com:LorenzoTarricone/TranscriptomiC.git`. This will clone the entire repository to your computer. Since we will have established the ssh-key authentification by then, you should not be prompted for any passwords.

## Working with git
Here are some basic concepts that are important to remember when collaborating with other people on git:
- anytime you start working, cd into your repository on the commandline and run `git fetch`, this will update your local repository with the changes made to the remote repository on GitHub
- throughout working on your code, commit, push and fetch every now and then to keep your local repository **up to date**, since other people are changing their code as well 
- ideally, every version of code you push to the remote repository is working (for us, it should at least **compile**)

The basic commands you use to update your code are:
- `git fetch`: downloads updates from remote repository to your computer, but will not make any changes to your local files, harmless
- `git pull`: downloads updates from remote repository to your computer, includig changes made to files you have on your local machine, it will try to merge these changes (merge conflict can occur), do not use if you have any unstaged changes. Usage:
`git pull origin main` (TO BE COMPLETED)
- `git add`: adds file to your local git (it makes git aware that that file exists and to start tracking the changes you make to it)
- `git commit`: queues file to be added to the remote repository. Every commit needs a commit message, you can supply it using the argument `-m` and the message in double quotes: `git commit -m "put your commit message here"`. The commit message describes the changes made compared to the previous version. It might also be good to include your name in the message
- `git push`: adds the committed files to the remote respository. To avoid any conflicts, make sure your local repository is as up-to-date with the remote repository as possible by running `git fetch` or even `git pull` before. 
Usage: `git push -u origin master:main`, this pushes the changes on your local branch `master` to the remote branch `main`.
- `git stash`: can be used to save unstaged (added/ committed) local changes before dealing with pushes, pulls, etc.


### Branches
We will probably be working with branches, such that each of you can work on their on branch to minimize conflicts and errors in the main branch. The idea here is to merge the branches to the mai branch as often as possible. (TO BE COMPLETED)

### Pull requests
Whenever there is a merge to the main branch, you can create a pull request to properly integrate your code with the code in the main branch and to ensure the correctness of the main branch code. (TO BE COMPLETED)

