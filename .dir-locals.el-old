((nil . ((eval . (progn
                   (setq-local my-renderer-project-root "c:/dev/3drenderer/")

                   (unless (fboundp 'my-renderer-project-mode)
                     (define-minor-mode my-renderer-project-mode
                       "Local keybindings for this project directory."
                       :lighter " Renderer"
                       :keymap (let ((map (make-sparse-keymap)))
                                 (define-key map (kbd "<f1>")
                                   (lambda ()
                                     (interactive)
                                      (let ((default-directory my-renderer-project-root))
                                        (compile "make clean"))))
                                 (define-key map (kbd "M-m")
                                   (lambda ()
                                     (interactive)
                                     (compile
                                      (expand-file-name "build.bat"
                                                         my-renderer-project-root))))
                                 (define-key map (kbd "<f2>")
                                   (lambda ()
                                     (interactive)
                                     (start-process "renderer" nil
                                                    (expand-file-name "renderer.exe"
                                                                       my-renderer-project-root))))
                                 (define-key map (kbd "<f3>")
                                   (lambda ()
                                     (interactive)
                                     (start-process "raddbg" nil "raddbg.exe"
                                                    (expand-file-name "renderer.exe"
                                                                       my-renderer-project-root))))
                                 map)))
                   (my-renderer-project-mode 1)))
         (compile-command . "make"))))
