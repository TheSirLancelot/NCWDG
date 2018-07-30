#! /usr/bin/python
from pyintro import *


def fail(msg,input,output,expected):
	print msg
	print "Input: %s" %(input)
	print "Output: %s" %(output)
	print "Expected: %s" %(expected)
	exit(0)


#######################################################
#                   STRING PRACTICE                   #
#######################################################
def test_one():
	# Given a string name, return a greeting of the form "Hello, Name!"
	#str1('Bob')-> 'Hello Bob!'
	#str1('Alice')-> 'Hello Alice!'
	#str1('X')-> 'Hello X!'
	tlist = [['Bob','Hello Bob!'],
			['Alice','Hello Alice!'],
			['X','Hello X!'],
			]
	cnt = 1
	for item in tlist:
		result = greet(item[0])
		if result != item[1]:
			fail("Greet - test %d : Fail" %(cnt),item[0],result,item[1])
		else:
			print "Greet - test %d : Pass" %(cnt)
		cnt += 1
	return

def test_two():
	# Given two strings, a and b, return the result of putting them in
	# the order of abba.  e.g. "Hi" and "Bye" returns "HiByeByeHi"
	tlist = [["Hi","Bye","HiByeByeHi"],
			["Bye", "Hi", "ByeHiHiBye"],
			["Moop", "Sie", "MoopSieSieMoop"],
			]
	cnt = 1
	for item in tlist:
		result = abba(item[0],item[1])
		if result != item[2]:
			fail("ABBA - test %d : Fail" %(cnt),[item[0],item[1]],result,item[2])
		else:
			print "ABBA - test %d : Pass" %(cnt)
		cnt += 1

	return

def test_three():
	# Given an "out" string length of 4, such as "<<>>", and a word
	# return a new string (c)  where the word is in the middle of the out
	# string.  e.g. slice_us("<<>>", "word") -> "<<word>>"
	tlist = [["<<>>","Derp","<<Derp>>"],
			["Herp", ">><<", "He>><<rp"],
			["Derp", "Herp", "DeHerprp"],
			]
	cnt = 1
	for item in tlist:
		result = slice_us(item[0],item[1])
		if  result != item[2]:
			fail("Slice Us - test %d : Fail" %(cnt),[item[0],item[1]],result,item[2])
		else:
			print "Slice Us - test %d : Pass" %(cnt)
		cnt += 1
	return

def test_four():
	# Given a string s and a number n, return a new string made of
	# n copies of the last 2 chars in the original str. (hint: slicing)
	# e.g. duplicate("word", 4) -> "rdrdrdrd"
	tlist = [["Derp",4,"rp"*4],
			["Herp", 12, "rp"*12],
			["D", 20, "D"*20],
			]
	cnt = 1
	for item in tlist:
		result = duplicate(item[0],item[1])
		if  result != item[2]:
			fail("Duplicate - test %d : Fail" %(cnt),[item[0],item[1]],result,item[2])
		else:
			print "Duplicate - test %d : Pass" %(cnt)
		cnt += 1
	return

def test_five():
	# Given 2 strings, return a new string in the form of shortlongshort
	# use len(s) to figure out the length of a str
	tlist = [["Derps","Herp","HerpDerpsHerp"],
			["Derp", "Herps", "DerpHerpsDerp"],
			["Drachen", "Brais", "BraisDrachenBrais"],
			]
	cnt = 1
	for item in tlist:
		result = shortlongshort(item[0],item[1])
		if  result != item[2]:
			fail("ShortLongShort - test %d : Fail" %(cnt),[item[0],item[1]],result,item[2])
		else:
			print "ShortLongShort - test %d : Pass" %(cnt)
		cnt += 1
	return



#########################################################
#                    INTEGER PRACTICE                   #
#########################################################
def test_six():
	# return the sum of the two values
	# unless the values are the same, then double their sum
	tlist = [[5,10,15],
			[12,7,19],
			[-1,1,0],
			[20,20,80],
			[30,30,120],
			]
	cnt = 1
	for item in tlist:
		result = adding(item[0],item[1])
		if result != item[2]:
			fail("Adding - test %d : Fail" %(cnt),[item[0],item[1]],result,item[2])
		else:
			print "Adding - test %d : Pass" %(cnt)
		cnt += 1
	return

def test_seven():
	# given an int n, return the absolute value of the difference between n and 21
	# double it if n is over 21
	tlist = [[20,1],
			[40,38],
			[11,10],
			[7,14],
			[21,0],
			]
	cnt = 1
	for item in tlist:
		result = abs_dif(item[0])
		if result != item[1]:
			fail("Abs_Dif - test %d : Fail" %(cnt),item[0],result,item[1])
		else:
			print "Abs_Dif - test %d : Pass" %(cnt)
		cnt += 1
	return

