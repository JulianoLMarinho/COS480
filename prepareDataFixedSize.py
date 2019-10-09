filePath = 'Data/'
filename = "gh.csv"
fixedFilePrefix = "FixedSize_"
ID_SIZE = 7
UHE_SIZE = 3
CENARIO_SIZE = 3
ESTAGIO_SIZE = 10
GERACAO_SIZE = 20
# Open the file as read
f = open(filePath+filename, "r+")
# Create an array to hold write data
new_file = []
# Loop the file line by line
i = 0
for line in f:
  # add
  if(i==0):
    new_file.append('id,'+line)
  else:
    line = line.split(',')
    new_file.append(
      str(i).zfill(ID_SIZE)+',' # id
      +line[0].zfill(UHE_SIZE)+','     # UHE
      +line[1].zfill(CENARIO_SIZE)+','     # Cenario
      +line[2].zfill(ESTAGIO_SIZE)+','    # Estagio
      +line[3].replace('\n', '').zfill(GERACAO_SIZE)+'\n'        # Geracao
    )

  i+=1

# Open the file as Write, loop the new array and write with a newline
with open(filePath + fixedFilePrefix + filename, "w+") as f:
  for i in new_file:
    f.write(i)
