from tkinter import *
from tkinter.messagebox import *
from tkinter.filedialog import *
import os

BLACK = '#121212'
WHITE = '#ffffff'

class Notepad:

    __root = Tk()
    __textBox = Text(__root)
    __scrollbar = Scrollbar(__textBox)
    __menuBar = Menu(__root)
    __archiveMenu = Menu(__menuBar, tearoff=0)
    __file = None

    def __init__(self):

        self.__root.title('Untitled - Notepad')
        self.__root.geometry('400x400')
        self.__root.resizable(False, False)
        self.__root.config(menu=self.__menuBar)
        self.__root.grid_rowconfigure(0, weight=1)
        self.__root.grid_columnconfigure(0, weight=1)

        self.__scrollbar.pack(side=RIGHT, fill=Y)
        self.__scrollbar.config(command=self.__textBox.yview) 

        self.__textBox.grid(sticky = N + E + S + W)
        self.__textBox.config(yscrollcommand=self.__scrollbar.set)
        self.__textBox.config(bg=WHITE, fg=BLACK, font='Arial 12')

        self.__archiveMenu.add_command(label='New', command=self.__new)
        self.__archiveMenu.add_command(label='Open', command=self.__open)
        self.__archiveMenu.add_command(label='Save', command=self.__save)
        self.__archiveMenu.add_command(label='Exit', command=self.__exit)
        self.__menuBar.add_cascade(label='Archive', menu=self.__archiveMenu)

    def __new(self):
        self.__file = None
        self.__textBox.delete(1.0, 'end')
        self.__root.title("Untitled - Notepad") 

    def __open(self):

        self.__file = askopenfilename(defaultextension = '.txt',
            filetypes = [('Todos os Arquivos','*.*'),
                        ('Arquivos de texto','*.txt')])
        if self.__file == "": 
            self.__file = None
        else: 
            self.__root.title(os.path.basename(self.__file) + " - Notepad") 
            self.__textBox.delete(1.0,END) 
            __file = open(self.__file,"r") 
            self.__textBox.insert(1.0,__file.read()) 
            __file.close()

    def __save(self):

        if self.__file is None:
            self.__file = asksaveasfilename(initial__file = 'arquivo.txt',
            defaultextension = '.txt',
            filetypes = [('Todos os Arquivos','*.*'),
            ('Arquivos de Texto','*.txt')])

        self.__root.title(os.path.basename(self.__file) + " - Notepad") 
        __file = open(self.__file,'w')
        __file.write(self.__textBox.get(1.0,'end'))
        __file.close()

    def __exit(self): 
        self.__root.destroy() 

    def run(self): 
        self.__root.mainloop()

main = Notepad()
main.run()
