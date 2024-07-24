# Git - Status

**Forces:** For tracking changes in a git repository.

**Solution**

On the command line, type the command: 

```bash
git status 
```
This will return the current state of all items within your personal repo. Deleted, untracked, conflicting, and the old names of renamed files will show up in red. Items that have been changed, but need to be committed will show up in green. Changes set to be part of the next commit will appear in blue.

Example out put of git status:

```bash
On branch main
Your branch is ahead of 'origin/main' by 1 commit.
  (use "git push" to publish your local commits)

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   index.html (in green)
        modified:   styles.css (in green)

Untracked files:
  (use "git add <file>..." to include in what will be committed)
        newfile.txt (in red)

no changes added to commit (use "git add" and/or "git commit -a")
```

ChatGPT 3.5 used for generating example output and as reference for some of the possible output colors.

**Preceding Patterns**

[git_clone](./git_clone.md)

**Following Patterns**

[git_add](./git_add.md)

[git_commit](./git_commit)

[git_push](./git.push)

