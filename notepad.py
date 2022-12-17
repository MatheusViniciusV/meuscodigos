from tkinter import *
from tkinter.messagebox import *
from tkinter.filedialog import *
import os

BLACK = '#121212'
WHITE = '#ffffff'

class Notepad:

    root = Tk()
    textBox = Text(root)
    scrollbar = Scrollbar(textBox)
    menuBar = Menu(root)
    archiveMenu = Menu(menuBar, tearoff=0)
    styleMenu = Menu(menuBar, tearoff=0)
    helpMenu = Menu(menuBar, tearoff=0)
    file = None

    def __init__(self):

        self.root.title('Untitled - Notepad')
        self.root.geometry('400x400')
        self.root.iconphoto(False, PhotoImage(file='icon.png'))
        self.root.resizable(False, False)
        self.root.config(menu=self.menuBar)
        self.root.grid_rowconfigure(0, weight=1)
        self.root.grid_columnconfigure(0, weight=1)

        self.scrollbar.pack(side=RIGHT, fill=Y)
        self.scrollbar.config(command=self.textBox.yview) 

        self.textBox.grid(sticky = N + E + S + W)
        self.textBox.config(yscrollcommand=self.scrollbar.set)
        self.textBox.config(bg=BLACK, fg=WHITE, font='Arial 12 bold')

        self.archiveMenu.add_command(label='New', command=self.new)
        self.archiveMenu.add_command(label='Open', command=self.open)
        self.archiveMenu.add_command(label='Save', command=self.save)
        self.archiveMenu.add_command(label='Exit', command=self.exit)
        self.menuBar.add_cascade(label='Archive', menu=self.archiveMenu)

    def new(self):
        self.file = None
        self.textBox.delete(1.0, 'end')

    def open(self):

        self.file = askopenfilename(defaultextension = '.txt',
            filetypes = [('Todos os Arquivos','*.*'),
                        ('Arquivos de texto','*.txt')])
        if self.file == "": 
            self.file = None
        else: 
            self.root.title(os.path.basename(self.file) + " - Notepad") 
            self.textBox.delete(1.0,END) 
            file = open(self.file,"r") 
            self.textBox.insert(1.0,file.read()) 
            file.close()

    def save(self):

        if self.file is None:
            self.file = asksaveasfilename(initialfile = 'arquivo.txt',
            defaultextension = '.txt',
            filetypes = [('Todos os Arquivos','*.*'),
            ('Arquivos de Texto','*.txt')])

        self.root.title(os.path.basename(self.file) + " - Notepad") 
        file = open(self.file,'w')
        file.write(self.textBox.get(1.0,'end'))
        file.close()

    def exit(self): 
        self.root.destroy() 

    def run(self): 
        self.root.mainloop()

main = Notepad()
main.run()
