from tkinter import *

class Converter:

    __root = Tk()
    __label_kmh = Label(__root)
    __label_ms = Label(__root)
    __entry_kmh = Entry(__root)
    __entry_ms = Entry(__root)
    __label_lb = Label(__root)
    __label_kg = Label(__root)
    __entry_lb = Entry(__root)
    __entry_kg = Entry(__root)
    __label_c = Label(__root)
    __label_f = Label(__root)
    __entry_c = Entry(__root)
    __entry_f = Entry(__root)
    __clear = Button(__root)
    __button = Button(__root)

    def __init__(self):

        self.__root.title('')
        self.__root.geometry('180x220')
        self.__root.resizable(False, False)

        self.__label_kmh.config(text='Km/h')
        self.__label_kmh.grid(column=0, row=0, padx=10, pady=5)

        self.__label_ms.config(text='m/s')
        self.__label_ms.grid(column=1, row=0, padx=10, pady=5)

        self.__entry_kmh.config(width=10)
        self.__entry_kmh.grid(column=0, row=1, padx=10, pady=5)

        self.__entry_ms.config(width=10)
        self.__entry_ms.grid(column=1, row=1, padx=10, pady=5)

        self.__label_lb.config(text='Lb')
        self.__label_lb.grid(column=0, row=2, padx=10, pady=5)

        self.__label_kg.config(text='Kg')
        self.__label_kg.grid(column=1, row=2, padx=10, pady=5)

        self.__entry_lb.config(width=10)
        self.__entry_lb.grid(column=0, row=3, padx=10, pady=5)

        self.__entry_kg.config(width=10)
        self.__entry_kg.grid(column=1, row=3, padx=10, pady=5)

        self.__label_c.config(text='C°')
        self.__label_c.grid(column=0, row=4, padx=10, pady=5)

        self.__label_f.config(text='F°')
        self.__label_f.grid(column=1, row=4, padx=10, pady=5)

        self.__entry_c.config(width=10)
        self.__entry_c.grid(column=0, row=5, padx=10, pady=5)

        self.__entry_f.config(width=10)
        self.__entry_f.grid(column=1, row=5, padx=10, pady=5)

        self.__clear.config(command=self.__funcclear, width=8, height=1, text='Clear')
        self.__clear.grid(column=0, row=6, padx=5, pady=5)

        self.__button.config(command=self.__func, width=8, height=1, text='Converter')
        self.__button.grid(column=1, row=6, padx=5, pady=5)

    def __funcclear(self):
        self.__entry_kmh.delete(0, END)
        self.__entry_ms.delete(0, END)
        self.__entry_kg.delete(0, END)
        self.__entry_lb.delete(0, END)
        self.__entry_c.delete(0, END)
        self.__entry_f.delete(0, END)

    def __func(self):

        kmh = self.__entry_kmh.get()
        ms = self.__entry_ms.get()
        kg = self.__entry_kg.get()
        lb = self.__entry_lb.get()
        c = self.__entry_c.get()
        f = self.__entry_f.get()

        if kmh and not ms:
            val = float(kmh)
            val = val / 3.6
            val = str(val)
            self.__entry_kmh.delete(0, END)
            self.__entry_ms.insert(0, val)
        elif ms and not kmh:
            val = float(ms)
            val = val * 3.6
            val = str(val)
            self.__entry_ms.delete(0, END)
            self.__entry_kmh.insert(0, val)
        
        if kg and not lb:
            val = float(kg)
            val = val * 2.2046
            val = str(val)
            self.__entry_kg.delete(0, END)
            self.__entry_lb.insert(0, val)
        elif lb and not kg:
            val = float(lb)
            val = val / 2.2046
            val = str(val)
            self.__entry_lb.delete(0, END)
            self.__entry_kg.insert(0, val)

        if c and not f:
            val = float(c)
            val = val * 1.8 + 32
            val = str(val)
            self.__entry_c.delete(0, END)
            self.__entry_f.insert(0, val)
        elif f and not c:
            val = float(f)
            val = (val - 32) / 1.8
            val = str(val)
            self.__entry_f.delete(0, END)
            self.__entry_c.insert(0, val)

    def run(self):
        self.__root.mainloop()

main = Converter()
main.run()
