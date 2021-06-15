#Python equivalent of the ExtractLatitude() and ExtractLongitude() functions
FromGPS = ['$', 'G', 'P', 'G', 'L', 'L', ',',
 '4', '9', '1', '6', '.', '4', '5', ',', 'N',
 ',', '1', '2', '3', '1', '1', '.', '1', '2', ',', 'W',
 ',', '2', '2', '5', '4', '4', '4', ',', 'A'] #Dummy input

def iter_starting_at(start_pos, string):
    for i in range(start_pos, len(string)):
        yield string[i]
        
TakenLatitude = ""
TakenLongitude = ""
CommaCount = 0

#ExtractLatitude()
for y in FromGPS:
	if (counter > 1):
        break
    if(y == ','):
        counter = counter + 1
        if(counter == 1):
            TakenLatitude = TakenLatitude + y
    
        
#ExtractLongitude()        
for x in FromGPS:
    if(CommaCount > 3):
        break
    if(x == ','):
        CommaCount = CommaCount+1
    if(CommaCount==3):
        if(x != ','):
            TakenLongitude = TakenLongitude + x

TakenLatitude = float(TakenLatitude)
TakenLatitude = float(TakenLatitude)

print(TakenLatitude) #Debugging step
print(TakenLongitude) #Debugging step
print(CommaCount) #Debugging step