def test_eight():
	# given 2 ints, return True if one of them is 10, or if their sum is 10
	tlist = [[4,5,False],
			[3,7,True],
			[10,5,True],
			[9,11,False],
			[5,5,True]
			]
	cnt = 1
	for item in tlist:
		result = tens(item[0],item[1])
		if result != item[2]:
			fail("Tens - test %d : Fail" %(cnt),[item[0],item[1]],result,item[2])
		else:
			print "Tens - test %d : Pass" %(cnt)
		cnt += 1
	return

def test_nine():
	# given an int n, return True if it is within 10 of 100
	# note: abs(num) computes the absolute value of a number
	tlist = [[89,False],
			[99,True],
			[105,True],
			[55,False],
			[100,True]
			]
	cnt = 1
	for item in tlist:
		result = hundreds(item[0])
		if result != item[1]:
			fail("Hundreds - test %d : Fail" %(cnt),item[0],result,item[1])
		else:
			print "Hundreds - test %d : Pass" %(cnt)
		cnt += 1
	return

def test_ten():
	# given 2 int values, return True if one is negative and one is positive
	# Except if the paramater "negative" is True, then return True only if both are negative
	tlist = [[[89,-12,False],True],
			[[89,-12,True],False],
			[[89,12,False],False],
			[[-15,12,True],False],
			[[-6,-16,True],True],
			]
	cnt = 1
	for item in tlist:
		result = negatives(item[0][0],item[0][1],item[0][2])
		if result != item[1]:
			fail("Negatives - test %d : Fail" %(cnt),item[0],result,item[3])
		else:
			print "Negatives - test %d : Pass" %(cnt)
		cnt += 1
	return



#######################################################
#                     LIST PRACTICE                   #
#######################################################
def test_eleven():
	# given a list of integers a, return True if 6 appears as either
	# the first or last element.  The array length will be one or more
	tlist = [
			[[1,2,3,4,5,6],True],
			[[6,5,4,3,2,1],True],
			[[1,2,5,6,3,4],False],
			]
	cnt = 1
	for item in tlist:
		result = sixes(item[0])
		if result != item[1]:
			fail("Sixes - test %d : Fail" %(cnt),item[0],result,item[1])
		else:
			print "Sixes - test %d : Pass" %(cnt)
		cnt += 1
	return

def test_twelve():
	# given an array of ints, return True if the array is length 1 or more
	# and the first element and the last element are the same value
	# list2([1,2,3,4]) -> False
	# list2([1,2,3,1]) -> True
	tlist = [
			[[1,2,3,1],True],
			[[2,3,4,1],False],
			[[2,2],True],
			[[2],False],
			]
	cnt = 1
	for item in tlist:
		result = same_length(item[0])
		if result != item[1]:
			fail("SameLength - test %d : Fail" %(cnt),item[0],result,item[1])
		else:
			print "SameLength - test %d : Pass" %(cnt)
		cnt += 1
	return

def test_thirteen():
	# given an array of integers, return the sum of those integers
	# there is a built in function that does this already, bonus points if you use it
	# type "dir(__builtins__)" in the python console to view a list of builtin functions
	tlist = [
			[[1,2,3,1],7],
			[[2,3,9,1],15],
			[[2,2],4],
			[[2],2],
			]
	cnt = 1
	for item in tlist:
		result = sum_list(item[0])
		if result != item[1]:
			fail("SumList - test %d : Fail" %(cnt),item[0],result,item[1])
		else:
			print "SumList - test %d : Pass" %(cnt)
		cnt += 1
	return

def test_fourteen():
	# given a list l, rotate it left by 2 spaces
	# [1,2,3,4] -> [3,4,1,2]
	# use slicing, do not create a new list
	tlist = [
			[[1,2,3,1],[3,1,1,2,]],
			[[2,3,4,1],[4,1,2,3]],
			[[1,2,3,4],[3,4,1,2]],
			[[1,2,4,7,4],[4,7,4,1,2]],
			]
	#CHANGED THE EXPECTED OUTPUT FOR THE LAST TEST. IT WAS [7, 4, 1, 2, 4]
	cnt = 1

	for item in tlist:
		result = rotate_slice(item[0])
		if result != item[1]:
			fail("RotateSlice - test %d : Fail" %(cnt),item[0],result,item[1])
		else:
			print "RotateSlice - test %d : Pass" %(cnt)
		cnt += 1
	return

