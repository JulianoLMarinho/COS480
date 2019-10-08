filePath = 'Data/'
filename = "gh.csv"
variableFilePrefix = "VariableSize_"
ID_SIZE = 7
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
    new_file.append(str(i).zfill(ID_SIZE)+','+line[0].zfill(3)+','+(',').join(line[1:]))
  i+=1

# Open the file as Write, loop the new array and write with a newline
with open(filePath+variableFilePrefix+filename, "w+") as f:
  for i in new_file:
    f.write(i)
