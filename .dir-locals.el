((nil . ((eval . (progn
                    (local-set-key (kbd "M-m")
                      (lambda ()
                        (interactive)
                        (compile
                         (format "make -C %s"
                                 (project-root (project-current))))))
                    (local-set-key (kbd "<f2>")
                      (lambda ()
                        (interactive)
                        (async-shell-command
                         (expand-file-name "renderer.exe" (project-root (project-current))))))))
           (compile-command . "make"))))