def test_fifteen():
	# give a list l of integers, do the following:
	# 1. remove the last 2 items from the list (use l.pop())
	# 2. append the product of the popped values (use l.append(value))
	# 3. append the sum of the first 2 items in the list.
	tlist = [
			[[1,2,3,1],[1,2,3,3]],
			[[2,3,4,1],[2,3,4,5]],
			[[1,2,3,4],[1,2,12,3]],
			[[1,2,4,7,4],[1,2,4,28,3]],
			]
	cnt = 1
	for item in tlist:
		result = pop_append(item[0])
		if result != item[1]:
			fail("PopAppend - test %d : Fail" %(cnt),item[0],result,item[1])
		else:
			print "PopAppend - test %d : Pass" %(cnt)
		cnt += 1
	return


#########################################
#           BOOLEAN PRACTICE            #
#########################################
def test_sixteen():
	#write "if" statements that check if a,b,c are true or false
	#note: do not do a==False or a==True
	tlist = [
			[[True,True,True],3],
			[[True,True,False],2],
			[[True,False,True],2],
			[[True,False,False],1],
			[[False,True,True],2],
			[[False,True,False],1],
			[[False,False,True],1],
			[[False,False,False],0],
			]
	cnt = 1
	for item in tlist:
		result = basic_bool(item[0][0],item[0][1],item[0][2])
		if result != item[1]:
			fail("BasicBool - test %d : Fail" %(cnt),item[0],result,item[1])
		else:
			print "BasicBool - test %d : Pass" %(cnt)
		cnt += 1
	return

def test_seventeen():
	#write an "if" statement that checks if the product of a and b
	# is greater than 0 if so return True, else return False
	tlist = [
			[[1,2],True],
			[[2,0],False],
			[[3,-4],False],
			[[0,3],False],
			[[-3,12],False],
			]
	cnt = 1
	for item in tlist:
		result = multi_bool(item[0][0],item[0][1])
		if result != item[1]:
			fail("MiltiBool - test %d : Fail" %(cnt),item[0],result,item[1])
		else:
			print "MultiBool - test %d : Pass" %(cnt)
		cnt += 1
	return

def test_eighteen():
	#a is a list of integers, using a for loop, iterate through a to find
	#all instances of the number 7.  If a 6 appears, break out of the for loop.
	#return the number of 7's found
	#if the number of 7's found is 0, return the number 1337
	tlist = [
			[[7,],1],
			[[7,4,7],2],
			[[7,4,7,6,7],2],
			[[6,7],1337],
			[[3,4,2,5,4,7,7,7,4,3,6,7,7],3],
			[[7,7,7,7,7,7,7,7,7,7,6,7,7],10],
			]
	cnt = 1
	for item in tlist:
		result = iter_bool(item[0])
		if result != item[1]:
			fail("IterBool - test %d : Fail" %(cnt),item[0],result,item[1])
		else:
			print "IterBool - test %d : Pass" %(cnt)
		cnt += 1
	return

def test_nineteen():
	# write a SINGLE return statement, and no other lines of code
	# return true if a is greater than b and c
	tlist = [
			[[7,1,1],True],
			[[7,4,7],False],
			[[7,8,4],False],
			[[1,8,4],False],
			]
	cnt = 1
	for item in tlist:
		result = complex_bool_one(item[0][0],item[0][1],item[0][2])
		if result != item[1]:
			fail("ComplexBoolOne - test %d : Fail" %(cnt),item[0],result,item[1])
		else:
			print "ComplexBoolOne - test %d : Pass" %(cnt)
		cnt += 1
	return

def test_twenty():
	# write a single return statment: return true if -
		#1- one of a OR b is close to c (within 1 number)
		# AND
		#2- one of a OR b is far from the other two (>= 2 away)
		#note: use abs() to find the absolute value.
	tlist = [
			[[2,3,4],False],
			[[1,3,4],True],
			[[3,3,5],False],
			[[6,7,1],False],
			[[1,20,3],False],
			]
	cnt = 1
	for item in tlist:
		result = complex_bool_two(item[0][0],item[0][1],item[0][2])
		if result != item[1]:
			fail("ComplexBoolOne - test %d : Fail" %(cnt),item[0],result,item[1])
		else:
			print "ComplexBoolOne - test %d : Pass" %(cnt)
		cnt += 1
	return


