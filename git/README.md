### How to setup your Git
1. run `ssh-keygen -t ed25519 -C "your_email@example.com"`
2. Copy the content of `~/.ssh/id_ed25519.pub`.
3. Go to [Github](https://www.github.com).
4. Account Settings - SSH and GPG keys.
5. New SSH key.
6. Paste your SSH key.
7. run `eval "$(ssh-agent -s)"`
8. run `ssh-add ~/.ssh/id_ed25519`
9. run `git config --global user.name "<username>"`
10.run  `git config --global user.email "<useremail@domain.com>"`
11.run  `git remote -v`
12. If you see URLs starting with `https://` run `git remote set-url origin git@github.com:<username>/<repo>.git`.


