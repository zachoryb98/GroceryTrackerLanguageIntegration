#Zach Behrensmeyer
# CS210 Grocery Tracker Assignment
# This is the python integration for the Grocery Tracker assignment
# It will print a list of groceries and count of items sold from a file
# It will return a provided values grocery item and count to the C++ portion to be displayed
# It will read the grocery data from a file get the count and write it to a new file to be read by C++
# It makes use of preprovided code by SNHU to print to the console in Python

import re
import string
import collections

## *** PROVIDED CODE START *** ##

def printsomething():
    print("Hello from python!")

def PrintMe(v):
    print("You sent me: " + v)
    return 100;

def SquareValue(v):
    return v * v

## *** PROVIDED CODE END *** ##

#This method reads data from a file and displays that data to the console
def DisplayListOfItems():

    #Name of file, this variable can be changed
    fileName = "CS210_Project_Three_Input_File.txt"
    
    #Open and read
    inputFile = open(fileName, "r")

    #Only if the file was opened
    if inputFile:

        #read data and create a dictionary
        inputData = inputFile.read()
        itemList = inputData.split()
        itemTracker = {}
        
        #Close the file, we no longer need it
        inputFile.close()
        
        print("ITEMS SOLD: " + '\n')

        #Add to list or count if match
        for item in itemList:
            itemTracker[item] = itemTracker.get(item, 0) + 1 
     
        #String to hold the final value for the grocery list
        result = ""
        for key, value in itemTracker.items():

            #Add each dictionary entry to the result
            result += key + ": " + str(value) + '\n'
        
        #Display list and return to main menu
        print(result)
        return
    else:

        #File was not opened for some reason
        print(fileName, " was not opened, check the file and try again.")
        return

#This method will print given item and count
def GetNumberSoldOfSingleItem(itemName):    
    
    filename = "CS210_Project_Three_Input_File.txt"  
    inputFile = open(filename, "r")  

    #Only if the file was opened
    if inputFile:

        #read data and create a dictionary
        inputData = inputFile.read() 
        itemList = inputData.split()  
        itemTracker = {} 

        #File no longer needed close it.
        inputFile.close()       

        #Add to list and count if match
        for item in itemList:
            itemTracker[item] = itemTracker.get(item, 0) + 1
            
        #Compare given name to dictionary names from file
        if itemName in itemTracker:

            #If found send back the name and account
            return itemTracker[itemName]
        else:            
            return 0
    else:

        #File was not able to be opened for some reason
        print("The file was not opened, check the file and try again.")  
        return

def WriteGroceryDataToFile():    
    
    filename = "CS210_Project_Three_Input_File.txt"  
    inputFile = open(filename, "r")  

    #Only if the file was opened
    if inputFile:        

        #read data and create a dictionary
        inputData = inputFile.read() 
        itemList = inputData.split()  
        itemTracker = {} 

        #close the file, no longer needed
        inputFile.close()

        #Add to list and count if match
        for item in itemList:                        
            itemTracker[item] = itemTracker.get(item, 0) + 1           
    else:
        #File was unable to be opened for some reason
        print("The file was not opened, check the file and try again.")
        return        
    
    #Open file we are writing data to
    outputFile = open("frequency.dat", "w")

    #if the file being written to was opened
    if outputFile:        

        #Search for the key in the dictionary, if its found write to the file
        for key in list(itemTracker.keys()):            
            outputFile.write(str(key.capitalize()) + ": " + str(itemTracker[key]) + "\n")
    else:
        #File was unable to be opened for some reason
        print("The file was not opened, check the file and try again.")

    #Close the file
    outputFile.close()
    return