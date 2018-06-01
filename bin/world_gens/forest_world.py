dir_temp = "../cell_templates/"
dir_world = "../world_folder/"
world_file_name = dir_world + "world_file.txt"
num_temps = 20
import io
from random import randint
from shutil import copyfile

temps = []
for i in range(num_temps):
	t = dir_temp + str(i)
	temps.append(t)
	
w = 200
h = 200

wfc = ""
world_file = io.open(world_file_name, "w", newline='\n')

for y in range(w):
	for x in range(h):
		rand_cell = randint(0, num_temps-1)
		
		name_source = dir_temp + "cell_" + str(rand_cell) + ".xml"
		name_dest = dir_world + "cell_" + str(x) + "_" + str(y) + ".xml"
		copyfile(name_source, name_dest)
		
		wfc += str(x) + " " + str(y) + "\n"
		
world_file.write(wfc)
world_file.close()
