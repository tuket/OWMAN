s = """<cell>
<entity>
	<position>
		<x>125</x>
		<y>125</y>
	</position>
	<graphics>
		<sprite>grass</sprite>
		<width>250</width>
		<height>250</height>
		<priority>-10</priority>
	</graphics>
</entity>
</cell>"""

wf = open("world_file.txt", "w")

for y in xrange(0, 200):
	for x in xrange(0, 200):
		name = "cell_" + str(x) + "_" + str(y) + ".xml"
		f = open(name, "w")
		f.write(s)
		f.close()
		
		line = str(x) + " " + str(y) + "\n"
		wf.write(line)