##################################################
#              LOOPING AND ITERATION             #
##################################################
def test_twentyone():
	# given a list of strings (l), iterate through each item using a counter
	# if the item begins with "xkcd", strip off "xkcd" frrom the beginning
	# and replace it with "CAD".  Return the changed list.
	# Note: Do not create a second list.  Operate on the exiting one.
	tlist = [
			[['xkcd_moop','derp_sie','flub_wub'],['CAD_moop','derp_sie','flub_wub']],
			[['xkcd_moop','xkcd_sie','xkcd_wub'],['CAD_moop','CAD_sie','CAD_wub']],
			[['sie_moop','xkcd_sie','xkcd_wub'],['sie_moop','CAD_sie','CAD_wub']],
			[['sie_moop','derp_sie','xkcd_wub'],['sie_moop','derp_sie','CAD_wub']],
			]
	cnt = 1
	for item in tlist:
		result = count_for(item[0])
		if result != item[1]:
			fail("CountFor- test %d : Fail" %(cnt),item[0],result,item[1])
		else:
			print "CountFor - test %d : Pass" %(cnt)
		cnt += 1
	return

def test_twentytwo():
	# given a list of integers (l), iterate through each item
	# if the int is even, add it to even_sum
	# if the int is odd, add it to odd_sum
	# After summing all the numbers, return the product of even_sum and odd_sum
	tlist = [
			[[1,2,3,4,5],54],
			[[7,5,3,4,6],150],
			[[4,8,6,4,2],0],
			[[1,3,5,7,9],0],
			]
	cnt = 1
	for item in tlist:
		result = iter_for(item[0])
		if result != item[1]:
			fail("IterFor - test %d : Fail" %(cnt),item[0],result,item[1])
		else:
			print "IterFor - test %d : Pass" %(cnt)
		cnt += 1
	return


#THIS FUNCTION IS UTTERLY BROKEN, I'M NOT SURE HOW TO FIX IT


def test_twentythree():
	# Given a list of integers (l), use a while loop that tests if l evalutes to True (not empty)
	# If l is not empty, use l.pop() to add the numbers in the list to m

	l = []
	pop_while(l)

	tlist = [
			[[1,2,3,4,5],15],
			[[7,5,3,4,6],25],
			[[4,8,6,4,2],24],
			[[1,3,5,12,10],31],
			]
	cnt = 1
	for item in tlist:
		result = pop_while(item[0])
		if result != item[1]:
			fail("Pop_While - test %d : Fail" %(cnt),item[0],result,item[1])
		else:
			print "Pop_While - test %d : Pass" %(cnt)
		cnt += 1

	return


###############################################
#               FUNCTIONS!                    #
###############################################

def test_twentyfour():
	# write a function named my_first_function
	# have it accept no parameters, and return True
	# use "def" to define a function, just like this function!
	# also makes sure you define it above this one
	f = functions_one()
	print(f)
	return

def test_twentyfive():
	# write a function named my_second_function
	# have it return the product of a,b
	f = functions2()
	if (f(4, 5) == 20) and (f(1,9) == 9) and (f(8,6) == 48):
		print("Success, you have finished the first Python Competency.");
	return



if __name__ == '__main__':
	# TODO: dynamic import
	print "Test 1 Starting\n"
	test_one()			# Greet()
	print "\nTest 2 Starting\n"
	test_two()			# ABBA()
	print "\nTest 3 Starting\n"
	test_three()
	print "\nTest 4 Starting\n"
	test_four()
	print "\nTest 5 Starting\n"
	test_five()
	print "\nTest 6 Starting\n"
	test_six()
	print "\nTest 7 Starting\n"
	test_seven()
	print "\nTest 8 Starting\n"
	test_eight()
	print "\nTest 9 Starting\n"
	test_nine()
	print "\nTest 10 Starting\n"
	test_ten()
	print "\nTest 11 Starting\n"
	test_eleven()
	print "\nTest 12 Starting\n"
	test_twelve()
	print "\nTest 13 Starting\n"
	test_thirteen()
	print "\nTest 14 Starting\n"
	test_fourteen()
	print "\nTest 15 Starting\n"
	test_fifteen()
	print "\nTest 16 Starting\n"
	test_sixteen()
	print "\nTest 17 Starting\n"
	test_seventeen()
	print "\nTest 18 Starting\n"
	test_eighteen()
	print "\nTest 19 Starting\n"
	test_nineteen()
	print "\nTest 20 Starting\n"
	test_twenty()
	print "\nTest 21 Starting\n"
	test_twentyone()
	#print "\nTest 22 Starting\n"
	#test_twentytwo()
	print "\nTest 23 Starting\n"
	test_twentythree()
	print "\nTest 24 Starting\n"
	test_twentyfour()
	print "\nTest 25 Starting\n"
	test_twentyfive()
