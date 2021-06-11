import optparse #allows us to get arguements from the user and parse them to be used in code 
import subprocess # allows us to make command line arguements 

def main ():
	options = parsed_args()
	res = subprocess.check_output(["ifconfig",options.interface])
	print(res)
	change_MAC(options.interface,options.mac_address)


def parsed_args():
	parser = optparse.OptionParser() #creates an object to interpret command line args

	parser.add_option("-i","--interface",dest="interface",help="Interface tp change the MAC address to ") #add new command line options
	parser.add_option("-m","--mac",dest="mac_address",help="The new MAC address input") #add new command line options

	(options,args) = parser.parse_args() #interpret the parsed args

	if not options.interface:
		parser.error("There has been an incorrect interface, or no interface input")
	elif not options.mac_address:
		parser.error("Please enter a MAC address, use --help for more info ")

	return options 

def change_MAC	(interface,mac_address):

	# A list has been implemented in the call to prevent a command line hijack, example: > eth0;ls;cd

	subprocess.call(["ifconfig",interface,"down"])
	subprocess.call(["ifconfig",interface,"hw","ether",mac_address])
	subprocess.call(["ifconfig",interface,"up"])
	print("\n\nInterface "+interface+" has been changed to the new Mac address of "+mac_address)

	print("\n\n",subprocess.check_output(["ifconfig",interface]))


main()