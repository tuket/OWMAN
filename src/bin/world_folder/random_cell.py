import sys
import random

cellSize = 250.0;

ents=[

	("topo.png", 100, 150),
	("chicken.png", 64, 64),
	("pikachu.png", 64, 64),
	("elf.png", 100, 100),
	("tukifoc.png", 120, 120),
	("wood_box.png", 80, 80),
	("angry_bird.png", 64, 64)
]

def gen_rand_cell():
	
	res = ""
	res += "<cell>\n"

	numEnts = random.randint(2, 6)

	for i in xrange(numEnts):

		res += "<entity>\n"

		res += "\t<position>\n"

		x = random.uniform(0, cellSize);
		y = random.uniform(0, cellSize);

		res += "\t\t<x>"
		res += str(x)
		res += "</x>\n"

		res += "\t\t<y>"
		res += str(y)
		res += "</y>\n"

		res += "\t</position>\n"

		res += "\t<graphics>\n"

		sp = random.randint(0, len(ents)-1);

		res += "\t\t<texture>"
		res += str(ents[sp][0])
		res += "</texture>\n"

		res += "\t\t<width>"
		res += str(ents[sp][1])
		res += "</width>\n"

		res += "\t\t<height>"
		res += str(ents[sp][2])
		res += "</height>\n"

		res += "\t</graphics>\n"

		res += "\t<physics>\n"

		res += "\t\t<shape>box</shape>\n"
		res += "\t\t<width>"
		res += str(ents[sp][1])
		res += "</width>\n"

		res += "\t\t<height>"
		res += str(ents[sp][2])
		res += "</height>\n"

		res += "\t\t<mass>60</mass>\n"

		res += "\t</physics>\n"

		res += "</entity>\n"

	res += "</cell>\n"

	return res


fileName = sys.argv[1]
f = open(fileName, 'w')

f.write( gen_rand_cell() )