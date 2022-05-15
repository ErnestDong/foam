---
tags: cli
---
# minor things

## how to debug `require cl`

```emacs-lisp
(require 'loadhist)
(file-dependents (feature-file 'cl))
```

## lsp mode

an introduction of lsp mode can be found [here](https://emacs-lsp.github.io/lsp-mode/tutorials/how-to-turn-off/)

## [[python]] mode

`C-n` send python line

`C-c C-l` send python file

## debug

```shell
  ps aux | grep -ie emacs | grep -v grep | awk '{print $2}' | xargs kill -SIGUSR2
```

# [[emacs-lisp]]

# eshell

eshell is a built-in [[shell]] in [[emacs-lisp]] and can REPL [[emacs-lisp]]

# evil

an awesome [[emacs]] package

## search and replace

    :s/old/new/g

