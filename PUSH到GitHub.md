# 首次推送到 GitHub

先在 GitHub 创建公开的 Algorithm-Template 空仓库，不勾选自动生成 README。

```bash
cd ~/Desktop/Algorithm-Template
git init
git branch -M main
git add .
git commit -m "Add C++17 algorithm templates and explanations"
git remote add origin https://github.com/你的用户名/Algorithm-Template.git
git push -u origin main
```

将“你的用户名”换成自己的账号。终端若提示认证失败：执行 `gh auth login`，选择 GitHub.com、HTTPS、浏览器登录；然后执行 `gh auth setup-git`，再重试 push。浏览器网页登录状态不会自动登录 gh。

以后更新：`git add .` → `git commit -m "说明修改内容"` → `git push`。

若远程已有 README 或其他提交，先检查并合并远程历史，不要直接强制推送。若已有 origin，先用 `git remote -v` 检查，无需重复添加。
