import os
import subprocess
import tkinter
import tkinter.filedialog


class MainFrame(tkinter.Frame):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)

        tkinter.Button(self, text="..", command=self.on_select_exe).grid(
            row=0, column=0
        )
        self.exe_path = tkinter.StringVar()
        tkinter.Label(self, textvariable=self.exe_path, relief="sunken").grid(
            row=0, column=1, sticky=tkinter.EW
        )
        tkinter.Button(self, text="Launch", command=self.on_launch).grid(
            row=0, column=2
        )
        self.frame = tkinter.Frame(self)
        self.frame.grid(row=1, column=0, columnspan=3, sticky=tkinter.NSEW)
        self.grid_columnconfigure(0, weight=0)
        self.grid_columnconfigure(1, weight=1)
        self.grid_columnconfigure(2, weight=0)
        self.grid_rowconfigure(1, weight=1)

        self.proc = None

        self.master.protocol("WM_DELETE_WINDOW", self.on_close)

    def on_select_exe(self):
        current_dir = os.path.abspath(os.path.dirname(__file__))
        path = tkinter.filedialog.askopenfile(initialdir=current_dir)
        if len(path.name) > 0:
            self.exe_path.set(path.name)

    def on_launch(self):
        if len(self.exe_path.get()) > 0 and not self.proc:
            self.proc = subprocess.Popen(
                f"{self.exe_path.get()} --parent {self.frame.winfo_id()}"
            )

    def on_close(self):
        if self.proc:
            self.proc.kill()
        self.master.destroy()


def main():
    root = tkinter.Tk()
    root.geometry("640x480")
    MainFrame(root, border=1).pack(fill=tkinter.BOTH, expand=True)
    root.mainloop()


if __name__ == "__main__":
    main()
