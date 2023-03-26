#Vetor de strings com cada frase do texto em um respectivo índice
lorem = [" Lorem ipsum dolor sit amet, consectetur adipiscing elit.",
         " Quisque vitae varius ex, eu volutpat orci.",
         " Aenean ullamcorper orci et vulputate fermentum.",
         " Cras erat dui, finibus vel lectus ac, pharetra dictum odio.",
         " Nullam tempus scelerisque purus, sed mattis elit condimentum nec.",
         " Etiam risus sapien, auctor eu volutpat sit amet, porta in nunc.",
         " Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas.",
         " Proin ipsum purus, laoreet quis dictum a, laoreet sed ligula.",
         " Integer ultricies malesuada quam.",
         " Cras vel elit sed mi placerat pharetra eget vel odio.",
         " Duis ac nulla varius diam ultrices rutrum."]
        
"""Função geradora do texto final em uma única
string, recebe como parâmetro um vetor que diz
o número de frases em cada parágrafo."""
def gerar_texto(arr_frases):
    
    texto = ''
    index = 0
    
    for num_frases in arr_frases: #adiciona os paragrafos
        
        cont = 0
        
        while(cont < num_frases): #adiciona as frases
            
            texto += lorem[index]
            
            cont += 1
            index = (index + 1) % 10 
            index %= 10
            
        texto += '\n'
        
    return texto
    
#Código interativo com o usuário.
x = input('Digite o número de frases em cada parágrafo e dê enter: ').split()
valores = [int(val) for val in x]

resultado = gerar_texto(valores)

print(resultado)
