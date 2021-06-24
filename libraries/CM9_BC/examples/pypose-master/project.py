#!/usr/bin/env python

"""
  PyPose: for all things related to PyPose projects
  Copyright (c) 2008-2010 Michael E. Ferguson.  All right reserved.

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software Foundation,
  Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
"""


###############################################################################
# Pose class is a list, first element is name, rest are servo positions.
class pose(list):
    """ A class to hold a pose. """
    def __init__(self, line, length):
        # now load the name, positions for this pose
        try:
            for servo in range(length):
                if line.find(",") > 0:
                    self.append(int(line[0:line.index(",")]))
                else:
                    self.append(int(line[0:]))
                line = line[line.index(",")+1:]
        # we may not have enough data, so dump it
        except:
            for i in range(length-len(self)):
                self.append(512)

    def __str__(self):
        return ", ".join([str(p) for p in self])


###############################################################################
# Sequence class is a list, first element is name, rest are (pose,time) pairs
class sequence(list):
    """ A class to hold a sequence. """
    def __init__(self, line=None):
        # load the name, (pose,time) pairs for this sequence
        try:
            if line == None:
                return
            while True:
                if line.find(",") > 0:
                    self.append(line[0:line.index(",")].strip().rstrip())
                elif line != "":
                    self.append(line.strip().rstrip())
                line = line[line.index(",")+1:]
        except:
            pass

    def __str__(self):
        return ", ".join([str(t) for t in self])


###############################################################################
# Class for dealing with project files
class project:
    def __init__(self):
        self.name = ""
        self.count = 18
        self.resolution = [1024 for i in range(self.count)]
        self.poses = dict()
        self.sequences = dict()
        self.nuke = ""
        self.save = False

    def load(self, filename):
        self.poses = dict()
        self.sequences = dict()
        prjFile = open(filename, "r").readlines()
        # load robot name and servo count
        self.name = prjFile[0].split(":")[0]
        self.count = int(prjFile[0].split(":")[1])
        # load resolution of each servo in count
        self.resolution = [int(x) for x in prjFile[0].split(":")[2:]]
        if len(self.resolution) != self.count:
            self.resolution = [1024 for x in range(self.count)]
        # load poses and sequences
        for line in prjFile[1:]:
            if line[0:5] == "Pose=":
                self.poses[line[5:line.index(":")]] = pose(line[line.index(":")+1:].rstrip(),self.count)
            elif line[0:4] == "Seq=":
                self.sequences[line[4:line.index(":")]] = (sequence(line[line.index(":")+1:].rstrip()))
            elif line[0:5] == "Nuke=":
                self.nuke = line[5:].rstrip()
            # these next two lines can be removed later, once everyone is moved to Ver 0.91
            else:
                self.poses[line[0:line.index(":")]] = pose(line[line.index(":")+1:].rstrip(),self.count)
        self.save = False

    def saveFile(self, filename):
        prjFile = open(filename, "w")
        print>>prjFile, self.name + ":" + str(self.count) + ":" + ":".join([str(x) for x in self.resolution])
        for p in self.poses.keys():
            print>>prjFile, "Pose=" + p + ":" + str(self.poses[p])
        for s in self.sequences.keys():
            print>>prjFile, "Seq=" + s + ": " + str(self.sequences[s])
        if self.nuke != "":
            print>>prjFile, "Nuke=" + self.nuke
        self.save = False

    def new(self, nName, nCount, nResolution):
        self.poses = dict()
        self.sequences = dict()
        self.filename = ""
        self.count = nCount
        self.name = nName
        self.resolution = [nResolution for i in range(self.count)]
        self.save = True

    ###########################################################################
    # Export functionality
    def export(self, filename):
        import os.path
        """ Export a pose file for use with OpenCM BioloidController Library. """
        filepath, shortfilenameStr = os.path.split(filename)
        posefileNameStr = shortfilenameStr + "_Poses.h"
        seqfileNameStr = shortfilenameStr + "_Sequences.h"
        posefileIDarray = shortfilenameStr + "_id"

        posefile = open(filename + "_Poses.h", "w")
        print>>posefile, "#ifndef " + self.name.upper() + "_POSES"
        print>>posefile, "#define " + self.name.upper() + "_POSES"
        print>>posefile, ""
        print>>posefile, "#include <CM9_BC.h>"
        print>>posefile, ""

        print>>posefile, "bc_pose_t __FLASH__ " + posefileIDarray + "[] = {" + str(self.count) + ",",
        for itera in range(self.count-1):
            print>>posefile, str(itera+1) + ",",
        print>>posefile, str(itera+2)+"};\n"

        for p in self.poses.keys():
            if p.startswith("ik_"):
                continue
            print>>posefile, "bc_pose_t __FLASH__ " + p + "[] = {" + str(self.count) + ",",
            p = self.poses[p]
            for x in p[0:-1]:
                print>>posefile, str(x) + ",",
            print>>posefile, str(p[-1]) + "};"
            #print>>posefile, ""
        print>>posefile, ""
        print>>posefile, "#endif"
        posefile.close()

        seqfile = open(filename + "_Sequences.h", "w")
        print>>seqfile, "#ifndef " + self.name.upper() + "_SEQUENCES"
        print>>seqfile, "#define " + self.name.upper() + "_SEQUENCES"
        print>>seqfile, ""
        print>>seqfile, "#include \"" + posefileNameStr + "\""
        print>>seqfile, ""
        for s in self.sequences.keys():
            print>>seqfile, "bc_seq_t __FLASH__ " + s + "[] = {{" +  posefileIDarray + "," + str(len(self.sequences[s])) + "}",
            s = self.sequences[s]
            for t in s:
                print>>seqfile, ",{" + t[0:t.find("|")] + "," + t[t.find("|")+1:] + "}",            
            print>>seqfile, "};"
        print>>seqfile, ""
        print>>seqfile, "#endif"
        seqfile.close()
        
        #Add stuff to create a proper RPM_Array using the sequences with 0 as "next" and "stop" indices.
        rpmfile = open(filename + "_RPM.h", "w")
        print>>rpmfile, "#ifndef " + self.name.upper() + "_RPM"
        print>>rpmfile, "#define " + self.name.upper() + "_RPM"
        print>>rpmfile, ""
        print>>rpmfile, "#include \"" + seqfileNameStr + "\""
        print>>rpmfile, ""
        print>>rpmfile, "rpm_page_t " + self.name + "_RoboPlusMotion_Array[] __FLASH__ = {"
        print>>rpmfile, "	{0,						0,		255}",
        itera = 0
        for s in self.sequences.keys():
            print>>rpmfile, ",	// " + str(itera) + "\n	{" + s + ",	0, 0}",
            itera += 1
        print>>rpmfile, "	// "+ str(itera)
        print>>rpmfile, "}"
        print>>rpmfile, ""
        print>>rpmfile, "#endif"
        rpmfile.close()


def extract(li):
    """ extract x%256,x>>8 for every x in li """
    out = list()
    for i in li:
        out = out + [i%256,i>>8]
    return out

