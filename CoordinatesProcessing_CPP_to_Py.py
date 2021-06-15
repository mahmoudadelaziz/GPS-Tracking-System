#Python equivalent of the ExtractLatitude() and ExtractLongitude() functions
FromGPS = "$GPGLL,4916.45,N,12311.12,W,225444,A" #Dummy input

def iter_starting_at(start_pos, string):
    for i in range(start_pos, len(string)):
        yield string[i]
        
TakenLatitude = ""
TakenLongitude = ""
CommaCount = 0

#ExtractLatitude()
for character in iter_starting_at(7, FromGPS):
    if(character == ','):
    	break
    TakenLatitude = TakenLatitude + character
        
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