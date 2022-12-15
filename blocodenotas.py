from tkinter import *
from tkinter import ttk

janela = Tk()
janela.title('Bloco de notas')
janela.geometry('300x300')

caixa_texto = Text(janela) 
caixa_texto.pack(fill = BOTH)

janela.mainloop()
